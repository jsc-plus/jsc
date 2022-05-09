
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
]

export interface Type {
    kind: TypeKind
    isa?: Class | string
    weak?: boolean
    var?: boolean
    property?: boolean
    CString?: boolean
    enum?: Enum
    closures?: ClosuresDeclare
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

export interface ClosuresDeclare extends Doc {
    name: Symbol
    returnType: Type
    arguments: Argument[]
}

export interface Function extends Doc {
    name: Symbol
    returnType: Type
    arguments: Argument[]
    body?: Body
    closures?: ClosuresDeclare
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

export interface EnumItem extends Doc {
    name: string
}

export interface Enum extends Doc {
    name: Symbol
    type: Type
    items: EnumItem[]
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
    refEnum: Map<string, Enum>
    enums: Enum[]
    vars: Var[]
    includes: Symbol[]
    closureses: ClosuresDeclare[]
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

    hasLocal(name: string): boolean {
        return this._varSet.has(name)
    }

    set(name: Symbol, type: Type): void {
        this._varSet.set(name.name, { name: name, type: type })
    }

}

export class Closures {

    protected _typeSet: Map<string, Type>
    protected _keys: string[]

    readonly func: Function
    readonly declare: ClosuresDeclare

    constructor(func: Function, declare: ClosuresDeclare) {
        this.func = func
        this.declare = declare
        this._typeSet = new Map<string, Type>()
        this._keys = []
    }

    add(key: string, type: Type): Type {
        if (this._typeSet.has(key)) {
            return this._typeSet.get(key)!
        }
        let t: any = {}
        for (let key in type) {
            t[key] = (type as any)[key]
        }
        t.closures = this
        t.index = this._keys.length
        this._typeSet.set(key, t)
        this._keys.push(key)
        return t
    }

    get keys(): string[] {
        return this._keys
    }

    get(key: string): Type | undefined {
        return this._typeSet.get(key)
    }

}   