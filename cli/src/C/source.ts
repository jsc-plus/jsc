import { baseClassSet } from "./base";
import { Doc, Module, Symbol, Function, Type, Argument, ModuleName, Method, Class, TypeKind, ClosuresDeclare } from "./types"

export interface Source {
    include_h: string;
    include_c: string;
    implemented: string;
}


export function toDoc(doc: Doc, level: number = 0, rows?: string[]): string {
    let vs: string[] = [];
    if ((rows && rows.length > 0) || doc.title || (doc.tags && doc.tags.length > 0)) {
        let t = "\t".repeat(level);
        vs.push(`${t}/**\n`)
        if (doc.title) {
            for (let s of doc.title.split("\n")) {
                vs.push(`${t} * ${s}\n`)
            }
        }
        if (doc.tags) {
            for (let tag of doc.tags) {
                vs.push(`${t} * @${tag.name} ${tag.value || ''}\n`)
            }
        }
        if (rows) {
            for (let row of rows) {
                vs.push(`${t} * ${row}\n`)
            }
        }
        vs.push(`${t} */\n`)
    }
    return vs.join('')
}

export function toSymbolPath(s: Symbol): string {
    let vs: string[] = []
    if (s.module) {
        if (s.module.dirs) {
            vs.push(s.module.dirs.join('/'))
            vs.push('/')
        }
        vs.push(s.module.name)
        vs.push('/')
    }
    vs.push(s.name)
    return vs.join('')
}

export function toSymbolModule(s: ModuleName): string {
    let vs: string[] = []
    if (s.dirs) {
        vs.push(s.dirs.join('_'))
        vs.push('_')
    }
    vs.push(s.name)
    return vs.join('')
}

export function toSymbolModulePath(s: ModuleName): string {
    let vs: string[] = []
    if (s.dirs) {
        vs.push(s.dirs.join('/'))
        vs.push('/')
    }
    vs.push(s.name)
    return vs.join('')
}

export function toSymbolName(s: Symbol): string {
    let vs: string[] = []
    if (s.module && s.export) {
        if (s.module.dirs) {
            vs.push(s.module.dirs.join('_'))
            vs.push('_')
        }
        vs.push(s.module.name)
        vs.push('_')
    }
    vs.push(s.name)
    return vs.join('')
}

export function toInclude(s: Symbol, exname: string = 'h'): string {
    return `#include "${toSymbolPath(s)}.${exname}"\n`
}

export function toFunctionType(func: Function, name: string = ""): string {
    let vs: string[] = [];
    vs.push(`${toType(func.returnType)} (*${name})(`)
    for (let i = 0; i < func.arguments.length; i++) {
        if (i != 0) {
            vs.push(',')
        }
        vs.push(`${toType(func.arguments[i].type)}`)
    }
    vs.push(')')
    return vs.join('')
}

export function toType(t: Type): string {
    switch (t.kind) {
        case TypeKind.INT8:
            return "jsc_int8_t";
        case TypeKind.UINT8:
            return "jsc_uint8_t";
        case TypeKind.INT16:
            return "jsc_int16_t";
        case TypeKind.UINT16:
            return "jsc_uint16_t";
        case TypeKind.INT32:
            return "jsc_int32_t";
        case TypeKind.UINT32:
            return "jsc_uint32_t";
        case TypeKind.INT64:
            return "jsc_int64_t";
        case TypeKind.UINT64:
            return "jsc_uint64_t";
        case TypeKind.INT:
            return "jsc_int_t";
        case TypeKind.UINT:
            return "jsc_uint_t";
        case TypeKind.LONG:
            return "jsc_long_t";
        case TypeKind.ULONG:
            return "jsc_ulong_t";
        case TypeKind.FLOAT32:
            return "jsc_float32_t";
        case TypeKind.FLOAT64:
            return "jsc_float64_t";
        case TypeKind.BOOLEAN:
            return "jsc_boolean_t";
        case TypeKind.UNICHAR:
            return "jsc_unichar_t";
        case TypeKind.STRING:
            return "jsc_string_t";
        case TypeKind.OBJECT:
            return "jsc_object_t *";
        case TypeKind.VARIANT:
            return "jsc_variant_t";
    }
    return "void"
}

export function toTypeDefaultValue(t: Type): string {
    switch (t.kind) {
        case TypeKind.INT8:
        case TypeKind.UINT8:
        case TypeKind.INT16:
        case TypeKind.UINT16:
        case TypeKind.INT32:
        case TypeKind.UINT32:
        case TypeKind.INT64:
        case TypeKind.UINT64:
        case TypeKind.INT:
        case TypeKind.UINT:
        case TypeKind.LONG:
        case TypeKind.ULONG:
        case TypeKind.FLOAT32:
        case TypeKind.FLOAT64:
        case TypeKind.BOOLEAN:
        case TypeKind.UNICHAR:
            return "0";
        case TypeKind.STRING:
            return "NULL";
        case TypeKind.OBJECT:
            return "NULL";
        case TypeKind.VARIANT:
            return "jsc_Nil";
    }
    return ""
}

export function toArgumentsDefinition(args: Argument[], vs: string[] = ['']): string {
    if (args.length > 0) {
        for (let a of args) {
            vs.push(`${toType(a.type)}${a.type.closures?` /* jsc_${toSymbolName(a.type.closures.name)}_t */`:''} ${a.name}`)
        }
    }
    return vs.join(', ')
}

export function toArgumentsName(args: Argument[]): string {
    let vs: string[] = [''];
    for (let a of args) {
        vs.push(a.name)
    }
    return vs.join(',')
}

export function toFunctionDefinition(v: Function): string {
    let vs: string[] = []
    if (!v.name.export) {
        vs.push('static ')
    }
    vs.push(toType(v.returnType))
    vs.push(" jsc_")
    vs.push(toSymbolName(v.name))
    vs.push("(");
    if (v.arguments.length == 0) {
        vs.push('void')
    } else {
        vs.push(toArgumentsDefinition(v.arguments, []));
    }
    vs.push(");\n");
    return vs.join('')
}

export function toFunctionTypeDefinition(v: Function | ClosuresDeclare): string {
    let vs: string[] = []
    vs.push(`typedef `)
    vs.push(toType(v.returnType))
    vs.push(" (*jsc_")
    vs.push(toSymbolName(v.name))
    vs.push("_t)(");
    if (v.arguments.length == 0) {
        vs.push('void')
    } else {
        vs.push(toArgumentsDefinition(v.arguments, []));
    }
    vs.push(");\n");
    return vs.join('')
}

export function toFunctionImplemented(v: Function): string {
    let vs: string[] = []
    if (!v.name.export) {
        vs.push('static ')
    }
    vs.push(toType(v.returnType))
    vs.push(" jsc_")
    vs.push(toSymbolName(v.name))
    vs.push("(");
    vs.push(toArgumentsDefinition(v.arguments, []));
    vs.push(") {\n");
    if (v.body) {
        vs.push(v.body(1))
    } else if (v.returnType.kind != TypeKind.VOID) {
        vs.push(`\treturn ${toTypeDefaultValue(v.returnType)};\n`)
    }
    vs.push("}\n");
    return vs.join('')
}

export function toMethodTypeName(isa: Class, v: Method): string {
    return `jsc_${toSymbolName(isa.name)}_${v.name.name}_t`
}

export function toMethodTypeDefinition(isa: Class, v: Method, level: number = 0): string {
    let vs: string[] = []
    vs.push("\t".repeat(level));
    vs.push(`typedef ${toType(v.returnType)} (*${toMethodTypeName(isa, v)})(jsc_class_t * __isa,jsc_object_t * __object${toArgumentsDefinition(v.arguments)});\n`)
    return vs.join('')
}

export function toMethodClassDefinition(isa: Class, v: Method, level: number = 0): string {
    let vs: string[] = []
    vs.push("\t".repeat(level));
    if (!isa.name.export) {
        vs.push('static ')
    }
    vs.push(`${toType(v.returnType)} jsc_${toSymbolName(isa.name)}_${v.name.name}_(jsc_class_t * __isa,jsc_object_t * __object${toArgumentsDefinition(v.arguments)});\n`)
    return vs.join('')
}

export function toNewClassDefinition(isa: Class, func: Function, level: number = 0): string {
    let vs: string[] = []
    vs.push("\t".repeat(level));
    if (!isa.name.export) {
        vs.push('static ')
    }
    vs.push(`${toType(func.returnType)} jsc_${toSymbolName(isa.name)}_new(${func.arguments.length == 0 ? 'void' : toArgumentsDefinition(func.arguments, [])});\n`)
    return vs.join('')
}

export function toMethodDefinition(isa: Class, v: Method, level: number = 0): string {
    let vs: string[] = []
    vs.push("\t".repeat(level));
    if (!isa.name.export) {
        vs.push('static ')
    }
    vs.push(`${toType(v.returnType)} jsc_${toSymbolName(isa.name)}_${v.name.name}(jsc_object_t * __object${toArgumentsDefinition(v.arguments)});\n`)
    return vs.join('')
}

export function toClassDefinition(isa: Class, level: number = 0): string {
    let vs: string[] = []
    vs.push(`${"\t".repeat(level)}typedef struct jsc_${toSymbolName(isa.name)}_class_t {\n`)
    vs.push(`${"\t".repeat(level + 1)}jsc_${isa.base ? toSymbolName(isa.base.name) + "_" : ""}class_t base;\n`)
    for (let m of isa.methods) {
        vs.push(`${"\t".repeat(level + 1)}${toMethodTypeName(isa, m)} ${m.name.name};\n`)
    }
    vs.push(`${"\t".repeat(level)}} jsc_${toSymbolName(isa.name)}_class_t;\n`)
    return vs.join('')
}

export function toClassInstanceDefinition(isa: Class, level: number = 0): string {
    let vs: string[] = []
    vs.push(`${"\t".repeat(level)}typedef struct ${toSymbolName(isa.name)}_t {\n`)
    vs.push(`${"\t".repeat(level + 1)}jsc_${isa.base ? toSymbolName(isa.base.name) : "object"}_t base;\n`)
    for (let p of isa.properties) {
        vs.push(`${"\t".repeat(level + 1)}${toType(p.type.kind == TypeKind.STRING ? { kind: TypeKind.OBJECT } : p.type)} ${p.name.name};\n`)
    }
    vs.push(`${"\t".repeat(level)}} jsc_${toSymbolName(isa.name)}_t;\n`)
    return vs.join('')
}

export function toClassConst(isa: Class, base?: Class): string {
    let vs: string[] = []
    let name = toSymbolName(isa.name);

    let methodSet = new Set<string>();

    for (let m of isa.methods) {
        if (m.name.name == '__init' && isa != base) {
            continue;
        }
        methodSet.add(m.name.name)
    }


    if (base) {

        vs.push(`{${toClassConst(isa, base.base)}`)

        for (let m of base.methods) {
            if (methodSet.has(m.name.name)) {
                vs.push(`,_jsc_${isa.name.name}_${m.name.name}`)
            } else {
                vs.push(',NULL')
            }
        }

        vs.push("}")

    } else {

        vs.push(`{(jsc_class_t *)&jsc_${isa.base ? toSymbolName(isa.base.name) : 'Object'},sizeof(jsc_${name}_t),"${name}",_jsc_${isa.name.name}_alloc,_jsc_${isa.name.name}_dealloc`)

        for (let m of baseClassSet.get('Object')!.methods) {
            if (methodSet.has(m.name.name)) {
                vs.push(`,_jsc_${isa.name.name}_${m.name.name}`)
            } else {
                vs.push(',NULL')
            }
        }

        vs.push("}")
    }

    return vs.join('')
}

export function toSource(m: Module): Source {

    let include_h: string[] = [];
    let include_c: string[] = [];
    let implemented: string[] = [];

    include_h.push(toDoc(m));
    include_c.push(toDoc(m));

    {
        let name = toSymbolModule(m.name);
        include_h.push(`#ifndef jsc_${name}_h\n#define jsc_${name}_h\n\n`);
    }

    implemented.push(toDoc(m));

    /** include */
    include_c.push(toInclude({
        name: 'jsc'
    }))

    include_c.push(toInclude({
        name: m.name.name,
    }));

    for (let s of m.includes) {
        if (s.export) {
            include_h.push(toInclude(s))
        }
        include_c.push(toInclude(s))
    }

    implemented.push(toInclude({
        name: m.name.name,
    }, 'inc'))

    include_h.push('#ifdef __cplusplus\nextern "C" {\n#endif\n\n');

    /** enum definition */

    for (let v of m.enums) {
        include_h.push(toDoc(v, 1));
        include_h.push(`\tenum {\n`)
        let n = `jsc_${toSymbolName(v.name)}`
        for (let item of v.items) {
            include_h.push(toDoc(item, 2));
            include_h.push(`\t\t${n}_${item.name},\n`)
        }
        include_h.push(`\t};\n`)
    }

    /** var definition */

    for (let v of m.vars) {
        let n = `jsc_${toSymbolName(v.name)}`
        if (v.name.export) {
            include_h.push(toDoc(v, 1));
            if (v.type.kind == TypeKind.STRING && !v.type.CString) {
                include_h.push(`\textern ${toType({ kind: TypeKind.OBJECT })} ${n};\n`)
            } else {
                include_h.push(`\textern ${toType(v.type)} ${n};\n`)
            }
        } else {
            include_c.push(toDoc(v, 1));
            if (v.type.kind == TypeKind.STRING && !v.type.CString) {
                include_c.push(`static ${toType({ kind: TypeKind.OBJECT })} ${n} = ${toTypeDefaultValue(v.type)} ;\n`)
            } else {
                include_c.push(`static ${toType(v.type)} ${n} = ${v.initializer ? v.initializer : toTypeDefaultValue(v.type)};\n`)
            }
        }
    }

    /** closures declare definition */
    for (let f of m.closureses) {
        if (f.name.export) {
            include_h.push(toDoc(f, 1));
            include_h.push("\t");
            include_h.push(toFunctionTypeDefinition(f))
        } else {
            include_c.push(toDoc(f));
            include_c.push(toFunctionTypeDefinition(f))
        }
    }

    /** function definition */
    for (let f of m.functions) {
        if (f.name.export) {
            include_h.push(toDoc(f, 1));
            include_h.push("\t");
            include_h.push(toFunctionDefinition(f))
        } else {
            include_c.push(toDoc(f));
            include_c.push(toFunctionDefinition(f))
        }
    }

    /** class definition */
    for (let isa of m.classes) {

        if (isa.name.export) {

            for (let m of isa.methods) {
                include_h.push(toMethodTypeDefinition(isa, m, 1))
            }

            include_h.push(toDoc(isa, 1));
            include_h.push(toClassDefinition(isa, 1));
            include_h.push(`${"\t".repeat(1)}extern jsc_${toSymbolName(isa.name)}_class_t jsc_${toSymbolName(isa.name)};\n\n`);

            include_h.push(toClassInstanceDefinition(isa, 1));

            include_h.push("\n");

            for (let m of isa.methods) {
                include_h.push(toMethodClassDefinition(isa, m, 1))
            }

            include_h.push("\n");

            for (let m of isa.methods) {
                include_h.push(toMethodDefinition(isa, m, 1))
            }


            if (isa.new) {

                include_h.push("\n");

                include_h.push(toNewClassDefinition(isa, isa.new, 1))
            }

        } else {

            for (let m of isa.methods) {
                include_c.push(toMethodTypeDefinition(isa, m))
            }

            include_c.push(toDoc(isa));
            include_c.push(toClassDefinition(isa));

            include_c.push("\n");

            include_c.push(toClassInstanceDefinition(isa));

            include_c.push("\n");

            for (let m of isa.methods) {
                include_c.push(toMethodClassDefinition(isa, m))
            }

            include_c.push("\n");

            for (let m of isa.methods) {
                include_c.push(toMethodDefinition(isa, m))
            }

            if (isa.new) {

                include_c.push("\n");
                include_c.push(toNewClassDefinition(isa, isa.new, 1))

            }
        }
    }

    include_c.push("\n/* var implemented */\n");

    /** var implemented */
    for (let v of m.vars) {
        let n = `jsc_${toSymbolModule(m.name)}_${v.name.name}`
        if (v.name.export) {
            if (v.type.kind == TypeKind.STRING && !v.type.CString) {
                include_c.push(`static ${toType({ kind: TypeKind.OBJECT })} ${n} = ${toTypeDefaultValue(v.type)} ;\n`)
            } else {
                include_c.push(`${toType(v.type)} ${n} = ${v.initializer ? v.initializer : toTypeDefaultValue(v.type)};\n`)
            }
        }
    }

    include_c.push("\n/* class implemented */\n");
    implemented.push("\n/* class implemented */\n");

    /** class implemented */
    for (let isa of m.classes) {

        let name = toSymbolName(isa.name);

        include_c.push(`static void _jsc_${isa.name.name}_alloc(jsc_class_t * __isa, jsc_object_t * __object);\n`)
        include_c.push(`static void _jsc_${isa.name.name}_dealloc(jsc_class_t * __isa, jsc_object_t * __object);\n`)

        for (let m of isa.methods) {
            include_c.push(`static ${toType(m.returnType)} _jsc_${isa.name.name}_${m.name.name}(jsc_class_t * __isa, jsc_object_t * __object${toArgumentsDefinition(m.arguments)});\n`)
        }

        include_c.push(`static void _jsc_${isa.name.name}_alloc(jsc_class_t * __isa, jsc_object_t * __object) {}\n`)

        include_c.push(`static void _jsc_${isa.name.name}_dealloc(jsc_class_t * __isa, jsc_object_t * __object) {\n`)

        let hasStrong = false;
        for (let p of isa.properties) {
            if (!p.type.weak && (p.type.kind == TypeKind.OBJECT || (p.type.kind == TypeKind.STRING && !p.type.CString))) {
                hasStrong = true;
                break
            }
        }

        if (hasStrong) {
            include_c.push(`\tjsc_${name}_t * __v = (jsc_${name}_t *) __object;\n`)
            for (let p of isa.properties) {
                if (!p.type.weak) {
                    if (p.type.kind == TypeKind.STRING || p.type.kind == TypeKind.OBJECT) {
                        include_c.push(`\tjsc_setStrong(&__v->${p.name.name},NULL);\n`)
                    } else if (p.type.kind == TypeKind.VARIANT) {
                        include_c.push(`\tjsc_veriant_setStrong(&__v->${p.name.name},jsc_Nil);\n`)
                    }
                }
            }
        }

        include_c.push(`}\n`)

        if (!isa.name.export) {
            include_c.push('static ')
        }

        include_c.push(`jsc_${name}_class_t jsc_${name} = ${toClassConst(isa, isa)};\n`)

        for (let m of isa.methods) {

            implemented.push(`static ${toType(m.returnType)} _jsc_${isa.name.name}_${m.name.name}(jsc_class_t * __isa, jsc_object_t * __object${toArgumentsDefinition(m.arguments)}) {\n`)

            if (m.body) {
                implemented.push(m.body(1))
            } else if (m.returnType.kind != TypeKind.VOID) {
                implemented.push(`\treturn ${toTypeDefaultValue(m.returnType)};\n`)
            }

            implemented.push(`}\n`)

            include_c.push(`${m.name.export ? '' : 'static '}${toType(m.returnType)} jsc_${name}_${m.name.name}_(jsc_class_t * __isa, jsc_object_t * __object${toArgumentsDefinition(m.arguments)}) {\n`)
            include_c.push(`\tif(__isa == NULL || __object == NULL) {
        return ${toTypeDefaultValue(m.returnType)};
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_${name})) {
        jsc_${name}_class_t * s = (jsc_${name}_class_t *) __isa;
        if(s->${m.name.name}) {
            ${m.returnType.kind == TypeKind.VOID ? '' : 'return '}(*s->${m.name.name})(__isa,__object${toArgumentsName(m.arguments)});
        } else {
            ${m.returnType.kind == TypeKind.VOID ? '' : 'return '}jsc_${name}_${m.name.name}_(__isa->isa,__object${toArgumentsName(m.arguments)});
        }
    }

    ${m.returnType.kind == TypeKind.VOID ? '\n' : 'return ' + toTypeDefaultValue(m.returnType) + ';\n'}`)

            include_c.push(`}\n`)

            include_c.push(`${m.name.export ? '' : 'static '}${toType(m.returnType)} jsc_${name}_${m.name.name}(jsc_object_t * __object${toArgumentsDefinition(m.arguments)}) {\n`)
            include_c.push(`\tif(__object == NULL) {
        return ${toTypeDefaultValue(m.returnType)};
    }
    ${m.returnType.kind == TypeKind.VOID ? '' : 'return '}jsc_${name}_${m.name.name}_(__object->isa,__object${toArgumentsName(m.arguments)});\n`)

            include_c.push(`}\n`)

            include_c.push(`\n`)

        }

        if (isa.new) {
            include_c.push(`${isa.name.export ? '' : 'static '}${toType(isa.new.returnType)} jsc_${name}_${isa.new.name.name}(${toArgumentsDefinition(isa.new.arguments, [])}) {\n`)
            include_c.push(`\tjsc_object_t * __object = jsc_object_new((jsc_class_t *)&jsc_${name},0);\n`)
            include_c.push(`\tjsc_${name}___init_((jsc_class_t *)&jsc_${name},__object${toArgumentsName(isa.new.arguments)});\n`)
            include_c.push(`\treturn __object;\n`)
            include_c.push(`}\n`)
        }
    }

    implemented.push("\n/* function implemented */\n");

    /** function implemented */
    for (let f of m.functions) {
        implemented.push(toFunctionImplemented(f))
    }

    include_h.push('\n#ifdef __cplusplus\n}\n#endif\n\n');
    include_h.push(`#endif\n\n`);

    return {
        include_h: include_h.join(''),
        include_c: include_c.join(''),
        implemented: implemented.join('')
    }
}