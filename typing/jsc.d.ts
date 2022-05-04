
declare namespace jsc {

    /**
     * s
     * type string
     */

    /**
     * z
     * type boolean
     */

    /**
     * i
     */
    type int = number

    /**
     * I
     */
    type uint = number

    /**
     * l
     */
    type long = number

    /**
     * L
     */
    type ulong = number

    /**
     * i32
     */
    type int32 = number

    /**
     * I32
     */
    type uint32 = number

    /**
     * i16
     */
    type int16 = number

    /**
     * I16
     */
    type uint16 = number

    /**
     * i64
     */
    type int64 = number | string

    /**
     * I64
     */
    type uint64 = number | string

    /**
     * f
     */
    type float = number

    /**
     * d
     */
    type double = number

    /**
     * f32
     */
    type float32 = number

    /**
     * f64
     */
    type float64 = number

    /**
     * p
     */
    type ptr = any

    /**
     * b
     */
    type byte = number

    /**
     * B
     */
    type ubyte = number

    /**
     * 弱引用
     */
    type weak = any

    class Class {
        readonly isa?: Class
        readonly name: string
        readonly size: int
        isKindOf(isa?: Class): boolean
    }

    class Object {
        readonly isa: Class
        readonly retainCount: int
        isKindOf(isa?: Class): boolean
        toString(): string
        hashCode(): ulong
        compare(b: Object): long
        toInt64(): int64
        toFloat64(): float64
        toBoolean(): boolean
    }

    function log(format: string, ...args: any[]): void

}
