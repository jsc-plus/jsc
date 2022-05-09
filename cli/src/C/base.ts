import { Class, Type, Function, TypeKind, Enum, Var } from "./types";

export var baseClassSet = new Map<String, Class>();

baseClassSet.set('Object', {
    name: {
        name: 'Object'
    },
    properties: [
        {
            name: { name: 'retainCount' },
            type: { kind: TypeKind.INT }
        }
    ],
    methods: [
        {
            name: { name: 'hashCode' },
            returnType: { kind: TypeKind.ULONG },
            arguments: [
            ],
        },
        {
            name: { name: 'compare' },
            returnType: { kind: TypeKind.LONG },
            arguments: [
                {
                    name: 'v',
                    type: { kind: TypeKind.OBJECT }
                }
            ],
        },
        {
            name: { name: 'toString' },
            returnType: { kind: TypeKind.OBJECT },
            arguments: [
            ],
        },
        {
            name: { name: 'toInt64' },
            returnType: { kind: TypeKind.INT64 },
            arguments: [
            ],
        },
        {
            name: { name: 'toFloat64' },
            returnType: { kind: TypeKind.FLOAT64 },
            arguments: [
            ],
        },
        {
            name: { name: 'toBoolean' },
            returnType: { kind: TypeKind.BOOLEAN },
            arguments: [
            ],
        }
    ]
})

baseClassSet.set('String', {
    base: baseClassSet.get('Object'),
    name: {
        name: 'String'
    },
    properties: [
        {
            name: { name: 'length' },
            type: { kind: TypeKind.INT },
            getter: 'length'
        }
    ],
    methods: [
        {
            name: { name: 'length' },
            returnType: { kind: TypeKind.INT },
            arguments: [
            ],
        }
    ]
})

baseClassSet.set('Number', {
    base: baseClassSet.get('Object'),
    name: {
        name: 'Number'
    },
    properties: [
    ],
    methods: [
    ]
})

baseClassSet.set('ArrayBuffer', {
    base: baseClassSet.get('Object'),
    name: {
        name: 'ArrayBuffer'
    },
    new: {
        name: { name: 'new' },
        returnType: { kind: TypeKind.OBJECT, isa: 'this' },
        arguments: [
            {
                name: 'length',
                type: { kind: TypeKind.INT }
            }
        ]
    },
    properties: [
        {
            name: { name: 'byteLength' },
            type: { kind: TypeKind.INT },
            getter: 'byteLength'
        }
    ],
    methods: [
        {
            name: { name: 'byteLength' },
            returnType: { kind: TypeKind.INT },
            arguments: [
            ],
        },
        {
            name: { name: 'slice' },
            returnType: { kind: TypeKind.OBJECT, isa: 'this' },
            arguments: [
                {
                    name: "begin",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "end",
                    type: { kind: TypeKind.INT }
                }
            ],
        },
        {
            name: { name: 'copy' },
            returnType: { kind: TypeKind.OBJECT, isa: 'this' },
            arguments: [
                {
                    name: "dst",
                    type: { kind: TypeKind.OBJECT, isa: 'DataView' }
                },
                {
                    name: "begin",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "end",
                    type: { kind: TypeKind.INT }
                }
            ],
        }
    ]
})

baseClassSet.set('DataView', {
    base: baseClassSet.get('Object'),
    name: {
        name: 'DataView'
    },
    new: {
        name: { name: 'new' },
        returnType: { kind: TypeKind.OBJECT, isa: 'this' },
        arguments: [
            {
                name: 'buffer',
                type: { kind: TypeKind.OBJECT, isa: baseClassSet.get('ArrayBuffer') }
            },
            {
                name: 'offset',
                type: { kind: TypeKind.INT }
            },
            {
                name: 'length',
                type: { kind: TypeKind.INT }
            }
        ]
    },
    properties: [
        {
            name: { name: 'byteLength' },
            type: { kind: TypeKind.INT },
            getter: 'byteLength'
        },
        {
            name: { name: 'byteOffset' },
            type: { kind: TypeKind.INT },
            getter: 'byteOffset'
        },
        {
            name: { name: 'buffer' },
            type: { kind: TypeKind.OBJECT, isa: baseClassSet.get('ArrayBuffer') },
            getter: 'buffer'
        },
    ],
    methods: [
        {
            name: { name: 'byteLength' },
            returnType: { kind: TypeKind.INT },
            arguments: [
            ],
        },
        {
            name: { name: 'byteOffset' },
            returnType: { kind: TypeKind.INT },
            arguments: [
            ],
        },
        {
            name: { name: 'buffer' },
            returnType: { kind: TypeKind.OBJECT, isa: baseClassSet.get('ArrayBuffer') },
            arguments: [
            ],
        },
        {
            name: { name: 'getInt8' },
            returnType: { kind: TypeKind.INT8 },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                }
            ],
        },
        {
            name: { name: 'getUint8' },
            returnType: { kind: TypeKind.UINT8 },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                }
            ],
        },
        {
            name: { name: 'getInt16' },
            returnType: { kind: TypeKind.INT16 },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "littleEndian",
                    type: { kind: TypeKind.BOOLEAN }
                }
            ],
        },
        {
            name: { name: 'getUint16' },
            returnType: { kind: TypeKind.UINT16 },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "littleEndian",
                    type: { kind: TypeKind.BOOLEAN }
                }
            ],
        },
        {
            name: { name: 'getInt32' },
            returnType: { kind: TypeKind.INT32 },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "littleEndian",
                    type: { kind: TypeKind.BOOLEAN }
                }
            ],
        },
        {
            name: { name: 'getUint32' },
            returnType: { kind: TypeKind.UINT32 },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "littleEndian",
                    type: { kind: TypeKind.BOOLEAN }
                }
            ],
        },
        {
            name: { name: 'getInt64' },
            returnType: { kind: TypeKind.INT64 },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "littleEndian",
                    type: { kind: TypeKind.BOOLEAN }
                }
            ],
        },
        {
            name: { name: 'getUint64' },
            returnType: { kind: TypeKind.UINT64 },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "littleEndian",
                    type: { kind: TypeKind.BOOLEAN }
                }
            ],
        },
        {
            name: { name: 'getFloat32' },
            returnType: { kind: TypeKind.FLOAT32 },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "littleEndian",
                    type: { kind: TypeKind.BOOLEAN }
                }
            ],
        },
        {
            name: { name: 'getFloat64' },
            returnType: { kind: TypeKind.FLOAT64 },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "littleEndian",
                    type: { kind: TypeKind.BOOLEAN }
                }
            ],
        },
        {
            name: { name: 'getString' },
            returnType: { kind: TypeKind.STRING },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                }
            ],
        },
        {
            name: { name: 'setInt8' },
            returnType: { kind: TypeKind.VOID },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "value",
                    type: { kind: TypeKind.INT8 }
                }
            ],
        },
        {
            name: { name: 'setUint8' },
            returnType: { kind: TypeKind.VOID },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "value",
                    type: { kind: TypeKind.UINT8 }
                }
            ],
        },
        {
            name: { name: 'setInt16' },
            returnType: { kind: TypeKind.VOID },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "value",
                    type: { kind: TypeKind.INT16 }
                },
                {
                    name: "littleEndian",
                    type: { kind: TypeKind.BOOLEAN }
                }
            ],
        },
        {
            name: { name: 'setUint16' },
            returnType: { kind: TypeKind.VOID },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "value",
                    type: { kind: TypeKind.UINT16 }
                },
                {
                    name: "littleEndian",
                    type: { kind: TypeKind.BOOLEAN }
                }
            ],
        },
        {
            name: { name: 'setInt32' },
            returnType: { kind: TypeKind.VOID },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "value",
                    type: { kind: TypeKind.INT32 }
                },
                {
                    name: "littleEndian",
                    type: { kind: TypeKind.BOOLEAN }
                }
            ],
        },
        {
            name: { name: 'setUint32' },
            returnType: { kind: TypeKind.VOID },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "value",
                    type: { kind: TypeKind.UINT32 }
                },
                {
                    name: "littleEndian",
                    type: { kind: TypeKind.BOOLEAN }
                }
            ],
        },
        {
            name: { name: 'setInt64' },
            returnType: { kind: TypeKind.VOID },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "value",
                    type: { kind: TypeKind.INT64 }
                },
                {
                    name: "littleEndian",
                    type: { kind: TypeKind.BOOLEAN }
                }
            ],
        },
        {
            name: { name: 'setUint64' },
            returnType: { kind: TypeKind.VOID },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "value",
                    type: { kind: TypeKind.UINT64 }
                },
                {
                    name: "littleEndian",
                    type: { kind: TypeKind.BOOLEAN }
                }
            ],
        },
        {
            name: { name: 'setFloat32' },
            returnType: { kind: TypeKind.VOID },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "value",
                    type: { kind: TypeKind.FLOAT32 }
                },
                {
                    name: "littleEndian",
                    type: { kind: TypeKind.BOOLEAN }
                }
            ],
        },
        {
            name: { name: 'setFloat64' },
            returnType: { kind: TypeKind.VOID },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "value",
                    type: { kind: TypeKind.FLOAT64 }
                },
                {
                    name: "littleEndian",
                    type: { kind: TypeKind.BOOLEAN }
                }
            ],
        },
        {
            name: { name: 'setString' },
            returnType: { kind: TypeKind.INT },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "value",
                    type: { kind: TypeKind.STRING }
                }
            ],
        },
        {
            name: { name: 'setData' },
            returnType: { kind: TypeKind.INT },
            arguments: [
                {
                    name: "offset",
                    type: { kind: TypeKind.INT }
                },
                {
                    name: "value",
                    type: { kind: TypeKind.OBJECT, isa: 'this' }
                }
            ],
        }
    ]
})

baseClassSet.set('Map', {
    base: baseClassSet.get('Object'),
    name: {
        name: 'Map'
    },
    properties: [
        {
            name: { name: 'size' },
            type: { kind: TypeKind.INT },
            getter: 'size'
        },
    ],
    methods: [
        {
            name: { name: 'size' },
            returnType: { kind: TypeKind.INT },
            arguments: [
            ],
        },
        {
            name: { name: 'clear' },
            returnType: { kind: TypeKind.VOID },
            arguments: [
            ],
        },
        {
            name: { name: 'del' },
            returnType: { kind: TypeKind.VOID },
            arguments: [
                {
                    name: 'key',
                    type: { kind: TypeKind.VARIANT }
                },
            ],
        },
        {
            name: { name: 'get' },
            returnType: { kind: TypeKind.VARIANT },
            arguments: [
                {
                    name: 'key',
                    type: { kind: TypeKind.VARIANT }
                },
            ],
        },
        {
            name: { name: 'has' },
            returnType: { kind: TypeKind.BOOLEAN },
            arguments: [
                {
                    name: 'key',
                    type: { kind: TypeKind.VARIANT }
                },
            ],
        },
        {
            name: { name: 'set' },
            returnType: { kind: TypeKind.VOID },
            arguments: [
                {
                    name: 'key',
                    type: { kind: TypeKind.VARIANT }
                },
                {
                    name: 'value',
                    type: { kind: TypeKind.VARIANT }
                },
            ],
        }
    ]
})

baseClassSet.set('Array', {
    base: baseClassSet.get('Object'),
    name: {
        name: 'Array'
    },
    properties: [
        {
            name: { name: 'length' },
            type: { kind: TypeKind.INT },
            getter: 'length'
        },
    ],
    methods: [
        {
            name: { name: 'length' },
            returnType: { kind: TypeKind.INT },
            arguments: [
            ],
        },
        {
            name: { name: 'push' },
            returnType: { kind: TypeKind.VOID },
            arguments: [
                {
                    name: 'value',
                    type: { kind: TypeKind.VARIANT }
                },
            ],
        },
        {
            name: { name: 'pop' },
            returnType: { kind: TypeKind.VARIANT },
            arguments: [
            ],
        },
        {
            name: { name: 'shift' },
            returnType: { kind: TypeKind.VARIANT },
            arguments: [
            ],
        },
        {
            name: { name: 'unshift' },
            returnType: { kind: TypeKind.VOID },
            arguments: [
                {
                    name: 'value',
                    type: { kind: TypeKind.VARIANT }
                },
            ],
        },
        {
            name: { name: 'splice' },
            returnType: { kind: TypeKind.VOID },
            arguments: [
                {
                    name: 'index',
                    type: { kind: TypeKind.INT }
                },
                {
                    name: 'count',
                    type: { kind: TypeKind.INT }
                },
            ],
        },
        {
            name: { name: 'slice' },
            returnType: { kind: TypeKind.OBJECT, isa: 'this' },
            arguments: [
                {
                    name: 'begin',
                    type: { kind: TypeKind.INT }
                },
                {
                    name: 'end',
                    type: { kind: TypeKind.INT }
                },
            ],
        },
        {
            name: { name: 'join' },
            returnType: { kind: TypeKind.OBJECT, isa: baseClassSet.get('String') },
            arguments: [
                {
                    name: 'separator',
                    type: { kind: TypeKind.STRING }
                },
            ],
        },
        {
            name: { name: 'indexOf' },
            returnType: { kind: TypeKind.INT },
            arguments: [
                {
                    name: 'value',
                    type: { kind: TypeKind.VARIANT }
                },
            ],
        },
    ]
})

baseClassSet.set('Closures',{
    base: baseClassSet.get('Object'),
    name: {
        name: 'Closures'
    },
    properties: [
    ],
    methods: [
    ]
})

export var baseFunctionSet = new Map<string, Function>()

baseFunctionSet.set('log', {
    name: {
        name: 'log'
    },
    returnType: { kind: TypeKind.VOID },
    arguments: [
        {
            name: 'format',
            type: { kind: TypeKind.STRING }
        },
        {
            name: '...',
            type: { kind: TypeKind.VARIANT }
        }
    ]
})

export var baseVarSet = new Map<string, Var>()

export function getRefClass(isa?: Class | string): Class | undefined {
    if (typeof isa == 'string') {
        return baseClassSet.get(isa)
    }
    return isa
}

export function addDeclare(info: any): void {
    if (info.classes) {
        for (let name in info.classes) {
            baseClassSet.set(name, info.classes[name])
        }
    }
    if (info.functions) {
        for (let name in info.functions) {
            baseFunctionSet.set(name, info.functions[name])
        }
    }
    if (info.vars) {
        for (let name in info.vars) {
            baseVarSet.set(name, info.vars[name])
        }
    }
}

export function getBaseClass(name: string): Class | undefined {
    if (/^jsc\./i.test(name)) {
        name = name.substring(4)
    }
    return baseClassSet.get(name)
}

export function getBaseFunction(name: string): Function | undefined {
    if (/^jsc\./i.test(name)) {
        name = name.substring(4)
    }
    return baseFunctionSet.get(name)
}

export function getBaseVar(name: string): Var | undefined {
    if (/^jsc\./i.test(name)) {
        name = name.substring(4)
    }
    return baseVarSet.get(name)
}

addDeclare(require('./jsc.d.ts.json/Math.jsc.d.ts.json'))
addDeclare(require('./jsc.d.ts.json/crypto.jsc.d.ts.json'))
addDeclare(require('./jsc.d.ts.json/Typeof.jsc.d.ts.json'))
