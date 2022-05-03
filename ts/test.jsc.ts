

class A extends jsc.Object {

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


export function main() {

    let a = new A();
    let b = new B();

    a.test();

    b.test();

}

