import * as ts from "typescript"
import * as fs from "fs"
import * as path from "path"
import { Source, toSource, toSymbolName } from "./source"
import { Module, Function, Type, Argument, Doc, Tag, Class, Property, Method, Body, Symbol, ModuleName } from "./types"


interface SourceFileModule extends Module {
    sourceFile: ts.SourceFile
    source?: Source
}

export function mkdir(dir: string): void {
    if (!fs.existsSync(dir)) {
        mkdir(path.dirname(dir))
        fs.mkdirSync(dir)
    }
}

export function parseType(defaultType: Type, type?: ts.TypeNode): Type {
    if (type) {
        switch (type.getText()) {

        }
    }
    return defaultType
}

export function parseArguments(args: ts.NodeArray<ts.ParameterDeclaration>): Argument[] {
    let vs: Argument[] = []
    args.forEach((item) => {
        vs.push({
            name: item.name.getText(),
            type: parseType(Type.VARIANT, item.type)
        })
    })
    return vs
}

export function parseDoc(checker: ts.TypeChecker, doc: Doc, symbol: ts.Symbol): void {
    doc.title = ts.displayPartsToString(symbol.getDocumentationComment(checker));
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

export function parseExpressionArguments(checker: ts.TypeChecker, module: SourceFileModule, moduleSet: Map<string, SourceFileModule>, s: ts.NodeArray<ts.Expression>, isa?: Class, method?: Method, dot?: boolean): string {

    let vs: string[] = []

    if (dot) {
        vs.push('')
    }

    s.forEach((item) => {
        vs.push(parseExpression(checker, module, moduleSet, item, isa, method))
    })

    return vs.join(',')
}

export function getObjectSymbol(checker: ts.TypeChecker, module: SourceFileModule, moduleSet: Map<string, SourceFileModule>, s: ts.Expression, isa?: Class, method?: Method): Symbol {

    if (s.kind == ts.SyntaxKind.SuperKeyword) {
        return {
            name: 'super'
        }
    }

    if (s.kind == ts.SyntaxKind.ThisKeyword) {
        return {
            name: 'this'
        }
    }

    console.info(s)
    debugger
    throw new Error(`getObjectSymbol kind:${s.kind}`)
}

export function parseExpression(checker: ts.TypeChecker, module: SourceFileModule, moduleSet: Map<string, SourceFileModule>, s: ts.Expression, isa?: Class, method?: Method): string {

    if (ts.isCallExpression(s)) {
        if (s.expression.getText() == 'jsc.log') {
            return `jsc_log(${parseExpressionArguments(checker, module, moduleSet, s.arguments, isa, method)})`
        } else if (ts.isPropertyAccessExpression(s.expression)) {
            let name = getObjectSymbol(checker, module, moduleSet, s.expression.expression, isa, method);
            if (name.name == 'super') {
                if (isa) {
                    return `jsc_${isa.base ? toSymbolName(isa.base.name) : 'object'}_${s.expression.name.text}_((jsc_class_t *)&jsc_${isa.base ? toSymbolName(isa.base.name) : 'Object'},__object${parseExpressionArguments(checker, module, moduleSet, s.arguments, isa, method)})`
                }
            } else if (name.name == 'this') {
                if (isa) {
                    return `jsc_${toSymbolName(isa.name)}_${s.expression.name.text}_(__isa,__object${parseExpressionArguments(checker, module, moduleSet, s.arguments, isa, method)})`
                }
            }

        }
    } else if (ts.isStringLiteral(s)) {
        return JSON.stringify(s.text)
    }

    console.info(s)
    debugger
    throw new Error(`parseExpression kind:${s.kind}`)
}

export function parseStatement(checker: ts.TypeChecker, module: SourceFileModule, moduleSet: Map<string, SourceFileModule>, s: ts.Statement, isa?: Class, method?: Method): string {

    if (ts.isExpressionStatement(s)) {
        return parseExpression(checker, module, moduleSet, s.expression, isa, method);
    }

    throw new Error(`parseStatement kind:${s.kind}`)

}

export function parseBody(checker: ts.TypeChecker, module: SourceFileModule, moduleSet: Map<string, SourceFileModule>, node?: ts.FunctionBody, isa?: Class, method?: Method): Body | undefined {
    if (node) {
        return (level: number = 0): string => {
            let vs: string[] = []
            for (let s of node.statements) {
                vs.push(`${"\t".repeat(level)}${parseStatement(checker, module, moduleSet, s, isa, method)};\n`)
            }
            return vs.join('')
        }
    }
}

export function parseFunction(checker: ts.TypeChecker, module: SourceFileModule, moduleSet: Map<string, SourceFileModule>, node: ts.FunctionDeclaration): void {

    let symbol = checker.getSymbolAtLocation(node.name!)!;

    let v: Function = {
        name: {
            name: symbol.name,
            module: module.name
        },
        returnType: parseType(Type.VOID, node.type),
        arguments: parseArguments(node.parameters),
        body: parseBody(checker, module, moduleSet, node.body)
    }

    parseDoc(checker, v, symbol)

    if (node.modifiers) {
        node.modifiers.forEach((item) => {
            if (item.kind == ts.SyntaxKind.ExportKeyword) {
                v.name.export = true
            }
        })
    }

    module.functions.push(v)

}

export function parseClass(checker: ts.TypeChecker, module: SourceFileModule, moduleSet: Map<string, SourceFileModule>, node: ts.ClassDeclaration): void {

    let symbol = checker.getSymbolAtLocation(node.name!)!;

    let v: Class = {
        name: {
            name: symbol.name,
            module: module.name
        },
        properties: [],
        methods: []
    }

    parseDoc(checker, v, symbol)

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
                        let m = module.ref.get(name.substring(0,i))
                        let n = name.substring(i+1)
                        if(m) {
                            for (let isa of m.classes) {
                                if (name == isa.name.name) {
                                    v.base = isa;
                                    break
                                }
                            }
                        }
                    } else {
                        for (let isa of module.classes) {
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

    node.forEachChild((item) => {
        if (ts.isPropertyDeclaration(item)) {
            let s = checker.getSymbolAtLocation(item.name)!
            let p: Property = {
                name: {
                    name: symbol.name
                },
                type: parseType(Type.VARIANT, item.type)
            }
            parseDoc(checker, p, s)
            v.properties.push(p)
        } else if (ts.isMethodDeclaration(item)) {
            let s = checker.getSymbolAtLocation(item.name)!
            let p: Method = {
                name: {
                    name: symbol.name,
                    module: module.name
                },
                returnType: parseType(Type.VOID, item.type),
                arguments: parseArguments(item.parameters),
            }
            p.body = parseBody(checker, module, moduleSet, item.body, v, p)
            parseDoc(checker, p, s)
            v.methods.push(p)
        }
    })

    module.classes.push(v);

}

export function parseModule(checker: ts.TypeChecker, module: SourceFileModule, moduleSet: Map<string, SourceFileModule>): void {

    module.sourceFile.forEachChild((node) => {

        if (ts.isFunctionDeclaration(node)) {
            parseFunction(checker, module, moduleSet, node)
        } else if (ts.isClassDeclaration(node)) {
            parseClass(checker, module, moduleSet, node)
        }

    })

    module.source = toSource(module)
}

export function parse(inFile: string, outDir: string, moduleName: string): void {

    let program = ts.createProgram({
        rootNames: [inFile],
        options: {
            target: ts.ScriptTarget.ES5,
            module: ts.ModuleKind.CommonJS,
            removeComments: false
        }
    })

    let checker = program.getTypeChecker();

    let dirname = path.dirname(inFile)

    let moduleSet = new Map<string, SourceFileModule>()

    for (let sourceFile of program.getSourceFiles()) {

        if (sourceFile.fileName.endsWith(".jsc.ts")) {
            let r = path.relative(dirname, sourceFile.fileName)
            let basename = r.substring(0, r.length - 7)
            let name = path.join(moduleName, basename)
            let dirs = path.dirname(name).split('/')
            let i = 0;
            while (i < dirs.length) {
                let dir = dirs[i]
                if (dir == '' || dir == '.') {
                    dirs.splice(i, 1)
                } else {
                    i++
                }
            }
            let module: SourceFileModule = {
                sourceFile: sourceFile,
                ref: new Map<string, Module>(),
                name: {
                    dirs: dirs.length > 0 ? dirs : undefined,
                    name: path.basename(name)
                },
                includes: [],
                functions: [],
                classes: [],
            }
            moduleSet.set(name, module)
        }

    }

    moduleSet.forEach((item) => {
        parseModule(checker, item, moduleSet)
    })

    moduleSet.forEach((item, name) => {
        if (item.source) {
            let p = path.join(outDir, name)
            mkdir(path.dirname(p))
            fs.writeFileSync(p + '.h', item.source.included)
            fs.writeFileSync(p + '.c', item.source.implemented)
        }
    })
}