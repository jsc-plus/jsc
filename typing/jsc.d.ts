
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
    type int8 = number

    /**
     * B
     */
    type ubyte = number
    type uint8 = number

    /**
     * 弱引用
     */
    type weak = any

    /**
     * C 字符串
     */
    type CString = string

    class DataView {

        constructor(buffer: ArrayBuffer, byteOffset?: number, byteLength?: number);

        readonly buffer: ArrayBuffer;
        readonly byteLength: number;
        readonly byteOffset: number;
        /**
         * Gets the Float32 value at the specified byte offset from the start of the view. There is
         * no alignment constraint; multi-byte values may be fetched from any offset.
         * @param byteOffset The place in the buffer at which the value should be retrieved.
         */
        getFloat32(byteOffset: number, littleEndian?: boolean): number;

        /**
         * Gets the Float64 value at the specified byte offset from the start of the view. There is
         * no alignment constraint; multi-byte values may be fetched from any offset.
         * @param byteOffset The place in the buffer at which the value should be retrieved.
         */
        getFloat64(byteOffset: number, littleEndian?: boolean): number;

        /**
         * Gets the Int8 value at the specified byte offset from the start of the view. There is
         * no alignment constraint; multi-byte values may be fetched from any offset.
         * @param byteOffset The place in the buffer at which the value should be retrieved.
         */
        getInt8(byteOffset: number): number;

        /**
         * Gets the Int16 value at the specified byte offset from the start of the view. There is
         * no alignment constraint; multi-byte values may be fetched from any offset.
         * @param byteOffset The place in the buffer at which the value should be retrieved.
         */
        getInt16(byteOffset: number, littleEndian?: boolean): number;
        /**
         * Gets the Int32 value at the specified byte offset from the start of the view. There is
         * no alignment constraint; multi-byte values may be fetched from any offset.
         * @param byteOffset The place in the buffer at which the value should be retrieved.
         */
        getInt32(byteOffset: number, littleEndian?: boolean): number;

        /**
         * Gets the Uint8 value at the specified byte offset from the start of the view. There is
         * no alignment constraint; multi-byte values may be fetched from any offset.
         * @param byteOffset The place in the buffer at which the value should be retrieved.
         */
        getUint8(byteOffset: number): number;

        /**
         * Gets the Uint16 value at the specified byte offset from the start of the view. There is
         * no alignment constraint; multi-byte values may be fetched from any offset.
         * @param byteOffset The place in the buffer at which the value should be retrieved.
         */
        getUint16(byteOffset: number, littleEndian?: boolean): number;

        /**
         * Gets the Uint32 value at the specified byte offset from the start of the view. There is
         * no alignment constraint; multi-byte values may be fetched from any offset.
         * @param byteOffset The place in the buffer at which the value should be retrieved.
         */
        getUint32(byteOffset: number, littleEndian?: boolean): number;

        /**
         * Stores an Float32 value at the specified byte offset from the start of the view.
         * @param byteOffset The place in the buffer at which the value should be set.
         * @param value The value to set.
         * @param littleEndian If false or undefined, a big-endian value should be written,
         * otherwise a little-endian value should be written.
         */
        setFloat32(byteOffset: number, value: number, littleEndian?: boolean): void;

        /**
         * Stores an Float64 value at the specified byte offset from the start of the view.
         * @param byteOffset The place in the buffer at which the value should be set.
         * @param value The value to set.
         * @param littleEndian If false or undefined, a big-endian value should be written,
         * otherwise a little-endian value should be written.
         */
        setFloat64(byteOffset: number, value: number, littleEndian?: boolean): void;

        /**
         * Stores an Int8 value at the specified byte offset from the start of the view.
         * @param byteOffset The place in the buffer at which the value should be set.
         * @param value The value to set.
         */
        setInt8(byteOffset: number, value: number): void;

        /**
         * Stores an Int16 value at the specified byte offset from the start of the view.
         * @param byteOffset The place in the buffer at which the value should be set.
         * @param value The value to set.
         * @param littleEndian If false or undefined, a big-endian value should be written,
         * otherwise a little-endian value should be written.
         */
        setInt16(byteOffset: number, value: number, littleEndian?: boolean): void;

        /**
         * Stores an Int32 value at the specified byte offset from the start of the view.
         * @param byteOffset The place in the buffer at which the value should be set.
         * @param value The value to set.
         * @param littleEndian If false or undefined, a big-endian value should be written,
         * otherwise a little-endian value should be written.
         */
        setInt32(byteOffset: number, value: number, littleEndian?: boolean): void;

        /**
         * Stores an Uint8 value at the specified byte offset from the start of the view.
         * @param byteOffset The place in the buffer at which the value should be set.
         * @param value The value to set.
         */
        setUint8(byteOffset: number, value: number): void;

        /**
         * Stores an Uint16 value at the specified byte offset from the start of the view.
         * @param byteOffset The place in the buffer at which the value should be set.
         * @param value The value to set.
         * @param littleEndian If false or undefined, a big-endian value should be written,
         * otherwise a little-endian value should be written.
         */
        setUint16(byteOffset: number, value: number, littleEndian?: boolean): void;

        /**
         * Stores an Uint32 value at the specified byte offset from the start of the view.
         * @param byteOffset The place in the buffer at which the value should be set.
         * @param value The value to set.
         * @param littleEndian If false or undefined, a big-endian value should be written,
         * otherwise a little-endian value should be written.
         */
        setUint32(byteOffset: number, value: number, littleEndian?: boolean): void;

        getString(byteOffset: number): string | undefined;

        setString(byteOffset: number, value: string): jsc.int

        getData(byteOffset: number, data: DataView): jsc.int

        setData(byteOffset: number, data: DataView): jsc.int
        
    }

    class ArrayBuffer {

        constructor(byteLength: number);

        /**
        * Read-only. The length of the ArrayBuffer (in bytes).
        */
        readonly byteLength: number;
        /**
         * Returns a section of an ArrayBuffer.
         */
        slice(begin: number, end?: number): ArrayBuffer;

        copy(dst: DataView, begin: number, end?: number): jsc.int;
    }

    function log(format: string, ...args: any[]): void

}