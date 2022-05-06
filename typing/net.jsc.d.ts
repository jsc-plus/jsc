
declare namespace jsc {

    namespace net {

        const AF_INET: jsc.int
        const AF_INET6: jsc.int
        const AF_UNIX: jsc.int

        const EV_READ: jsc.int
        const EV_WRITE: jsc.int

        const SOCK_STREAM: jsc.int
        const SOCK_DGRAM: jsc.int
        const SOCK_RAW: jsc.int


        function createAddr(s: string, port: jsc.int): ArrayBuffer
        function getAddrFamily(s: ArrayBuffer): jsc.int
        function getAddrPort(s: ArrayBuffer): jsc.int
        function getAddrString(s: ArrayBuffer): string

        function resolve(s: string, port: jsc.int): ArrayBuffer | undefined

        class Socket {
            protected _fd: jsc.int
            bind(addr: ArrayBuffer): jsc.int
            connect(addr: ArrayBuffer): jsc.int
            listen(block: jsc.int): jsc.int
            accept(addr: ArrayBuffer): Socket | undefined
            nonblock(v: boolean): jsc.int
            keepalive(enabled: boolean, idle: jsc.int, interval: jsc.int, count: jsc.int): jsc.int
            broadcast(v: boolean): jsc.int
            bufsize(recvbuf: jsc.int, sendbuf: jsc.int): jsc.int
            select(types: jsc.int, tv: jsc.int): jsc.int
            send(data: DataView): jsc.int
            recv(data: DataView): jsc.int
            sendto(addr: ArrayBuffer, data: DataView): jsc.int
            recvfrom(addr: ArrayBuffer, data: DataView): jsc.int
            fd(): jsc.int
            valid(): boolean
            addr(): ArrayBuffer
            close(): void
        }

        function createSocket(family: jsc.int, type: jsc.int, protocol: jsc.int): Socket | undefined
    }
}