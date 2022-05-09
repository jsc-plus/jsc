
declare namespace jsc {


    namespace crypto {

        /**
         * @value "UTF-8"
         */
        const UTF8: jsc.CString

        function encode(data: DataView, charset: string): ArrayBuffer
        function encodeString(s: string, charset: string): ArrayBuffer

        function decode(data: DataView, charset: string): ArrayBuffer
        function decodeString(data: DataView, charset: string): string

    }

}