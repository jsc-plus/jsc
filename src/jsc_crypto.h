#ifndef jsc_crypto_h
#define jsc_crypto_h

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @value "UTF-8"
     */
    extern jsc_string_t jsc_crypto_UTF8;
    jsc_object_t * jsc_crypto_encode(jsc_object_t * data, jsc_string_t charset);
    jsc_object_t * jsc_crypto_encodeString(jsc_string_t s, jsc_string_t charset);
    jsc_object_t * jsc_crypto_decode(jsc_object_t * data, jsc_string_t charset);
    jsc_string_t jsc_crypto_decodeString(jsc_object_t * data, jsc_string_t charset);

#ifdef __cplusplus
}
#endif

#endif

