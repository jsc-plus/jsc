
export enum TypeKind {
    VOID,
    NIL,
    OBJECT,
    VARIANT,
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
    FLOAT32,
    FLOAT64,
    BOOLEAN,
    UNICHAR,
    STRING,
    PTR,
}

export var TypeKinds: string[] = [
    'VOID',
    'NIL',
    'OBJECT',
    'VARIANT',
    'INT8',
    'UINT8',
    'INT16',
    'UINT16',
    'INT32',
    'UINT32',
    'INT64',
    'UINT64',
    'INT',
    'UINT',
    'LONG',
    'ULONG',
    'FLOAT32',
    'FLOAT64',
    'BOOLEAN',
    'UNICHAR',
    'STRING',
    'PTR'
]

export interface Type {
    kind: TypeKind
    isa?: Class
    func?: Function
    weak?: boolean
    var?: boolean
    property?: boolean
    CString?: boolean
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

export interface Property extends Var {
    getter?: string
    setter?: string
}

export interface Var extends Doc {
    name: Symbol
    type: Type
    initializer?: string
}

export interface Class extends Doc {
    base?: Class
    name: Symbol
    new?: Function
    properties: Property[]
    methods: Method[]
}

export interface Module extends Doc {
    name: ModuleName
    ref: Map<string, Module>
    refClass: Map<string, Class>
    refFunction: Map<string, Function>
    refVar: Map<string, Var>
    vars: Var[]
    includes: Symbol[]
    functions: Function[]
    classes: Class[]
}

export function isEmptyModule(m: Module): boolean {
    return m.vars.length == 0 && m.includes.length == 0 && m.functions.length == 0 && m.classes.length == 0
}

export interface ScopeVar {
    name: Symbol
    type: Type
}

export class Scope {

    readonly parent?: Scope

    protected _varSet: Map<string, ScopeVar>

    constructor(p?: Scope) {
        this.parent = p
        this._varSet = new Map<string, ScopeVar>()
    }

    get(name: string): ScopeVar | undefined {
        let v = this._varSet.get(name)
        if (v) {
            return v;
        }
        if (this.parent) {
            return this.parent.get(name)
        }
    }

    set(name: Symbol, type: Type): void {
        this._varSet.set(name.name, { name: name, type: type })
    }

}
