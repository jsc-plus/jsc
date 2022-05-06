import * as ts from "typescript"
import * as fs from "fs"
import * as path from "path"
import { Source, toSource, toSymbolModule, toSymbolModulePath, toSymbolName, toType, toTypeDefaultValue } from "./source"
import { Module, Function, Type, Argument, Doc, Tag, Class, Property, Method, Body, Symbol, ModuleName, Scope, ScopeVar, TypeKinds, TypeKind, Var, isEmptyModule } from "./types"
import { baseClassSet, baseFunctionSet } from "./base"

var StringClass = baseClassSet.get('String')!
var ObjectClass = baseClassSet.get('Object')!

export interface SourceFileModule extends Module {
    sourceFile: ts.SourceFile
    declare: ts.Node
    source?: Source
}


export interface ContextOptions {
    checker?: ts.TypeChecker
    module?: SourceFileModule
    moduleSet?: Map<string, SourceFileModule>
    scope?: Scope
    isa?: Class
    method?: Method
}

export class Context {

    protected _parent?: Context
    protected _options: ContextOptions

    constructor(options: ContextOptions, parent?: Context) {
        this._options = options
        this._parent = parent
    }

    newContext(options: ContextOptions): Context {
        return new Context(options, this)
    }

    get checker(): ts.TypeChecker {
        if (this._options.checker) {
            return this._options.checker
        }
        return this._parent!.checker
    }

    get module(): SourceFileModule {
        if (this._options.module) {
            return this._options.module
        }
        return this._parent!.module
    }

    get moduleSet(): Map<string, SourceFileModule> {
        if (this._options.moduleSet) {
            return this._options.moduleSet
        }
        return this._parent!.moduleSet
    }

    get scope(): Scope {
        if (this._options.scope) {
            return this._options.scope
        }
        return this._parent!.scope
    }

    get isa(): Class | undefined {
        if (this._options.isa) {
            return this._options.isa
        }
        if (this._parent) {
            return this._parent!.isa
        }
    }

    get method(): Method | undefined {
        if (this._options.method) {
            return this._options.method
        }
        if (this._parent) {
            return this._parent!.method
        }
    }

    getModule(): SourceFileModule | undefined {
        if (this._options.module) {
            return this._options.module
        }
        if (this._parent) {
            return this._parent.getModule();
        }
    }

    getClass(name: string, m?: Module): Class | undefined {
        if (m === undefined) {
            m = this.getModule()
        }
        if (m) {
            for (let isa of m.classes) {
                if (isa.name.name == name) {
                    return isa
                }
            }
            {
                let isa = m.refClass.get(name)
                if (isa) {
                    return isa
                }
            }
            let i = name.indexOf('.')
            if (i >= 0) {
                let r = m.ref.get(name.substring(0, i))
                if (r) {
                    let n = name.substring(i + 1)
                    return this.getClass(n,r)
                }
            }
        }
        return baseClassSet.get(name)
    }

    getVar(name: string, m?: Module): Var | undefined {
        if (m === undefined) {
            m = this.getModule()
        }
        if (m) {
            for (let v of m.vars) {
                if (v.name.name == name) {
                    return v
                }
            }
            {
                let v = m.refVar.get(name)
                if (v) {
                    return v
                }
            }
            let i = name.indexOf('.')
            if (i >= 0) {
                let r = m.ref.get(name.substring(0, i))
                if (r) {
                    let n = name.substring(i + 1)
                    return this.getVar(n, r)
                }
            }
        }
    }
}

export function mkdir(dir: string): void {
    if (!fs.existsSync(dir)) {
        mkdir(path.dirname(dir))
        fs.mkdirSync(dir)
    }
}

export function assignVarType(type: Type, fromType: Type): string {
    let t = type.isa == StringClass ? TypeKind.OBJECT : type.kind
    let f = fromType.isa == StringClass ? TypeKind.OBJECT : fromType.kind
    if (t == f) {
        return ''
    }
    return `JSC_AS_${TypeKinds[t]}_${TypeKinds[f]}`
}

export function parseFunctionType(ctx: Context, s: ts.FunctionTypeNode): Function {
    let v: Function = {
        name: {
            name: '__type',
            module: ctx.module.name,
        },
        returnType: parseVarType(ctx, { kind: TypeKind.VOID }, s.type),
        arguments: parseArguments(ctx, s.parameters)
    }
    return v;
}

export function parseVarType(ctx: Context, defaultType: Type, type?: ts.TypeNode): Type {
    if (type) {

        if (ts.isUnionTypeNode(type)) {
            let t = parseVarType(ctx, defaultType, type.types[0])
            for (let i = 1; i < type.types.length; i++) {
                if (type.types[i].getText() == 'jsc.weak') {
                    t.weak = true
                    break
                }
            }
            return t
        }

        switch (type.getText()) {
            case 'jsc.uint64':
                return { kind: TypeKind.UINT64 }
            case 'jsc.int64':
                return { kind: TypeKind.INT64 }
            case 'jsc.uint32':
                return { kind: TypeKind.UINT32 }
            case 'jsc.int32':
                return { kind: TypeKind.INT32 }
            case 'jsc.uint16':
                return { kind: TypeKind.UINT16 }
            case 'jsc.int16':
                return { kind: TypeKind.INT16 }
            case 'jsc.uint8':
                return { kind: TypeKind.UINT8 }
            case 'jsc.int8':
                return { kind: TypeKind.INT8 }
            case 'jsc.uint':
                return { kind: TypeKind.UINT }
            case 'jsc.int':
                return { kind: TypeKind.INT }
            case 'jsc.ulong':
                return { kind: TypeKind.ULONG }
            case 'jsc.long':
                return { kind: TypeKind.LONG }
            case 'jsc.float32':
                return { kind: TypeKind.FLOAT32 }
            case 'number':
            case 'jsc.float64':
                return { kind: TypeKind.FLOAT64 }
            case 'boolean':
                return { kind: TypeKind.BOOLEAN }
            case 'string':
                return { kind: TypeKind.STRING }
            case 'any':
                return { kind: TypeKind.VARIANT }
            case 'jsc.ptr':
                return { kind: TypeKind.PTR }
            case 'void':
                return { kind: TypeKind.VOID }
            case 'jsc.CString':
                return { kind: TypeKind.STRING, CString: true }
        }

        console.info(type.getText())

        let t = ctx.checker.getTypeAtLocation(type)

        if (t.symbol && t.symbol.declarations) {
            for (let i of t.symbol.declarations) {
                if (ts.isFunctionTypeNode(i)) {
                    return {
                        kind: TypeKind.PTR,
                        func: parseFunctionType(ctx, i)
                    }
                }
            }
        }

        let isa = ctx.getClass(t.symbol.name);

        if (isa) {
            return { kind: TypeKind.OBJECT, isa: isa }
        }

    }
    return defaultType
}

export function isStringType(t: Type): boolean {
    return t.kind == TypeKind.STRING || (t.kind == TypeKind.OBJECT && t.isa == StringClass)
}

let logicOpSet = new Set<string>(['==', '===', '!=', '!==', '>', '>=', '<', '<=', '&&', '||'])

export function parseVarTypeWithExpression(ctx: Context, s: ts.Expression, defaultType: Type): Type {
    if (ts.isNewExpression(s)) {
        let sv = getScopeVar(ctx, s.expression);
        return sv.type
    } else if (ts.isStringLiteral(s)) {
        return {
            kind: TypeKind.STRING
        }
    } else if (ts.isNumericLiteral(s)) {
        let f = parseFloat(s.text);
        let i = Math.floor(f)
        if (f == i) {
            if (i >= 0) {
                if (i <= 2147483647) {
                    return {
                        kind: TypeKind.INT
                    }
                } else if (i <= 4294967295) {
                    return {
                        kind: TypeKind.UINT
                    }
                } else {
                    return {
                        kind: TypeKind.INT64
                    }
                }
            } else if (i >= -2147483648) {
                return {
                    kind: TypeKind.INT
                }
            } else {
                return {
                    kind: TypeKind.INT64
                }
            }
        } else {
            return {
                kind: TypeKind.FLOAT64
            }
        }
    } else if (ts.isBinaryExpression(s)) {
        let aType = parseVarTypeWithExpression(ctx, s.left, defaultType);
        let bType = parseVarTypeWithExpression(ctx, s.right, defaultType);
        let op = s.operatorToken.getText()
        if (logicOpSet.has(op)) {
            return {
                kind: TypeKind.BOOLEAN,
            }
        }
        if (op == '=') {
            return aType
        }
        if (isStringType(aType) || isStringType(bType)) {
            return {
                kind: TypeKind.STRING,
                isa: StringClass,
            }
        }
        if (aType.kind < bType.kind) {
            return bType
        }
        return aType
    } else if (ts.isPrefixUnaryExpression(s) || ts.isPostfixUnaryExpression(s)) {
        return {
            kind: TypeKind.INT
        }
    } else {
        let sv = getScopeVar(ctx, s);
        return sv.type
    }
}

export function parseArguments(ctx: Context, args: ts.NodeArray<ts.ParameterDeclaration>): Argument[] {
    let vs: Argument[] = []
    args.forEach((item) => {
        let t = parseVarType(ctx, { kind: TypeKind.VARIANT }, item.type)
        vs.push({
            name: item.name.getText(),
            type: t
        })
    })
    return vs
}

export function parseDoc(ctx: Context, doc: Doc, symbol: ts.Symbol): void {
    doc.title = ts.displayPartsToString(symbol.getDocumentationComment(ctx.checker));
    doc.tags = []
    for (let tag of symbol.getJsDocTags()) {
        let v: Tag = {
            name: tag.name
        }
        if (tag.text) {
            let vs: string[] = []
            for (let t of tag.text) {
                vs.push(t.text)
            }
            v.value = vs.join(' ')
        }
        doc.tags.push(v)
    }
}

export function getScopeVar(ctx: Context, s: ts.Expression): ScopeVar {

    if (s.kind == ts.SyntaxKind.SuperKeyword) {
        if (ctx.isa) {
            return {
                name: {
                    name: 'super'
                },
                type: {
                    kind: TypeKind.OBJECT,
                    isa: ctx.isa.base
                }
            }
        }
    }

    if (s.kind == ts.SyntaxKind.ThisKeyword) {
        if (ctx.isa) {
            return {
                name: {
                    name: 'this'
                },
                type: {
                    kind: TypeKind.OBJECT,
                    isa: ctx.isa
                }
            }
        }
    }

    if (ts.isIdentifier(s)) {

        let v = ctx.scope.get(s.text);

        if (v) {
            return v
        }

        for (let i of ctx.module.classes) {
            if (i.name.name == s.text) {
                return {
                    name: i.name,
                    type: {
                        kind: TypeKind.OBJECT,
                        isa: i
                    }
                }
            }
        }

        let isa = baseClassSet.get(s.text)

        if (isa) {
            return {
                name: isa.name,
                type: {
                    kind: TypeKind.OBJECT,
                    isa: isa
                }
            }
        }
    }



    console.error(s)
    debugger
    throw new Error(`getObjectSymbol kind:${s.kind}`)
}

export function getClassWithMethod(method: string, isa?: Class): { isa: Class, method: Method } | undefined {
    if (isa) {
        for (let i of isa.methods) {
            if (i.name.name == method) {
                return {
                    isa: isa,
                    method: i
                }
            }
        }
        return getClassWithMethod(method, isa.base)
    } else {
        for (let i of ObjectClass.methods) {
            if (i.name.name == method) {
                return {
                    isa: ObjectClass,
                    method: i
                }
            }
        }
    }
}

export function parseCallArguments(ctx: Context, args: ts.NodeArray<ts.Expression> | undefined, func: Function, vs: string[] = []): string {
    let i = 0;
    while (i < func.arguments.length) {
        let a = func.arguments[i];
        if (a.name == '...') {
            if (i > 0 && args && i - 1 < args.length) {
                let e = args[i - 1]
                if (ts.isStringLiteral(e)) {
                    e.text.replace(/%[\-\.0-9]{0,}(s|d|g|f|ld|lld|u|lu|llu|x|X)/g, function (text, type) {
                        let t = TypeKind.STRING
                        switch (type) {
                            case 's':
                                t = TypeKind.STRING;
                                break;
                            case 'd':
                                t = TypeKind.INT;
                                break;
                            case 'g':
                            case 'f':
                                t = TypeKind.FLOAT64;
                                break;
                            case 'ld':
                                t = TypeKind.LONG;
                                break;
                            case 'lld':
                                t = TypeKind.INT64;
                                break;
                            case 'u':
                                t = TypeKind.UINT;
                                break;
                            case 'lu':
                                t = TypeKind.ULONG;
                                break;
                            case 'llu':
                            case 'x':
                            case 'X':
                                t = TypeKind.UINT64;
                                break;
                        }
                        if (i < args.length) {
                            let v = parseVarTypeWithExpression(ctx, args[i], { kind: t })
                            vs.push(`${assignVarType({ kind: t }, v)}(${parseExpression(ctx, args[i])})`)
                        } else {
                            vs.push(`${toTypeDefaultValue({ kind: t })}`)
                        }
                        i++;
                        return text;
                    })
                } else {
                    break
                }
            } else {
                break
            }
        } else if (args && i < args.length) {
            let v = parseVarTypeWithExpression(ctx, args[i], a.type)
            vs.push(`${assignVarType(a.type, v)}(${parseExpression(ctx, args[i])})`)
        } else {
            vs.push(toTypeDefaultValue(a.type))
        }
        i++;
    }
    return vs.join(',')
}

export function parseExpression(ctx: Context, s: ts.Expression): string {

    if (ts.isCallExpression(s)) {
        let baseFunc = baseFunctionSet.get(s.expression.getText())
        if (baseFunc) {
            return `${baseFunc.name.name}(${parseCallArguments(ctx, s.arguments, baseFunc)})`
        } else if (ts.isPropertyAccessExpression(s.expression)) {
            let sv = getScopeVar(ctx, s.expression.expression);
            if (sv.type.kind == TypeKind.OBJECT) {
                let name = s.expression.name.text
                let m = getClassWithMethod(name, sv.type.isa)
                let objectName = sv.name.name == 'this' || sv.name.name == 'super' ? '__object' : sv.name.name
                if (m && m.isa == ObjectClass) {
                    return `jsc_object_${name}_((jsc_class_t *)&jsc_Object,${objectName}${parseCallArguments(ctx, s.arguments, m.method)})`
                } else if (m && m.isa) {
                    return `jsc_${toSymbolName(m.isa.name)}_${name}_((jsc_class_t *)&jsc_${toSymbolName(m.isa.name)},${objectName}${parseCallArguments(ctx, s.arguments, m.method)})`
                }
            }
        }
    } else if (ts.isStringLiteral(s)) {
        return JSON.stringify(s.text)
    } else if (ts.isNumericLiteral(s)) {
        return s.text
    } else if (ts.isBinaryExpression(s)) {
        let op: string = s.operatorToken.getText()
        if (op == '===') {
            op = '=='
        } else if (op == '!==') {
            op = '!='
        }
        let aType = parseVarTypeWithExpression(ctx, s.left, { kind: TypeKind.STRING })
        let bType = parseVarTypeWithExpression(ctx, s.right, { kind: TypeKind.STRING })
        if (op == '=') {

            if (aType.var && (aType.isa || aType.kind == TypeKind.OBJECT || (aType.kind == TypeKind.STRING && !aType.CString))) {
                if (aType.weak) {
                    return `jsc_setWeak(&${parseExpression(ctx, s.left)},${assignVarType({ kind: TypeKind.OBJECT }, bType)}(${parseExpression(ctx, s.right)}))`
                } else {
                    return `jsc_setStrong(&${parseExpression(ctx, s.left)},${assignVarType({ kind: TypeKind.OBJECT }, bType)}(${parseExpression(ctx, s.right)}))`
                }
            }

        } if (isStringType(aType) || isStringType(bType)) {
            if (op == '==' || op == '!=' || op == '<' || op == '<=' || op == '>' || op == '>=') {
                return `(JSC_STRING_COMP(${assignVarType({ kind: TypeKind.STRING }, aType)}(${parseExpression(ctx, s.left)}),${assignVarType({ kind: TypeKind.STRING }, bType)}(${parseExpression(ctx, s.right)})) ${op} 0)`
            } else if (op == '+') {
                return `JSC_STRING_ADD(${assignVarType({ kind: TypeKind.STRING }, aType)}(${parseExpression(ctx, s.left)}),${assignVarType({ kind: TypeKind.STRING }, bType)}(${parseExpression(ctx, s.right)}))`
            } else {
                debugger
                throw new Error(s.getText())
            }
        }
        return `(${parseExpression(ctx, s.left)}${op}${parseExpression(ctx, s.right)})`
    } else if (ts.isPrefixUnaryExpression(s)) {
        if (ts.isIdentifier(s.operand)) {
            switch (s.operator) {
                case ts.SyntaxKind.PlusPlusToken:
                    return `(++${s.operand.text})`
                case ts.SyntaxKind.MinusMinusToken:
                    return `(--${s.operand.text})`
            }
        }
    } else if (ts.isPostfixUnaryExpression(s)) {
        if (ts.isIdentifier(s.operand)) {
            switch (s.operator) {
                case ts.SyntaxKind.PlusPlusToken:
                    return `(${s.operand.text}++)`
                case ts.SyntaxKind.MinusMinusToken:
                    return `(${s.operand.text}--)`
            }
        }
    } else if (ts.isNewExpression(s)) {
        let sv = getScopeVar(ctx, s.expression);
        if (sv.type.kind == TypeKind.OBJECT && sv.type.isa) {
            if (sv.type.isa.new) {
                return `(jsc_object_t *) jsc_${toSymbolName(sv.type.isa.name)}_${sv.type.isa.new.name.name}(${parseCallArguments(ctx, s.arguments, sv.type.isa.new)})`;
            }
            return `jsc_object_new((jsc_class_t*)&jsc_${toSymbolName(sv.type.isa.name)},0)`
        }
    } else if (ts.isIdentifier(s)) {
        {
            let v = ctx.getVar(s.text)
            if(v) {
                return `jsc_${toSymbolName(v.name)}`
            }
        }
        return s.text;
    }

    debugger
    throw new Error(s.getText())
}

export function parseStatement(ctx: Context, s: ts.Statement): string {

    if (ts.isExpressionStatement(s)) {
        return parseExpression(ctx, s.expression);
    } else if (ts.isVariableStatement(s)) {
        let n = 0;
        let vs: string[] = []
        for (let i of s.declarationList.declarations) {
            let varType: Type
            if (!i.type && i.initializer) {
                varType = parseVarTypeWithExpression(ctx, i.initializer, { kind: TypeKind.VARIANT })
            } else {
                varType = parseVarType(ctx, { kind: TypeKind.VARIANT }, i.type)
            }
            let name = i.name.getText()
            if (n == 0) {
                vs.push(`${toType(varType)} `)
            } else {
                vs.push(',')
            }
            vs.push(name)
            if (i.initializer) {
                vs.push(`=${parseExpression(ctx, i.initializer)}`)
            } else {
                vs.push(`=${toTypeDefaultValue(varType)}`)
            }
            ctx.scope.set({
                name: name,
                module: ctx.module.name
            }, varType)
            n++;
        }
        return vs.join('')
    } else if (ts.isReturnStatement(s)) {
        if (s.expression) {
            return `return (${parseExpression(ctx, s.expression)})`
        }
        return 'return'
    }

    debugger

    throw new Error(s.getText() + ' kind:' + s.kind)

}

export function parseBody(ctx: Context, node?: ts.FunctionBody): Body | undefined {
    if (node) {
        let _ctx = ctx.newContext({ scope: new Scope(ctx.scope) })
        return (level: number = 0): string => {
            let vs: string[] = []
            for (let s of node.statements) {
                vs.push(`${"\t".repeat(level)}${parseStatement(_ctx, s)};\n`)
            }
            return vs.join('')
        }
    }
}

export function parseFunction(ctx: Context, node: ts.FunctionDeclaration): void {

    let symbol = ctx.checker.getSymbolAtLocation(node.name!)!;

    let v: Function = {
        name: {
            name: symbol.name,
            module: ctx.module.name
        },
        returnType: parseVarType(ctx, { kind: TypeKind.VOID }, node.type),
        arguments: parseArguments(ctx, node.parameters),
    }

    let c = ctx.newContext({ scope: new Scope(ctx.scope) })

    for (let a of v.arguments) {
        c.scope.set({ name: a.name, module: ctx.module.name }, a.type)
    }

    v.body = parseBody(c, node.body)

    parseDoc(ctx, v, symbol)

    if (node.modifiers) {
        node.modifiers.forEach((item) => {
            if (item.kind == ts.SyntaxKind.ExportKeyword) {
                v.name.export = true
            }
        })
    }

    ctx.module.functions.push(v)

}

export function parseClass(ctx: Context, node: ts.ClassDeclaration): void {

    let symbol = ctx.checker.getSymbolAtLocation(node.name!)!;

    let v: Class = {
        name: {
            name: symbol.name,
            module: ctx.module.name
        },
        properties: [],
        methods: []
    }

    let _ctx = ctx.newContext({ isa: v })

    parseDoc(_ctx, v, symbol)

    if (node.modifiers) {
        node.modifiers.forEach((item) => {
            if (item.kind == ts.SyntaxKind.ExportKeyword) {
                v.name.export = true
            }
        })
    }

    if (node.heritageClauses) {
        for (let h of node.heritageClauses) {
            if (h.token == ts.SyntaxKind.ExtendsKeyword) {
                for (let t of h.types) {
                    let name = t.getText();
                    if (name.startsWith("jsc.")) {
                        break
                    }
                    let i = name.indexOf(".")
                    if (i >= 0) {
                        let m = _ctx.module.ref.get(name.substring(0, i))
                        let n = name.substring(i + 1)
                        if (m) {
                            for (let isa of m.classes) {
                                if (name == isa.name.name) {
                                    v.base = isa;
                                    break
                                }
                            }
                        }
                    } else {
                        for (let isa of _ctx.module.classes) {
                            if (name == isa.name.name) {
                                v.base = isa;
                                break
                            }
                        }
                    }
                    break
                }
                break
            }
        }
    }

    ctx.module.classes.push(v);

    node.forEachChild((item) => {
        if (ts.isPropertyDeclaration(item)) {
            let s = _ctx.checker.getSymbolAtLocation(item.name)!
            let p: Property = {
                name: {
                    name: s.name
                },
                type: parseVarType(ctx, { kind: TypeKind.VARIANT }, item.type)
            }
            p.type.property = true
            parseDoc(_ctx, p, s)
            v.properties.push(p)
        } else if (ts.isMethodDeclaration(item)) {
            let s = _ctx.checker.getSymbolAtLocation(item.name)!
            let p: Method = {
                name: {
                    name: s.name,
                    module: _ctx.module.name,
                    export: v.name.export
                },
                returnType: parseVarType(ctx, { kind: TypeKind.VOID }, item.type),
                arguments: parseArguments(ctx, item.parameters),
            }
            if (item.modifiers) {
                item.modifiers.forEach((item) => {
                    if (item.kind == ts.SyntaxKind.PrivateKeyword) {
                        v.name.export = false
                    }
                })
            }
            let c = _ctx.newContext({ scope: new Scope(), method: p })
            for (let a of p.arguments) {
                c.scope.set({ name: a.name, module: _ctx.module.name }, a.type)
            }
            p.body = parseBody(c, item.body)
            parseDoc(_ctx, p, s)
            v.methods.push(p)
        }
    })

}

export function parseConstExpression(ctx: Context, type: Type, s?: ts.Expression): string {
    if (s) {
        if (ts.isStringLiteral(s)) {
            return JSON.stringify(s.text)
        } else if (ts.isNumericLiteral(s)) {
            return s.text
        } else if (s.kind == ts.SyntaxKind.TrueKeyword) {
            return '1'
        } else if (s.kind == ts.SyntaxKind.FalseKeyword) {
            return '0'
        }
    }
    return toTypeDefaultValue(type)
}

export function parseModule(ctx: Context, module: SourceFileModule): void {

    let _ctx = ctx.newContext({ module: module, scope: new Scope(ctx.scope) })

    module.declare.forEachChild((node) => {

        if (ts.isFunctionDeclaration(node)) {
            parseFunction(_ctx, node)
        } else if (ts.isClassDeclaration(node)) {
            parseClass(_ctx, node)
        } else if (ts.isVariableStatement(node)) {
            for (let d of node.declarationList.declarations) {
                let s = _ctx.checker.getSymbolAtLocation(d.name)!
                let v: Var = {
                    name: { name: s.name, module: module.name },
                    type: parseVarType(_ctx, { kind: TypeKind.VARIANT }, d.type)
                }
                if (node.modifiers) {
                    node.modifiers.forEach((item) => {
                        if (item.kind == ts.SyntaxKind.ExportKeyword) {
                            v.name.export = true
                        } else if (item.kind == ts.SyntaxKind.ConstKeyword) {
                            v.initializer = parseConstExpression(_ctx, v.type, d.initializer)
                        }
                    })
                }

                if (v.type.kind == TypeKind.STRING && v.type.CString && !v.initializer) {
                    v.initializer = parseConstExpression(_ctx, v.type, d.initializer)
                }

                v.type.var = true
                parseDoc(_ctx, v, s)
                _ctx.scope.set(v.name, v.type)
                _ctx.module.vars.push(v)
            }
        }

    })

}

export function normalizeDirs(dirs: string[]): string[] {
    let i = 0;
    while (i < dirs.length) {
        let dir = dirs[i]
        if (dir == '' || dir == '.') {
            dirs.splice(i, 1)
        } else {
            i++
        }
    }
    return dirs
}

function walkFile(p: string, files: string[]): void {
    if (/\.jsc\.ts$/i.test(p)) {
        files.push(p);
    } else {
        let ts = fs.statSync(p);
        if (ts && ts.isDirectory()) {
            let items = fs.readdirSync(p);
            for (let item of items) {
                if (item.startsWith(".")) {
                    continue;
                }
                walkFile(path.join(p, item), files);
            }
        }
    }
}

export function parse(inDir: string, outDir: string, moduleName: string): void {

    let files: string[] = []
    let compilerOptions: ts.CompilerOptions = {
        target: ts.ScriptTarget.ES5,
        module: ts.ModuleKind.CommonJS,
        removeComments: false
    }

    if (fs.existsSync(path.join(inDir, "tsconfig.json"))) {
        let text = fs.readFileSync(path.join(inDir, "tsconfig.json")).toString().replace(/\/\/.*/g, '').replace(/\/\*.*\*\//g, '');
        console.log(text);
        let config = JSON.parse(text)
        if (config.files) {
            for (let f of config.files) {
                files.push(path.join(inDir, f))
            }
        }
        if (config.compilerOptions) {
            compilerOptions = config.compilerOptions
        }
    }

    walkFile(inDir, files)

    let program = ts.createProgram({
        rootNames: files,
        options: compilerOptions
    })

    let checker = program.getTypeChecker();

    let moduleSet = new Map<string, SourceFileModule>()

    let ctx = new Context({
        checker: checker,
        moduleSet: moduleSet,
        scope: new Scope()
    })

    let dirs = normalizeDirs(moduleName.split('/'))

    for (let sourceFile of program.getSourceFiles()) {

        if (sourceFile.fileName.endsWith(".jsc.ts")) {
            let r = path.relative(inDir, sourceFile.fileName)
            let basename = r.substring(0, r.length - 7)
            let name = path.basename(basename)
            let ds = normalizeDirs(dirs.concat(path.dirname(basename).split('/')))
            let module: SourceFileModule = {
                sourceFile: sourceFile,
                ref: new Map<string, Module>(),
                refClass: new Map<string, Class>(),
                refFunction: new Map<string, Function>(),
                refVar: new Map<string, Var>(),
                vars: [],
                name: {
                    dirs: ds.length > 0 ? ds : undefined,
                    name: name
                },
                includes: [],
                functions: [],
                classes: [],
                declare: sourceFile
            }
            moduleSet.set(toSymbolModulePath(module.name), module)
        }

    }

    moduleSet.forEach((item) => {
        parseModule(ctx, item)
        item.source = toSource(item)
    })

    moduleSet.forEach((item, name) => {
        if (item.source && !isEmptyModule(item)) {
            let p = path.join(outDir, name)
            mkdir(path.dirname(p))
            fs.writeFileSync(p + '.h', item.source.include_h)
            fs.writeFileSync(p + '.inc', item.source.include_c)
            fs.writeFileSync(p + '.c', item.source.implemented)
        }
    })
}