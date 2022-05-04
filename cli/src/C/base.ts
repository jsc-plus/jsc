import { Class, Type } from "./types";

export var ObjectClass: Class = {
    name: {
        name: 'Object'
    },
    properties: [
        {
            name: { name: 'retainCount' },
            type: Type.INT
        }
    ],
    methods: [
        {
            name: { name: 'hashCode' },
            returnType: Type.ULONG,
            arguments: [
            ],
        },
        {
            name: { name: 'compare' },
            returnType: Type.LONG,
            arguments: [
                {
                    name: 'v',
                    type: Type.OBJECT
                }
            ],
        },
        {
            name: { name: 'toString' },
            returnType: Type.OBJECT,
            arguments: [
            ],
        },
        {
            name: { name: 'toInt64' },
            returnType: Type.INT64,
            arguments: [
            ],
        },
        {
            name: { name: 'toFloat64' },
            returnType: Type.FLOAT64,
            arguments: [
            ],
        },
        {
            name: { name: 'toBoolean' },
            returnType: Type.BOOLEAN,
            arguments: [
            ],
        }
    ]
}