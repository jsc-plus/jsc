import { Class, Type, Function, TypeKind } from "./types";

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
        returnType: { kind: TypeKind.OBJECT },
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
        }
    ]
})

baseClassSet.set('DataView', {
    base: baseClassSet.get('Object'),
    name: {
        name: 'DataView'
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
        }
    ]
})

export var baseFunctionSet = new Map<string, Function>()

baseFunctionSet.set('jsc.log', {
    name: {
        name: 'jsc_log'
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