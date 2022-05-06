
declare namespace jsc {

    namespace fs {

        const O_CREAT: jsc.int
        const O_APPEND: jsc.int
        const O_RDONLY: jsc.int
        const O_WRONLY: jsc.int
        const O_RDWR: jsc.int

        const SEEK_SET: jsc.int
        const SEEK_CUR: jsc.int
        const SEEK_END: jsc.int


        class Stat {
            protected _size: jsc.ulong
            protected _isDir: boolean
            protected _mtime: jsc.ulong
            size(): jsc.ulong
            isDir(): boolean
            mtime(): jsc.ulong
        }

        function stat(path: string): Stat | undefined

        class File {
            protected _fd: jsc.int
            fd(): jsc.int
            close(): void
            read(data: DataView): jsc.long
            seek(off: jsc.long, mode: jsc.int): jsc.long
            write(data: DataView): jsc.long
        }

        function open(path: string, flag: jsc.int, perm: jsc.int): File | undefined
    }
}