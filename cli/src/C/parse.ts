import * as ts from "typescript"
import * as fs from "fs"
import * as path from "path"
import { Source, toSource, toSymbolModule, toSymbolModulePath, toSymbolName, toType, toTypeDefaultValue } from "./source"
import { Module, Function, Type, Argument, Doc, Tag, Class, Property, Method, Body, Symbol, ModuleName, Scope, ScopeVar, TypeKinds, TypeKind, Var, isEmptyModule, Enum, EnumItem, Closures, ClosuresDeclare } from "./types"
import { baseClassSet, baseFunctionSet, getBaseClass, getBaseFunction, getBaseVar, getRefClass } from "./base"

var StringClass = baseClassSet.get('String')!
var ObjectClass = baseClassSet.get('Object')!
var ClosuresClass = baseClassSet.get('Closures')!

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
    returnType?: Type
    setArgumentCode?: string
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

    get returnType(): Type | undefined {
        if (this._options.returnType) {
            return this._options.returnType
        }
        if (this._parent) {
            return this._parent!.returnType
        }
    }

    get setArgumentCode(): string | undefined {
        if (this._options.setArgumentCode !== undefined) {
            return this._options.setArgumentCode
        }
        if (this._parent) {
            return this._parent!.setArgumentCode
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
                    return this.getClass(n, r)
                }
            }
        }
        return getBaseClass(name)
    }

    getEnum(name: string, m?: Module): Enum | undefined {
        if (m === undefined) {
            m = this.getModule()
        }
        if (m) {
            for (let v of m.enums) {
                if (v.name.name == name) {
                    return v
                }
            }
            {
                let v = m.refEnum.get(name)
                if (v) {
                    return v
                }
            }
            let i = name.indexOf('.')
            if (i >= 0) {
                let r = m.ref.get(name.substring(0, i))
                if (r) {
                    let n = name.substring(i + 1)
                    return this.getEnum(n, r)
                }
            }
        }
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
        return getBaseVar(name)
    }
}

export function mkdir(dir: string): void {
    if (!fs.existsSync(dir)) {
        mkdir(path.dirname(dir))
        fs.mkdirSync(dir)
    }
}

export function assignVarType(type: Type, fromType: Type, code: string): string {
    let t = type.isa == StringClass ? TypeKind.OBJECT : type.kind
    let f = fromType.isa == StringClass ? TypeKind.OBJECT : fromType.kind
    if (t == f) {
        return code
    }
    return `JSC_AS_${TypeKinds[t]}_${TypeKinds[f]}(${code})`
}

export function parseFunctionType(ctx: Context, s: ts.FunctionTypeNode): ClosuresDeclare {
    let v: Function = {
        name: {
            name: '__type',
            module: ctx.module.name,
        },
        returnType: parseVarType(ctx, { kind: TypeKind.VOID }, s.type),
        arguments: parseArguments(ctx, s.parameters)
    }
    return getClosuresDeclare(ctx, v);
}

export function parseStringType(ctx: Context, text: string): Type | undefined {
    switch (text) {
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
        case 'void':
            return { kind: TypeKind.VOID }
        case 'jsc.CString':
            return { kind: TypeKind.STRING, CString: true }
    }

    {
        let isa = getBaseClass(text)
        if (isa) {
            return { kind: TypeKind.OBJECT, isa: isa }
        }
    }

    {
        let v = getBaseVar(text)
        if (v) {
            return v.type
        }
    }

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

        if (ts.isArrayTypeNode(type)) {
            return {
                kind: TypeKind.OBJECT,
                isa: baseClassSet.get('Array')
            }
        }
        {
            let t = parseStringType(ctx, type.getText())
            if (t !== undefined) {
                return t
            }
        }

        console.info(type.getText())

        let t = ctx.checker.getTypeAtLocation(type)

        if (t.symbol && t.symbol.declarations) {
            for (let i of t.symbol.declarations) {
                if (ts.isFunctionTypeNode(i)) {
                    return {
                        kind: TypeKind.OBJECT,
                        isa: ClosuresClass,
                        closures: parseFunctionType(ctx, i)
                    }
                }
            }
        }

        let isa = ctx.getClass(type.getText().replace(/<.*>/g, ''));

        if (isa) {
            return { kind: TypeKind.OBJECT, isa: isa }
        }

        let e = ctx.getEnum(type.getText());

        if (e) {
            return e.type
        }

    }
    return defaultType
}

export function isStringType(t: Type): boolean {
    return t.kind == TypeKind.STRING || (t.kind == TypeKind.OBJECT && t.isa == StringClass)
}

let logicOpSet = new Set<string>(['==', '===', '!=', '!==', '>', '>=', '<', '<=', '&&', '||', 'instanceof'])

export function parseVarTypeWithExpression(ctx: Context, s: ts.Expression, defaultType: Type): Type {
    if (ts.isParenthesizedExpression(s)) {
        return parseVarTypeWithExpression(ctx, s.expression, defaultType);
    } else if (ts.isNewExpression(s)) {
        return parseVarTypeWithExpression(ctx, s.expression, defaultType);
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
    } else if (ts.isArrayLiteralExpression(s)) {
        return {
            kind: TypeKind.OBJECT,
            isa: baseClassSet.get('Array')
        }
    } else if (ts.isPropertyAccessExpression(s)) {
        let text = s.getText()
        let t = parseStringType(ctx, text)
        if (t !== undefined) {
            return t
        }
        let aType = parseVarTypeWithExpression(ctx, s.expression, defaultType);
        if (aType.kind == TypeKind.OBJECT && aType.isa) {
            let p = getClassWithProperty(s.name.text, getRefClass(aType.isa))
            if (p) {
                return p.prop.type
            }
        } else if (aType.enum) {
            for (let item of aType.enum.items) {
                if (item.name == s.name.text) {
                    return aType
                }
            }
        }
        return defaultType
    } else if (ts.isCallExpression(s)) {
        let text = s.expression.getText();
        let baseFunc = getBaseFunction(text)
        if (baseFunc) {
            return baseFunc.returnType
        }
        if (ts.isPropertyAccessExpression(s.expression)) {
            let aType = parseVarTypeWithExpression(ctx, s.expression.expression, { kind: TypeKind.NIL });
            if (aType.kind == TypeKind.OBJECT) {
                let name = s.expression.name.text
                let m = getClassWithMethod(name, getRefClass(aType.isa))
                if (m) {
                    return m.method.returnType
                }
            }
        }
        return defaultType
    } else if (s.kind == ts.SyntaxKind.ThisKeyword) {
        if (ctx.isa) {
            return {
                kind: TypeKind.OBJECT,
                isa: ctx.isa
            }
        }
    } else if (s.kind == ts.SyntaxKind.SuperKeyword) {
        if (ctx.isa) {
            return {
                kind: TypeKind.OBJECT,
                isa: ctx.isa.base || ObjectClass
            }
        }
    } else if (s.kind == ts.SyntaxKind.TrueKeyword || s.kind == ts.SyntaxKind.FalseKeyword) {
        return { kind: TypeKind.BOOLEAN }
    } else if (s.kind == ts.SyntaxKind.UndefinedKeyword || s.kind == ts.SyntaxKind.NullKeyword) {
        return { kind: TypeKind.NIL }
    } else if (ts.isArrayLiteralExpression(s)) {
        return { kind: TypeKind.OBJECT, isa: baseClassSet.get('Array') }
    } else if (ts.isIdentifier(s)) {

        let text = s.text

        if (text == 'undefined' || text == 'null') {
            return { kind: TypeKind.NIL }
        } else if (text == 'true' || text == 'false') {
            return { kind: TypeKind.BOOLEAN }
        }

        {
            let v = ctx.scope.get(text)
            if (v) {
                return v.type
            }
        }

        {
            let v = ctx.getVar(text)
            if (v) {
                return v.type
            }
        }

        {
            let v = ctx.getClass(s.text.replace(/<.*>/g, ''))
            if (v) {
                return {
                    kind: TypeKind.OBJECT,
                    isa: v
                }
            }
        }

        {
            let v = ctx.getEnum(text)
            if (v) {
                return v.type
            }
        }

    } else if (ts.isConditionalExpression(s)) {
        return parseVarTypeWithExpression(ctx, s.whenTrue, defaultType)
    } else if (ts.isArrowFunction(s)) {
        return {
            kind: TypeKind.OBJECT,
            isa: ClosuresClass,
            closures: (s as any).__closures.declare
        }
    }

    console.error(s)
    debugger
    throw new Error(s.getText())
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

export function getClassWithProperty(prop: string, isa?: Class): { isa: Class, prop: Property } | undefined {
    if (isa) {
        for (let i of isa.properties) {
            if (i.name.name == prop) {
                return {
                    isa: isa,
                    prop: i
                }
            }
        }
        return getClassWithProperty(prop, isa.base)
    } else {
        for (let i of ObjectClass.properties) {
            if (i.name.name == prop) {
                return {
                    isa: ObjectClass,
                    prop: i,
                }
            }
        }
    }
}

export function parseCallArguments(ctx: Context, args: ts.NodeArray<ts.Expression> | undefined, func: Function, vs: string[] = [], funcIndex: number = 0): string {
    let i = 0;
    while (i + funcIndex < func.arguments.length) {
        let a = func.arguments[i + funcIndex];
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
                            vs.push(`${assignVarType({ kind: t }, v, parseExpression(ctx, args[i]))}`)
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
            vs.push(`${assignVarType(a.type, v, parseExpression(ctx, args[i]))}`)
        } else {
            vs.push(toTypeDefaultValue(a.type))
        }
        i++;
    }
    return vs.join(',')
}

export function getSetType(t: Type): { isStrong: boolean, isWeak: boolean, isVariant: boolean, type: Type } {
    if ((t.var || t.property) && t.kind == TypeKind.STRING && !t.CString) {
        return {
            isStrong: true,
            isWeak: t.weak ? true : false,
            isVariant: false,
            type: {
                kind: TypeKind.OBJECT,
                isa: StringClass,
            }
        }
    }
    return {
        isStrong: t.kind == TypeKind.OBJECT || t.kind == TypeKind.VARIANT,
        isWeak: t.weak ? true : false,
        isVariant: t.kind == TypeKind.VARIANT,
        type: t
    }
}


export function parseExpression(ctx: Context, s: ts.Expression): string {

    if (ts.isParenthesizedExpression(s)) {
        return `(${parseExpression(ctx, s.expression)})`
    } else if (ts.isCallExpression(s)) {
        let text = s.expression.getText();
        let baseFunc = getBaseFunction(text)
        if (baseFunc) {
            return `jsc_${toSymbolName(baseFunc.name)}(${parseCallArguments(ctx, s.arguments, baseFunc)})`
        }
        if (ts.isPropertyAccessExpression(s.expression)) {
            let aType = parseVarTypeWithExpression(ctx, s.expression.expression, { kind: TypeKind.NIL });
            if (aType.kind == TypeKind.OBJECT) {
                let name = s.expression.name.text
                let m = getClassWithMethod(name, getRefClass(aType.isa))
                if (m && m.isa == ObjectClass) {
                    return `jsc_object_${name}_((jsc_class_t *)&jsc_Object,${parseExpression(ctx, s.expression.expression)}${parseCallArguments(ctx, s.arguments, m.method, [''])})`
                } else if (m && m.isa) {
                    return `jsc_${toSymbolName(m.isa.name)}_${name}_((jsc_class_t *)&jsc_${toSymbolName(m.isa.name)},${parseExpression(ctx, s.expression.expression)}${parseCallArguments(ctx, s.arguments, m.method, [''])})`
                }
            }
        } else if (s.expression.kind == ts.SyntaxKind.SuperKeyword && ctx.isa && ctx.isa.base && ctx.isa.base.new) {
            let init: Method | undefined
            for (let m of ctx.isa.base.methods) {
                if (m.name.name == '__init') {
                    init = m
                    break
                }
            }
            if (init) {
                return `jsc_${toSymbolName(ctx.isa.base.name)}_${init.name.name}_((jsc_class_t *)&jsc_${toSymbolName(ctx.isa.name)},__object${parseCallArguments(ctx, s.arguments, init, [''])})`
            }
        } else {
            let text = s.expression.getText()
            let v = ctx.scope.get(text)
            if (v && v.type.kind == TypeKind.OBJECT && v.type.isa == ClosuresClass && v.type.closures) {
                let closures = v.type.closures!
                return `(*(jsc_${toSymbolName(closures.name)}_t)((jsc_Closures_t *)${v.name.name})->imp)(${v.name.name}${parseCallArguments(ctx, s.arguments, closures, [''], 1)})`
            }
        }

    } else if (ts.isPropertyAccessExpression(s)) {
        let text = s.getText()
        {
            let v = getBaseVar(text)
            if (v) {
                return `jsc_${toSymbolName(v.name)}`
            }
        }
        let aType = parseVarTypeWithExpression(ctx, s.expression, { kind: TypeKind.NIL });
        if (aType.kind == TypeKind.OBJECT) {
            let name = s.name.text
            let p = getClassWithProperty(name, getRefClass(aType.isa))
            if (p && p.isa) {

                let objectCode = parseExpression(ctx, s.expression)

                if (ctx.setArgumentCode !== undefined) {
                    if (p.prop.setter) {
                        return `jsc_${toSymbolName(p.isa.name)}_${p.prop.setter}(${objectCode},${ctx.setArgumentCode})`
                    } else {
                        let r = getSetType(p.prop.type)
                        let dst = `((jsc_${toSymbolName(p.isa.name)}_t *)(${objectCode}))->${name}`
                        if (r.isStrong && r.isWeak) {
                            return `jsc_${r.isVariant ? 'variant_' : ''}setWeak(&(${dst}),${ctx.setArgumentCode})`
                        } else if (r.isStrong) {
                            return `jsc_${r.isVariant ? 'variant_' : ''}setStrong(&(${dst}),${ctx.setArgumentCode})`
                        } else {
                            return `${dst} = ${ctx.setArgumentCode}`
                        }
                    }
                } else {
                    if (p.prop.getter) {
                        return `jsc_${toSymbolName(p.isa.name)}_${p.prop.getter}(${objectCode})`
                    }
                    return `((jsc_${toSymbolName(p.isa.name)}_t *)(${objectCode}))->${name}`
                }

            }
        } else if (aType.enum) {
            let name = s.name.text
            for (let item of aType.enum.items) {
                if (name == item.name) {
                    return `jsc_${toSymbolName(aType.enum.name)}_${name}`
                }
            }
        }
    } else if (ts.isStringLiteral(s)) {
        return JSON.stringify(s.text)
    } else if (ts.isNumericLiteral(s)) {
        return s.text
    } else if (ts.isBinaryExpression(s)) {
        let op: string = s.operatorToken.getText()
        let aType = parseVarTypeWithExpression(ctx, s.left, { kind: TypeKind.STRING })
        let bType = parseVarTypeWithExpression(ctx, s.right, { kind: TypeKind.STRING })

        if (op == 'instanceof') {
            let isa = ctx.getClass(s.right.getText())
            if (isa) {
                let a = assignVarType({ kind: TypeKind.OBJECT }, aType, parseExpression(ctx, s.left))
                return `jsc_object_isKind(${a},(jsc_class_t *) &jsc_${toSymbolName(isa.name)})`
            } else {
                console.info(s)
                debugger
                throw new Error(s.getText())
            }
        }

        if (op == '=') {

            let r = getSetType(aType)

            let bCode = `${assignVarType(r.type, bType, parseExpression(ctx, s.right))}`

            if (ts.isPropertyAccessExpression(s.left)) {
                return parseExpression(ctx.newContext({ setArgumentCode: bCode }), s.left)
            } else {

                let dst = parseExpression(ctx, s.left)

                if (r.isStrong && r.isWeak) {
                    return `jsc_${r.isVariant ? 'variant_' : ''}setWeak(&(${dst}),${bCode})`
                } else if (r.isStrong) {
                    return `jsc_${r.isVariant ? 'variant_' : ''}setStrong(&(${dst}),${bCode})`
                } else {
                    return `${dst} = ${bCode}`
                }
            }

        }

        if (isStringType(aType) || isStringType(bType)) {
            if (op == '===') {
                op = '=='
            } else if (op == '!==') {
                op = '!='
            }
            if (op == '==' || op == '!=' || op == '<' || op == '<=' || op == '>' || op == '>=') {
                return `JSC_STRING_COMP(${assignVarType({ kind: TypeKind.STRING }, aType, parseExpression(ctx, s.left))},${assignVarType({ kind: TypeKind.STRING }, bType, parseExpression(ctx, s.right))}) ${op} 0`
            } else if (op == '+') {
                return `JSC_STRING_ADD(${assignVarType({ kind: TypeKind.STRING }, aType, parseExpression(ctx, s.left))},${assignVarType({ kind: TypeKind.STRING }, bType, parseExpression(ctx, s.right))})`
            } else {
                debugger
                throw new Error(s.getText())
            }
        }

        if (aType.kind == TypeKind.VARIANT || bType.kind == TypeKind.VARIANT) {
            let a = assignVarType({ kind: TypeKind.VARIANT }, aType, parseExpression(ctx, s.left))
            let b = assignVarType({ kind: TypeKind.VARIANT }, bType, parseExpression(ctx, s.right))
            if (op == '===') {
                return `jsc_variant_strict_compare(${a},${b}) == 0`
            } else if (op == '!==') {
                return `jsc_variant_strict_compare(${a},${b}) != 0`
            } else if (op == '==' || op == '!=' || op == '<' || op == '<=' || op == '>' || op == '>=') {
                return `jsc_variant_strict_compare(${a},${b}) ${op} 0`
            } else if (op == '+') {
                return `jsc_variant_add(${a},${b})`
            } else if (op == '-') {
                return `jsc_variant_sub(${a},${b})`
            } else if (op == '*') {
                return `jsc_variant_mul(${a},${b})`
            } else if (op == '/') {
                return `jsc_variant_div(${a},${b})`
            } else if (op == '%') {
                return `jsc_variant_mod(${a},${b})`
            } else if (op == '&') {
                return `jsc_variant_bit_and(${a},${b})`
            } else if (op == '|') {
                return `jsc_variant_bit_or(${a},${b})`
            } else if (op == '^') {
                return `jsc_variant_bit_xor(${a},${b})`
            } else {
                console.info(s)
                debugger
                throw new Error(s.getText())
            }
        }

        if (aType.kind < bType.kind) {
            return `${assignVarType(bType, aType, parseExpression(ctx, s.left))}${op}${parseExpression(ctx, s.right)}`
        }
        return `${parseExpression(ctx, s.left)}${op}${assignVarType(aType, bType, parseExpression(ctx, s.right))}`
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
                    return `${s.operand.text}++`
                case ts.SyntaxKind.MinusMinusToken:
                    return `${s.operand.text}--`
            }
        }
    } else if (ts.isNewExpression(s)) {
        let aType = parseVarTypeWithExpression(ctx, s.expression, { kind: TypeKind.OBJECT });
        let isa = getRefClass(aType.isa)
        if (aType.kind == TypeKind.OBJECT && isa) {
            if (isa.new) {
                return `(jsc_object_t *) jsc_${toSymbolName(isa.name)}_${isa.new.name.name}(${parseCallArguments(ctx, s.arguments, isa.new)})`;
            }
            return `jsc_object_new((jsc_class_t*)&jsc_${toSymbolName(isa.name)},0)`
        }
    } else if (ts.isIdentifier(s)) {
        if (s.text == 'undefined' || s.text == 'null') {
            return 'NULL'
        }
        {
            let v = ctx.getVar(s.text)
            if (v) {
                return `jsc_${toSymbolName(v.name)}`
            }
        }
        return s.text;
    } else if (s.kind == ts.SyntaxKind.FalseKeyword) {
        return '0'
    } else if (s.kind == ts.SyntaxKind.TrueKeyword) {
        return '1'
    } else if (s.kind == ts.SyntaxKind.UndefinedKeyword || s.kind == ts.SyntaxKind.NullKeyword) {
        return 'NULL'
    } else if (s.kind == ts.SyntaxKind.ThisKeyword || s.kind == ts.SyntaxKind.SuperKeyword) {
        return '__object'
    } else if (ts.isArrayLiteralExpression(s)) {
        let ss = `jsc_object_new((jsc_class_t *) &jsc_Array,0)`
        for (let a of s.elements) {
            let aType = parseVarTypeWithExpression(ctx, a, { kind: TypeKind.VARIANT })
            ss = `jsc_object_add(${ss},${assignVarType({ kind: TypeKind.VARIANT }, aType, parseExpression(ctx, a))})`
        }
        return ss
    } else if (ts.isConditionalExpression(s)) {
        return `${parseExpression(ctx, s.condition)} ? ${parseExpression(ctx, s.whenTrue)} : ${parseExpression(ctx, s.whenFalse)}`
    } else if (ts.isArrowFunction(s)) {

        if ((s as any).__closures) {
            let closures: Closures = (s as any).__closures
            parseClosures(ctx, s.body, closures)
            let vs: string[] = []
            vs.push(`(jsc_object_t *) jsc_Closures_new((void *) jsc_${toSymbolName(closures.func.name)}`)
            for (let key of closures.keys) {
                let t = closures.get(key)!
                let kind = t.kind
                let weak = t.weak
                if (kind == TypeKind.STRING && !t.CString) {
                    kind = TypeKind.OBJECT
                    weak = false
                }
                vs.push(`,JSC_VARIANT_TYPE_${TypeKinds[kind]},${weak ? 1 : 0},&${key}`)
            }
            vs.push(`,0x0ff)`)
            return vs.join('')
        }

    }

    debugger
    throw new Error(s.getText())
}

export function parseClosures(ctx: Context, s: ts.ConciseBody, closures: Closures): void {
    
}


export function parseStatement(ctx: Context, s: ts.Statement, level: number): string {

    if (ts.isExpressionStatement(s)) {
        return `${parseExpression(ctx, s.expression)};`;
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
        vs.push(';')
        return vs.join('')
    } else if (ts.isReturnStatement(s)) {
        if (s.expression) {
            if (ctx.returnType) {
                let aType = parseVarTypeWithExpression(ctx, s.expression, ctx.returnType)
                return `return ${assignVarType(ctx.returnType, aType, parseExpression(ctx, s.expression))};`
            }
            return `return ${parseExpression(ctx, s.expression)};`
        }
        return 'return;'
    } else if (ts.isIfStatement(s)) {
        let vs: string[] = []
        vs.push(`if(${parseExpression(ctx, s.expression)}) ${parseStatement(ctx, s.thenStatement, level)}`)
        if (s.elseStatement) {
            vs.push(`else ${parseStatement(ctx, s.elseStatement, level)}`)
        }
        return vs.join('')
    } else if (ts.isBlock(s)) {
        let vs: string[] = []
        vs.push("{\n")
        for (let e of s.statements) {
            vs.push(`${"\t".repeat(level + 1)}${parseStatement(ctx, e, level + 1)}\n`)
        }
        vs.push(`${"\t".repeat(level)}}\n${"\t".repeat(level)}`)
        return vs.join('')
    } else if (ts.isWhileStatement(s)) {
        return `while(${parseExpression(ctx, s.expression)}) ${parseStatement(ctx, s.statement, level)}`
    } else if (ts.isBreakStatement(s)) {
        return `break;`
    } else if (ts.isSwitchStatement(s)) {
        let vs: string[] = [];
        vs.push(`switch(${parseExpression(ctx, s.expression)}) {\n`)
        for (let i of s.caseBlock.clauses) {
            if (ts.isCaseClause(i)) {
                vs.push(`${"\t".repeat(level)}case ${parseExpression(ctx, i.expression)}:\n`)
                for (let ss of i.statements) {
                    vs.push(`${"\t".repeat(level + 1)}${parseStatement(ctx, ss, level + 1)}\n`)
                }
            } else if (ts.isDefaultClause(i)) {
                vs.push(`${"\t".repeat(level)}default :\n`)
                for (let ss of i.statements) {
                    vs.push(`${"\t".repeat(level + 1)}${parseStatement(ctx, ss, level + 1)}\n`)
                }
            }
        }
        vs.push(`${"\t".repeat(level)}}\n${"\t".repeat(level)}`)
        return vs.join('')
    }

    debugger

    throw new Error(s.getText() + ' kind:' + s.kind)

}

export function getClosuresDeclare(ctx: Context, func: Function, ex: boolean = false): ClosuresDeclare {
    let ns: string[] = ['closures', 'declare']
    ns.push(func.returnType.kind + '')
    for (let i of func.arguments) {
        ns.push(i.type.kind + '')
    }
    let key = ns.join('_')
    for (let d of ctx.module.closureses) {
        if (d.name.name == key) {
            d.name.export = d.name.export || ex
            return d
        }
    }
    let r: ClosuresDeclare = {
        name: {
            name: key,
            module: ctx.module.name,
            export: ex
        },
        returnType: func.returnType,
        arguments: func.arguments
    }
    ctx.module.closureses.push(r)
    return r
}

export function scanningClosuresExpression(ctx: Context, s: ts.Expression): void {

    if (ts.isParenthesizedExpression(s)) {
        scanningClosuresExpression(ctx, s.expression)
    } else if (ts.isCallExpression(s)) {
        scanningClosuresExpression(ctx, s.expression)
        for (let a of s.arguments) {
            scanningClosuresExpression(ctx, a)
        }
    } else if (ts.isPropertyAccessExpression(s)) {
        scanningClosuresExpression(ctx, s.expression)
    } else if (ts.isStringLiteral(s)) {
    } else if (ts.isNumericLiteral(s)) {
    } else if (ts.isBinaryExpression(s)) {
        scanningClosuresExpression(ctx, s.left)
        scanningClosuresExpression(ctx, s.right)
    } else if (ts.isPrefixUnaryExpression(s)) {
    } else if (ts.isPostfixUnaryExpression(s)) {
    } else if (ts.isNewExpression(s)) {
        scanningClosuresExpression(ctx, s.expression)
        if (s.arguments) {
            for (let a of s.arguments) {
                scanningClosuresExpression(ctx, a)
            }
        }
    } else if (ts.isIdentifier(s)) {
    } else if (s.kind == ts.SyntaxKind.FalseKeyword) {
    } else if (s.kind == ts.SyntaxKind.TrueKeyword) {
    } else if (s.kind == ts.SyntaxKind.UndefinedKeyword || s.kind == ts.SyntaxKind.NullKeyword) {
    } else if (s.kind == ts.SyntaxKind.ThisKeyword || s.kind == ts.SyntaxKind.SuperKeyword) {
    } else if (ts.isArrayLiteralExpression(s)) {
        for (let a of s.elements) {
            scanningClosuresExpression(ctx, a)
        }
    } else if (ts.isConditionalExpression(s)) {
        scanningClosuresExpression(ctx, s.condition)
        scanningClosuresExpression(ctx, s.whenTrue)
        scanningClosuresExpression(ctx, s.whenFalse)
    } else if (ts.isArrowFunction(s)) {

        let func: Function = {
            name: {
                name: `closures_${ctx.module.functions.length}`,
                module: ctx.module.name,
                export: false
            },
            returnType: parseVarType(ctx, { kind: TypeKind.VOID }, s.type),
            arguments: parseArguments(ctx, s.parameters),
        };

        func.arguments.unshift({ name: '__closures', type: { kind: TypeKind.OBJECT, isa: ClosuresClass } });

        func.closures = getClosuresDeclare(ctx, func);

        (s as any).__closures = new Closures(func, func.closures)

        ctx.module.functions.push(func)

        if (ts.isBlock(s.body)) {
            for (let ss of s.body.statements) {
                scanningClosuresStatement(ctx, ss)
            }
        } else {
            scanningClosuresExpression(ctx, s.body)
        }

    }
}

export function scanningClosuresStatement(ctx: Context, s: ts.Statement): void {

    if (ts.isExpressionStatement(s)) {
        scanningClosuresExpression(ctx, s.expression)
    } else if (ts.isVariableStatement(s)) {
        for (let i of s.declarationList.declarations) {
            if (i.initializer) {
                scanningClosuresExpression(ctx, i.initializer)
            }
        }
    } else if (ts.isReturnStatement(s)) {
        if (s.expression) {
            scanningClosuresExpression(ctx, s.expression)
        }
    } else if (ts.isIfStatement(s)) {
        scanningClosuresExpression(ctx, s.expression)
        scanningClosuresStatement(ctx, s.thenStatement)
        if (s.elseStatement) {
            scanningClosuresStatement(ctx, s.elseStatement)
        }
    } else if (ts.isBlock(s)) {
        for (let e of s.statements) {
            scanningClosuresStatement(ctx, e)
        }
    } else if (ts.isWhileStatement(s)) {
        scanningClosuresExpression(ctx, s.expression)
        scanningClosuresStatement(ctx, s.statement)
    } else if (ts.isBreakStatement(s)) {
    } else if (ts.isSwitchStatement(s)) {
        scanningClosuresExpression(ctx, s.expression)
        let vs: string[] = [];
        vs.push(`switch(${parseExpression(ctx, s.expression)}) {\n`)
        for (let i of s.caseBlock.clauses) {
            for (let ss of i.statements) {
                scanningClosuresStatement(ctx, ss)
            }
        }
    }

}

export function scanningClosures(ctx: Context, body: ts.FunctionBody): void {

    for (let s of body.statements) {
        scanningClosuresStatement(ctx, s)
    }

}

export function parseBody(ctx: Context, node?: ts.FunctionBody): Body | undefined {
    if (node) {
        let _ctx = ctx.newContext({ scope: new Scope(ctx.scope) })
        scanningClosures(_ctx, node)
        return (level: number = 0): string => {
            let vs: string[] = []
            for (let s of node.statements) {
                vs.push(`${"\t".repeat(level)}${parseStatement(_ctx, s, level)}\n`)
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

    let c = ctx.newContext({ scope: new Scope(ctx.scope), returnType: v.returnType })

    for (let a of v.arguments) {
        c.scope.set({ name: a.name, module: ctx.module.name }, a.type)
    }

    v.body = parseBody(c, node.body)

    parseDoc(ctx, v, symbol)

    if (node.modifiers) {
        node.modifiers.forEach((item) => {
            if (item.kind == ts.SyntaxKind.ExportKeyword) {
                v.name.export = true

                if (v.returnType.closures) {
                    v.returnType.closures.name.export = true
                }

                for (let i of v.arguments) {
                    if (i.type.closures) {
                        i.type.closures.name.export = true
                    }
                }
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
                                if (n == isa.name.name) {
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
            if (v.name.export) {

                if (p.returnType.closures) {
                    p.returnType.closures.name.export = true
                }

                for (let i of p.arguments) {
                    if (i.type.closures) {
                        i.type.closures.name.export = true
                    }
                }
            }
            let c = _ctx.newContext({ scope: new Scope(), method: p, returnType: p.returnType })
            for (let a of p.arguments) {
                c.scope.set({ name: a.name, module: _ctx.module.name }, a.type)
            }
            p.body = parseBody(c, item.body)
            parseDoc(_ctx, p, s)
            v.methods.push(p)
        } else if (ts.isConstructorDeclaration(item)) {
            let p: Method = {
                name: {
                    name: '__init',
                    module: _ctx.module.name,
                    export: v.name.export
                },
                returnType: { kind: TypeKind.VOID },
                arguments: parseArguments(ctx, item.parameters)
            }
            let c = _ctx.newContext({ scope: new Scope(), method: p, returnType: p.returnType })
            for (let a of p.arguments) {
                c.scope.set({ name: a.name, module: _ctx.module.name }, a.type)
            }
            p.body = parseBody(c, item.body)
            v.methods.push(p)

            v.new = {
                name: {
                    name: 'new',
                    module: _ctx.module.name,
                    export: v.name.export
                },
                returnType: { kind: TypeKind.OBJECT, isa: v },
                arguments: parseArguments(ctx, item.parameters)
            }
        }
    })

}

export function parseConstExpression(ctx: Context, type: Type, doc: Doc, s?: ts.Expression): string {
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
    if (doc.tags) {
        for (let t of doc.tags) {
            if (t.name == 'value' && t.value) {
                return t.value
            }
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

                parseDoc(_ctx, v, s)

                if (node.modifiers) {
                    node.modifiers.forEach((item) => {
                        if (item.kind == ts.SyntaxKind.ExportKeyword) {
                            v.name.export = true
                        } else if (item.kind == ts.SyntaxKind.ConstKeyword) {
                            v.initializer = parseConstExpression(_ctx, v.type, v, d.initializer)
                        }
                    })
                }

                if (!v.initializer) {
                    if (d.initializer) {
                        v.initializer = parseExpression(ctx, d.initializer)
                    } else {
                        v.initializer = parseConstExpression(_ctx, v.type, v, d.initializer)
                    }
                }

                v.type.var = true
                _ctx.scope.set(v.name, v.type)
                _ctx.module.vars.push(v)
            }
        } else if (ts.isEnumDeclaration(node)) {
            let s = _ctx.checker.getSymbolAtLocation(node.name)!
            let v: Enum = {
                name: { name: s.name, module: module.name },
                type: { kind: TypeKind.UINT8 },
                items: []
            }

            v.type.enum = v

            if (node.members.length > 0x10000) {
                v.type.kind = TypeKind.UINT32
            } else if (node.members.length > 0x100) {
                v.type.kind = TypeKind.UINT16
            }

            parseDoc(_ctx, v, s)

            for (let i of node.members) {
                let ss = _ctx.checker.getSymbolAtLocation(i.name)!
                let item: EnumItem = {
                    name: ss.name,
                }
                parseDoc(_ctx, item, ss)
                v.items.push(item)
            }

            _ctx.module.enums.push(v)
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
                refEnum: new Map<string, Enum>(),
                enums: [],
                vars: [],
                name: {
                    dirs: ds.length > 0 ? ds : undefined,
                    name: name
                },
                includes: [],
                functions: [],
                closureses: [],
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