
export enum Type {
    NIL,
    INT8,
    UINT8,
    INT16,
    UINT16,
    INT32,
    UINT32,
    INT64,
    UINT64,
    INT,
    UINT,
    LONG,
    ULONG,
    FLOAT,
    DOUBLE,
    FLOAT32,
    FLOAT64,
    BOOLEAN,
    UNICHAR,
    STRING,
    OBJECT,
    VARIANT,
    VOID,
}

export type Body = (level?: number) => string

export interface Tag {
    name: string
    value?: string
}

export interface Doc {
    title?: string
    tags?: Tag[]
}

export interface Argument {
    name: string
    type: Type
}

export interface ModuleName {
    dirs?: string[]
    name: string
}

export interface Symbol {
    export?: boolean
    module?: ModuleName
    name: string
}

export interface Function extends Doc {
    name: Symbol
    returnType: Type
    arguments: Argument[]
    body?: Body
}

export interface Method extends Function {

}

export interface Property extends Doc {
    name: Symbol
    type: Type
    weak?: boolean
}

export interface Class extends Doc {
    base?: Class
    name: Symbol
    properties: Property[]
    methods: Method[]
}

export interface Module extends Doc {
    name: ModuleName
    ref: Map<string, Module>
    includes: Symbol[]
    functions: Function[]
    classes: Class[]
}

