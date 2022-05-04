import { ObjectClass } from "./base";
import { Doc, Module, Symbol, Function, Type, Argument, ModuleName, Method, Class } from "./types"

export interface Source {
    included: string;
    implemented: String
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

export function toInclude(s: Symbol): string {
    return `#include "${toSymbolPath(s)}.h"\n`
}

export function toType(t: Type): string {
    switch (t) {
        case Type.INT8:
            return "jsc_int8_t";
        case Type.UINT8:
            return "jsc_uint8_t";
        case Type.INT16:
            return "jsc_int16_t";
        case Type.UINT16:
            return "jsc_uint16_t";
        case Type.INT32:
            return "jsc_int32_t";
        case Type.UINT32:
            return "jsc_uint32_t";
        case Type.INT64:
            return "jsc_int64_t";
        case Type.UINT64:
            return "jsc_uint64_t";
        case Type.INT:
            return "jsc_int_t";
        case Type.UINT:
            return "jsc_uint_t";
        case Type.LONG:
            return "jsc_long_t";
        case Type.ULONG:
            return "jsc_ulong_t";
        case Type.FLOAT:
            return "jsc_float_t";
        case Type.DOUBLE:
            return "jsc_double_t";
        case Type.FLOAT32:
            return "jsc_float32_t";
        case Type.FLOAT64:
            return "jsc_float64t";
        case Type.BOOLEAN:
            return "jsc_boolean_t";
        case Type.UNICHAR:
            return "jsc_unichar_t";
        case Type.STRING:
            return "jsc_string_t";
        case Type.OBJECT:
            return "jsc_object_t *";
        case Type.VARIANT:
            return "jsc_variant_t";
    }
    return "void"
}

export function toTypeDefaultValue(t: Type): string {
    switch (t) {
        case Type.INT8:
        case Type.UINT8:
        case Type.INT16:
        case Type.UINT16:
        case Type.INT32:
        case Type.UINT32:
        case Type.INT64:
        case Type.UINT64:
        case Type.INT:
        case Type.UINT:
        case Type.LONG:
        case Type.ULONG:
        case Type.FLOAT:
        case Type.DOUBLE:
        case Type.FLOAT32:
        case Type.FLOAT64:
        case Type.BOOLEAN:
        case Type.UNICHAR:
            return "0";
        case Type.STRING:
            return "NULL";
        case Type.OBJECT:
            return "NULL";
        case Type.VARIANT:
            return "jsc_Nil";
    }
    return ""
}

export function toArgumentsDefinition(args: Argument[]): string {
    let vs: string[] = [''];
    if (args.length > 0) {
        for (let a of args) {
            vs.push(`${toType(a.type)} ${a.name}`)
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
    vs.push(toArgumentsDefinition(v.arguments));
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
    vs.push(toArgumentsDefinition(v.arguments));
    vs.push(") {\n");
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
    vs.push(`${toType(v.returnType)} jsc_${toSymbolName(isa.name)}_${v.name.name}_(jsc_class_t * __isa,jsc_object_t * __object${toArgumentsDefinition(v.arguments)});\n`)
    return vs.join('')
}

export function toMethodDefinition(isa: Class, v: Method, level: number = 0): string {
    let vs: string[] = []
    vs.push("\t".repeat(level));
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
        vs.push(`${"\t".repeat(level + 1)}${toType(p.type)} ${p.name.name};\n`)
    }
    vs.push(`${"\t".repeat(level)}} jsc_${toSymbolName(isa.name)}_t;\n`)
    return vs.join('')
}

export function toClassConst(isa: Class, base?: Class): string {
    let vs: string[] = []
    let name = toSymbolName(isa.name);

    let methodSet = new Set<string>();

    for (let m of isa.methods) {
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

        for (let m of ObjectClass.methods) {
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

    let included: string[] = [];
    let implemented: string[] = [];

    included.push(toDoc(m));

    {
        let name = toSymbolModule(m.name);
        included.push(`#ifndef jsc_${name}_h\n#define jsc_${name}_h\n\n`);
    }

    implemented.push(toDoc(m));

    /** include */
    implemented.push(toInclude({
        name: 'jsc'
    }))

    for (let s of m.includes) {
        if (s.export) {
            included.push(toInclude(s))
        }
        implemented.push(toInclude(s))
    }

    implemented.push(toInclude({
        name: m.name.name,
    }))

    included.push('#ifdef __cplusplus\nextern "C" {\n#endif\n\n');

    /** function definition */
    for (let f of m.functions) {
        if (f.name.export) {
            included.push(toDoc(f, 1));
            included.push("\t");
            included.push(toFunctionDefinition(f))
        } else {
            implemented.push(toDoc(f));
            implemented.push(toFunctionDefinition(f))
        }
    }

    /** class definition */
    for (let isa of m.classes) {

        if (isa.name.export) {

            for (let m of isa.methods) {
                included.push(toMethodTypeDefinition(isa, m, 1))
            }

            included.push(toDoc(isa, 1));
            included.push(toClassDefinition(isa, 1));
            included.push(`${"\t".repeat(1)}extern jsc_${toSymbolName(isa.name)}_class_t jsc_${toSymbolName(isa.name)};\n\n`);

            included.push(toClassInstanceDefinition(isa, 1));

            included.push("\n");

            for (let m of isa.methods) {
                included.push(toMethodClassDefinition(isa, m, 1))
            }

            included.push("\n");

            for (let m of isa.methods) {
                included.push(toMethodDefinition(isa, m, 1))
            }

        } else {

            for (let m of isa.methods) {
                implemented.push(toMethodTypeDefinition(isa, m))
            }

            implemented.push(toDoc(isa));
            implemented.push(toClassDefinition(isa));

            implemented.push("\n");

            implemented.push(toClassInstanceDefinition(isa));

            implemented.push("\n");

            for (let m of isa.methods) {
                implemented.push(toMethodClassDefinition(isa, m))
            }

            implemented.push("\n");

            for (let m of isa.methods) {
                implemented.push(toMethodDefinition(isa, m))
            }
        }
    }

    implemented.push("\n/* function implemented */\n");

    /** function implemented */
    for (let f of m.functions) {
        implemented.push(toFunctionImplemented(f))
    }

    implemented.push("\n/* class implemented */\n");

    /** class implemented */
    for (let isa of m.classes) {

        let name = toSymbolName(isa.name);

        implemented.push(`static void _jsc_${isa.name.name}_alloc(struct jsc_class_t * __isa, struct jsc_object_t * __object);\n`)
        implemented.push(`static void _jsc_${isa.name.name}_dealloc(struct jsc_class_t * __isa, struct jsc_object_t * __object);\n`)

        for (let m of isa.methods) {
            implemented.push(`static ${toType(m.returnType)} _jsc_${isa.name.name}_${m.name.name}(struct jsc_class_t * __isa, struct jsc_object_t * __object${toArgumentsDefinition(m.arguments)});\n`)
        }

        implemented.push(`static void _jsc_${isa.name.name}_alloc(struct jsc_class_t * __isa, struct jsc_object_t * __object) {}\n`)

        implemented.push(`static void _jsc_${isa.name.name}_dealloc(struct jsc_class_t * __isa, struct jsc_object_t * __object) {\n`)

        let hasStrong = false;
        for(let p of isa.properties) {
            if(!p.weak) {
                hasStrong = true;
                break
            }
        }

        if(hasStrong) {
            implemented.push(`\tjsc_${name}_t * __v = (jsc_${name}_t *) __object;\n`)
            for(let p of isa.properties) {
                if(!p.weak) {
                    if(p.type == Type.STRING || p.type == Type.OBJECT) {
                        implemented.push(`\tjsc_setStrong(&__v->${p.name.name},NULL);\n`)
                    } else {
                        implemented.push(`\tjsc_veriant_setStrong(&__v->${p.name.name},jsc_Nil);\n`)
                    }
                }
            }    
        }
        
        implemented.push(`}\n`)

        if (!isa.name.export) {
            implemented.push('static ')
        }

        implemented.push(`jsc_${name}_class_t jsc_${name} = ${toClassConst(isa, isa)};\n`)

        for (let m of isa.methods) {
            implemented.push(`static ${toType(m.returnType)} _jsc_${isa.name.name}_${m.name.name}(struct jsc_class_t * __isa, struct jsc_object_t * __object${toArgumentsDefinition(m.arguments)}) {\n`)
            if(m.body) {
                implemented.push(m.body(1))
            } else if (m.returnType != Type.VOID) {
                implemented.push(`\treturn ${toTypeDefaultValue(m.returnType)};\n`)
            }
            implemented.push(`}\n`)

            implemented.push(`static ${toType(m.returnType)} jsc_${name}_${m.name.name}_(struct jsc_class_t * __isa, struct jsc_object_t * __object${toArgumentsDefinition(m.arguments)}) {\n`)
            implemented.push(`\tif(__isa == NULL || __object == NULL) {
        return ${toTypeDefaultValue(m.returnType)};
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_${name})) {
        jsc_${name}_class_t * s = (jsc_${name}_class_t *) __isa;
        if(s->${m.name.name}) {
            ${m.returnType == Type.VOID ? '' : 'return '}(*s->${m.name.name})(__isa,__object${toArgumentsName(m.arguments)});
        } else {
            ${m.returnType == Type.VOID ? '' : 'return '}jsc_${name}_${m.name.name}_(isa->isa,object${toArgumentsName(m.arguments)});
        }
    }

    ${m.returnType == Type.VOID ? '\n' : 'return ' + toTypeDefaultValue(m.returnType) + ';\n'}`)
            implemented.push(`}\n`)

            implemented.push(`static ${toType(m.returnType)} jsc_${name}_${m.name.name}(struct jsc_object_t * __object${toArgumentsDefinition(m.arguments)}) {\n`)
            implemented.push(`\tif(__object == NULL) {
        return ${toTypeDefaultValue(m.returnType)};
    }
    ${m.returnType == Type.VOID ? '' : 'return '}jsc_${name}_${m.name.name}_(__object->isa,__object${toArgumentsName(m.arguments)});\n`)
            implemented.push(`}\n`)

            implemented.push(`\n`)

        }
    }

    included.push('\n#ifdef __cplusplus\n}\n#endif\n\n');
    included.push(`#endif\n\n`);

    return {
        included: included.join(''),
        implemented: implemented.join('')
    }
}