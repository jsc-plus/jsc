import * as ts from "typescript"
import * as fs from "fs"
import * as path from "path"
import { Context, mkdir, parseModule, SourceFileModule } from "./parse";
import { Class, isEmptyModule, Module, Scope, Var, Function, Enum } from "./types";
import { toSource } from "./source";


export function parseDeclareModule(ctx: Context, sourceFile: ts.SourceFile, node: ts.Node, ns: string[]): void {

    node.forEachChild((item) => {

        if (ts.isModuleDeclaration(item) && item.body) {

            let name = item.name.getText();

            if (name == 'jsc') {
                parseDeclareModule(ctx, sourceFile, item.body, ns)
                return
            }

            let vs = ns.concat([name])

            let module: SourceFileModule = {
                sourceFile: sourceFile,
                ref: new Map<string, Module>(),
                refClass: new Map<string, Class>(),
                refFunction: new Map<string, Function>(),
                refVar: new Map<string, Var>(),
                refEnum: new Map<string, Enum>(),
                vars: [],
                enums: [],
                name: {
                    name: vs.join('_')
                },
                includes: [],
                closureses: [],
                functions: [],
                classes: [],
                declare: item.body
            }

            ctx.moduleSet.set(module.name.name, module)

            parseDeclareModule(ctx, sourceFile, item.body, vs)

        }

    })

}

export function parseRootDeclareModule(ctx: Context, sourceFile: ts.SourceFile): void {

    sourceFile.forEachChild((item) => {

        if (ts.isModuleDeclaration(item) && item.body) {

            let name = item.name.getText();

            if (name == 'jsc') {
                parseDeclareModule(ctx, sourceFile, item.body, [])
                return
            }

        }

    })

}

export function parse(inFile: string, outDir: string): void {

    let program = ts.createProgram({
        rootNames: [inFile],
        options: {
            target: ts.ScriptTarget.ES5,
            module: ts.ModuleKind.CommonJS,
            removeComments: false
        }
    })

    let checker = program.getTypeChecker();

    let moduleSet = new Map<string, SourceFileModule>()

    let ctx = new Context({
        checker: checker,
        moduleSet: moduleSet,
        scope: new Scope()
    })

    for (let sourceFile of program.getSourceFiles()) {

        if (sourceFile.fileName.endsWith(".jsc.d.ts")) {
            parseRootDeclareModule(ctx, sourceFile)
        }

    }

    moduleSet.forEach((item) => {
        parseModule(ctx, item)
        for (let v of item.vars) {
            v.name.export = true
        }
        for (let v of item.functions) {
            v.name.export = true
        }
        for (let v of item.classes) {
            v.name.export = true
            for (let m of v.methods) {
                m.name.export = true
            }
        }
        item.source = toSource(item)
    })

    moduleSet.forEach((item, name) => {
        if (item.source && !isEmptyModule(item)) {
            let p = path.join(outDir, 'jsc_' + name)
            mkdir(path.dirname(p))
            fs.writeFileSync(p + '.h', item.source.include_h)
            fs.writeFileSync(p + '.inc', item.source.include_c)
            fs.writeFileSync(p + '.c', item.source.implemented)
        }
    })

    {

        let info: any = {
            vars: {},
            functions: {},
            classes: {},
        };

        moduleSet.forEach((item) => {
            if (item.source && !isEmptyModule(item)) {
                let ns: string[] = []
                if (item.name.dirs) {
                    ns = ns.concat(item.name.dirs)
                }
                ns.push(item.name.name)
                let name = ns.join('.')
                for (let v of item.vars) {
                    info.vars[`${name}.${v.name.name}`] = v
                }
                for (let v of item.functions) {
                    info.functions[`${name}.${v.name.name}`] = v
                }
                for (let v of item.classes) {
                    info.classes[`${name}.${v.name.name}`] = v
                }
            }
        })

        let basename = path.basename(inFile);
        fs.writeFileSync(path.join(outDir, basename + '.json'), JSON.stringify(info, undefined, 2))
    }
}