

class A {

    test(): void {
        jsc.log("A test")
    }
}

class B extends A {

    test(): void {
        super.test()
        jsc.log("B test")
    }
}

var _dir: string

export type CallContext = (id: jsc.uint64, data: ArrayBuffer) => ArrayBuffer

export function entrypoint(callContext: CallContext, id: jsc.uint64, data: ArrayBuffer): ArrayBuffer {
    return new ArrayBuffer(0)
}

export function init(dir: string): void {
    _dir = dir
}

export function exit(): void {

}

export function lowMemory(): void {

}


export function main() {

    let a = new A();
    let b = new B();
    let i = 0;

    jsc.log("a.test %s %d %s %d >>", a, a, 2 + 3 - 4 / 2 * 4 % 2 + "px", ++i)

    a.test();

    jsc.log("b.test %s %d >>", b, ++i)
    b.test();

    let done = ()=>{
        a.test();
        b.test();
    };

    done();
}
