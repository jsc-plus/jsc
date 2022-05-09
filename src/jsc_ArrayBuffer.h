//
//  jsc_ArrayBuffer.h
//  jsc
//
//  Created by 张海龙 on 2022/5/4.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#ifndef jsc_ArrayBuffer_h
#define jsc_ArrayBuffer_h


#ifdef __cplusplus
extern "C" {
#endif

    struct jsc_ArrayBuffer_t;

    typedef jsc_int_t (*jsc_ArrayBuffer_byteLength_t)(jsc_class_t * isa, jsc_object_t * object);
    typedef struct jsc_ArrayBuffer_t * (*jsc_ArrayBuffer_slice_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t begin,jsc_int_t end);
    typedef jsc_int_t (*jsc_ArrayBuffer_copy_t)(jsc_class_t * isa, jsc_object_t * object, jsc_object_t * dst,jsc_int_t begin,jsc_int_t end);

    typedef struct jsc_ArrayBuffer_class_t {
        jsc_class_t base;
        jsc_ArrayBuffer_byteLength_t byteLength;
        jsc_ArrayBuffer_slice_t slice;
        jsc_ArrayBuffer_copy_t copy;
    } jsc_ArrayBuffer_class_t;

    extern jsc_ArrayBuffer_class_t jsc_ArrayBuffer;

    typedef struct jsc_ArrayBuffer_t {
        jsc_object_t base;
        jsc_ubyte_t * _data;
        jsc_int_t _byteLength;
    } jsc_ArrayBuffer_t;

    jsc_int_t jsc_ArrayBuffer_byteLength_(jsc_class_t * isa, jsc_object_t * object);
    struct jsc_ArrayBuffer_t * jsc_ArrayBuffer_slice_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t begin,jsc_int_t end);
    jsc_int_t jsc_ArrayBuffer_copy_(jsc_class_t * isa, jsc_object_t * object, jsc_object_t * dst,jsc_int_t begin,jsc_int_t end);

    jsc_int_t jsc_ArrayBuffer_byteLength(jsc_object_t * object);
    struct jsc_ArrayBuffer_t * jsc_ArrayBuffer_slice(jsc_object_t * object,jsc_int_t begin,jsc_int_t end);
    jsc_int_t jsc_ArrayBuffer_copy(jsc_object_t * object, jsc_object_t * dst,jsc_int_t begin,jsc_int_t end);

    struct jsc_ArrayBuffer_t * jsc_ArrayBuffer_alloc(jsc_int_t length);
    struct jsc_ArrayBuffer_t * jsc_ArrayBuffer_new(jsc_int_t length);

#ifdef __cplusplus
}
#endif

#endif /* jsc_ArrayBuffer_h */
