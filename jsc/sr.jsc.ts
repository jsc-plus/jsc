
export enum Type {
    NIL,
    INT8,
    UINT8,
    INT16,
    UINT16,
    INT32,
    UINT32,
    FLOAT32,
    FLOAT64,
    BOOLEAN,
    STRING,
    BYTES,
    OBJECT,
    ARRAY,
    END,
}

export enum Error {
    NONE,
    EOF,
    STREAM,
}

export class ChunkReadStream {

    protected _data: jsc.DataView
    protected _index: jsc.int
    protected _err: Error

    constructor(data: jsc.DataView) {
        this._data = data
        this._index = 0
        this._err = Error.NONE
    }

    err(): Error {
        return this._err;
    }

    valid(n: jsc.int): boolean {
        return this._err == Error.NONE && (this._index + n <= this._data.byteLength)
    }

    getInt8(): jsc.int8 {
        if (this.valid(1)) {
            let v: jsc.int8 = this._data.getInt8(this._index)
            this._index += 1
            return v
        }
        return 0;
    }

    getUint8(): jsc.uint8 {
        if (this.valid(1)) {
            let v: jsc.uint8 = this._data.getUint8(this._index)
            this._index += 1
            return v
        }
        return 0;
    }

    getInt16(): jsc.int16 {
        if (this.valid(2)) {
            let v: jsc.int16 = this._data.getInt16(this._index, true)
            this._index += 2
            return v
        }
        return 0;
    }

    getUint16(): jsc.uint16 {
        if (this.valid(2)) {
            let v: jsc.uint16 = this._data.getUint16(this._index, true)
            this._index += 2
            return v
        }
        return 0;
    }

    getInt32(): jsc.int32 {
        if (this.valid(4)) {
            let v: jsc.int32 = this._data.getInt32(this._index, true)
            this._index += 4
            return v
        }
        return 0;
    }

    getUint32(): jsc.uint32 {
        if (this.valid(4)) {
            let v: jsc.uint32 = this._data.getUint32(this._index, true)
            this._index += 4
            return v
        }
        return 0;
    }

    getFloat32(): jsc.float32 {
        if (this.valid(4)) {
            let v: jsc.float32 = this._data.getFloat32(this._index, true)
            this._index += 4
            return v
        }
        return 0;
    }

    getFloat64(): jsc.float64 {
        if (this.valid(8)) {
            let v: jsc.float32 = this._data.getFloat64(this._index, true)
            this._index += 8
            return v
        }
        return 0;
    }

    getString(): string | undefined {
        let n = this.getUint32()
        if (n > 0 && this.valid(n)) {
            let s = this._data.getString(this._index)
            this._index += n
            return s
        }
        return undefined
    }

    getBoolean(): boolean {
        return this.getUint8() != 0
    }

    getBytes(): jsc.DataView | undefined {
        let n = this.getUint32()
        if (n > 0 && this.valid(n)) {
            let v = new jsc.DataView(this._data.buffer, this._data.byteOffset + this._index, n)
            this._index += n
            return v
        }
        return undefined
    }

    getValue(): any {
        if (this.valid(1)) {
            return this.getValueWithType(this.getUint8())
        }
        return undefined;
    }

    getObject(): Map<string, any> {

        let m: Map<string, any> = new Map<string, any>();

        while (this.valid(1)) {
            let type = this.getUint8();
            if (type == Type.END) {
                break
            } else {
                if (type != Type.STRING) {
                    this._err = Error.STREAM
                    break
                }
                let key = this.getString()
                let value = this.getValue()
                if (key !== undefined && value !== undefined) {
                    m.set(key, value)
                }
            }
        }

        return m;
    }

    getArray(): any[] {

        let a: any[] = []

        while (this.valid(1)) {
            let type = this.getUint8();
            if (type == Type.END) {
                break
            } else {
                let value = this.getValueWithType(type)
                a.push(value)
            }
        }

        return a;
    }

    getValueWithType(type: jsc.uint8): any {
        switch (type) {
            case Type.NIL:
                break
            case Type.INT8:
                return this.getInt8()
            case Type.UINT8:
                return this.getUint8()
            case Type.INT16:
                return this.getInt16()
            case Type.UINT16:
                return this.getUint16()
            case Type.INT32:
                return this.getInt32()
            case Type.UINT32:
                return this.getUint32()
            case Type.FLOAT32:
                return this.getFloat32()
            case Type.FLOAT64:
                return this.getFloat64()
            case Type.BOOLEAN:
                return this.getBoolean()
            case Type.STRING:
                return this.getString()
            case Type.BYTES:
                return this.getBytes()
            case Type.OBJECT:
                return this.getObject()
            case Type.ARRAY:
                return this.getArray()
            default:
                this._err = Error.STREAM
                break
        }
        return undefined
    }

    seekInt8(): void {
        if (this.valid(1)) {
            this._index += 1
        }
    }

    seekUint8(): void {
        if (this.valid(1)) {
            this._index += 1
        }
    }

    seekInt16(): void {
        if (this.valid(2)) {
            this._index += 2
        }
    }

    seekUint16(): void {
        if (this.valid(2)) {
            this._index += 2
        }
    }

    seekInt32(): void {
        if (this.valid(4)) {
            this._index += 4
        }
    }

    seekUint32(): void {
        if (this.valid(4)) {
            this._index += 4
        }
    }

    seekFloat32(): void {
        if (this.valid(4)) {
            this._index += 4
        }
    }

    seekFloat64(): void {
        if (this.valid(8)) {
            this._index += 8
        }
    }

    seekString(): void {
        let n = this.getUint32();
        if (this.valid(n)) {
            this._index += n
        }
    }

    seekBoolean(): void {
        if (this.valid(1)) {
            this._index += 1
        }
    }

    seekBytes(): void {
        let n = this.getUint32();
        if (this.valid(n)) {
            this._index += n
        }
    }

    seekValue(): void {
        if (this.valid(1)) {
            this.seekValueWithType(this.getUint8())
        }
    }

    seekObject(): void {
        while (this.valid(1)) {
            let type = this.getUint8();
            if (type == Type.END) {
                break;
            } else {
                if (type != Type.STRING) {
                    this._err = Error.STREAM
                    break
                }
                this.seekString()
                this.seekValue()
            }
        }
    }

    seekArray(): void {
        while (this.valid(1)) {
            let type = this.getUint8();
            if (type == Type.END) {
                break;
            } else {
                this.seekValueWithType(type)
            }
        }
    }

    seekValueWithType(type: jsc.uint8): void {
        switch (type) {
            case Type.NIL:
                break
            case Type.INT8:
                this.seekInt8()
                break
            case Type.UINT8:
                this.seekUint8()
                break
            case Type.INT16:
                this.seekInt16()
                break
            case Type.UINT16:
                this.seekUint16()
                break
            case Type.INT32:
                this.seekInt32()
                break
            case Type.UINT32:
                this.seekUint32()
                break
            case Type.FLOAT32:
                this.seekFloat32()
                break
            case Type.FLOAT64:
                this.seekFloat64()
                break
            case Type.BOOLEAN:
                this.seekBoolean()
                break
            case Type.STRING:
                this.seekString()
                break
            case Type.BYTES:
                this.seekBytes()
                break
            case Type.OBJECT:
                this.seekObject()
                break
            case Type.ARRAY:
                this.seekArray()
                break
            default:
                this._err = Error.STREAM
                break
        }
    }

    offset(): jsc.int {
        return this._index
    }

    setOffset(off: jsc.int): void {
        this._index = off
    }
}

export class Buffer {

    protected _buffer: jsc.ArrayBuffer
    protected _view: jsc.DataView
    protected _length: jsc.int
    protected _capacity: jsc.int

    constructor(capacity: jsc.int) {
        this._capacity = capacity
        this._buffer = new jsc.ArrayBuffer(capacity)
        this._length = 0
        this._view = new jsc.DataView(this._buffer, 0, this._buffer.byteLength)
    }

    capacity(v: jsc.int): void {
        if (v > this._buffer.byteLength) {
            let n = Math.max(v, this._buffer.byteLength + this._capacity)
            let dst = new jsc.ArrayBuffer(n);
            let view = new jsc.DataView(dst, 0, dst.byteLength)
            this._buffer.copy(view, 0, this._buffer.byteLength)
            this._buffer = dst;
            this._view = view;
        }
    }

    length(): jsc.int {
        return this._length
    }

    setLength(v: jsc.int): void {
        this._length = v
        this.capacity(v)
    }

    toDataView(): jsc.DataView {
        return new jsc.DataView(this._buffer, 0, this._length)
    }

}


export class ChunkWriteStream extends Buffer {

    protected _err: Error

    constructor() {
        super(20480)
        this._err = Error.NONE
    }

    err(): Error {
        return this._err;
    }

    setInt8(v: jsc.int8): void {
        this.capacity(this._length + 1)
        this._view.setInt8(this._length, v)
        this._length += 1
    }

    setUint8(v: jsc.uint8): void {
        this.capacity(this._length + 1)
        this._view.setUint8(this._length, v)
        this._length += 1
    }

    setInt16(v: jsc.int16): void {
        this.capacity(this._length + 2)
        this._view.setInt16(this._length, v, true)
        this._length += 2
    }

    setUint16(v: jsc.uint16): void {
        this.capacity(this._length + 2)
        this._view.setUint16(this._length, v, true)
        this._length += 2
    }

    setInt32(v: jsc.int32): void {
        this.capacity(this._length + 4)
        this._view.setInt32(this._length, v, true)
        this._length += 4
    }

    setUint32(v: jsc.uint32): void {
        this.capacity(this._length + 4)
        this._view.setUint32(this._length, v, true)
        this._length += 4
    }

    setFloat32(v: jsc.float32): void {
        this.capacity(this._length + 4)
        this._view.setFloat32(this._length, v, true)
        this._length += 4
    }

    setFloat64(v: jsc.float32): void {
        this.capacity(this._length + 8)
        this._view.setFloat64(this._length, v, true)
        this._length += 8
    }

    setString(v: string): void {
        let b = jsc.crypto.encodeString(v, jsc.crypto.UTF8)
        this.setUint32(b.byteLength)
        this.capacity(this._length + b.byteLength + 1)
        this._view.setData(this._length, new jsc.DataView(b, 0, b.byteLength))
        this._length += b.byteLength
        this.setUint8(0)
    }

    setBoolean(v: boolean): void {
        this.setUint8(v ? 1 : 0)
    }

    setBytes(b: jsc.DataView): void {
        this.setUint32(b.byteLength)
        this.capacity(this._length + b.byteLength)
        this._view.setData(this._length, b)
        this._length += b.byteLength
    }

    setValue(v: any): void {
        if (jsc.Typeof.isInt8(v)) {
            this.setUint8(Type.INT8)
            this.setInt8(v)
        } else if (jsc.Typeof.isUint8(v)) {
            this.setUint8(Type.UINT8)
            this.setUint8(v)
        } else if (jsc.Typeof.isInt16(v)) {
            this.setUint8(Type.INT16)
            this.setInt16(v)
        } else if (jsc.Typeof.isUint16(v)) {
            this.setUint8(Type.UINT16)
            this.setUint16(v)
        } else if (jsc.Typeof.isInt32(v)) {
            this.setUint8(Type.INT32)
            this.setInt32(v)
        } else if (jsc.Typeof.isUint32(v)) {
            this.setUint8(Type.UINT32)
            this.setUint32(v)
        } else if (jsc.Typeof.isInt64(v) || jsc.Typeof.isUint16(v)) {
            this.setUint8(Type.STRING)
            this.setString(v)
        } else if (jsc.Typeof.isFloat32(v)) {
            this.setUint8(Type.FLOAT32)
            this.setFloat32(v)
        } else if (jsc.Typeof.isFloat64(v)) {
            this.setUint8(Type.FLOAT64)
            this.setFloat64(v)
        } else if (jsc.Typeof.isBoolean(v)) {
            this.setUint8(Type.BOOLEAN)
            this.setBoolean(v)
        } else if (jsc.Typeof.isUnichar(v)) {
            this.setUint8(Type.UINT16)
            this.setUint16(v)
        } else if (jsc.Typeof.isString(v)) {
            this.setUint8(Type.STRING)
            this.setString(v)
        } else if(v instanceof Array) {
            this.setUint8(Type.ARRAY)
            this.setArray(v)
        } else if(v instanceof Map) {
            this.setUint8(Type.OBJECT)
            this.setObject(v)
        } else if(v instanceof jsc.DataView) {
            this.setUint8(Type.BYTES)
            this.setBytes(v)
        } else {
            this.setUint8(Type.NIL)
        }
    }

    setObject(v: Map<string, any>): void {

    }

    setArray(v: any[]): void {
    }

}
