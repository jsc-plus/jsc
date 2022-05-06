//
//  jsc_variant.h
//  jsc
//
//  Created by 张海龙 on 2022/1/14.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#ifndef jsc_variant_h
#define jsc_variant_h

#ifdef __cplusplus
extern "C" {
#endif
    
    struct jsc_object_t;
    struct jsc_buffer_t;

    enum {
        JSC_VARIANT_TYPE_NIL,
        JSC_VARIANT_TYPE_INT8,
        JSC_VARIANT_TYPE_UINT8,
        JSC_VARIANT_TYPE_INT16,
        JSC_VARIANT_TYPE_UINT16,
        JSC_VARIANT_TYPE_INT32,
        JSC_VARIANT_TYPE_UINT32,
        JSC_VARIANT_TYPE_INT64,
        JSC_VARIANT_TYPE_UINT64,
        JSC_VARIANT_TYPE_INT,
        JSC_VARIANT_TYPE_UINT,
        JSC_VARIANT_TYPE_LONG,
        JSC_VARIANT_TYPE_ULONG,
        JSC_VARIANT_TYPE_FLOAT32,
        JSC_VARIANT_TYPE_FLOAT64,
        JSC_VARIANT_TYPE_BOOLEAN,
        JSC_VARIANT_TYPE_UNICHAR,
        JSC_VARIANT_TYPE_STRING,
        JSC_VARIANT_TYPE_OBJECT,
    };

    typedef jsc_ubyte_t jsc_variant_type_t;

    typedef struct jsc_variant_t {
        jsc_variant_type_t type;
        union {
            jsc_byte_t int8Value;
            jsc_ubyte_t uint8Value;
            jsc_int16_t int16Value;
            jsc_uint16_t uint16Value;
            jsc_int32_t int32Value;
            jsc_uint32_t uint32Value;
            jsc_int64_t int64Value;
            jsc_uint64_t uint64Value;
            jsc_int_t intValue;
            jsc_uint_t uintValue;
            jsc_long_t longValue;
            jsc_ulong_t ulongValue;
            jsc_float32_t float32Value;
            jsc_float64_t float64Value;
            jsc_boolean_t booleanValue;
            jsc_string_t stringValue;
            jsc_unichar_t unicharValue;
        };
        struct jsc_object_t * objectValue;
    } jsc_variant_t;

    extern jsc_variant_t const jsc_Nil;

    inline static struct jsc_variant_t jsc_variant_Object(struct jsc_object_t * object) {
        jsc_variant_t v;
        if(object == NULL) {
            v.type = JSC_VARIANT_TYPE_NIL;
            v.uint64Value = 0;
            v.objectValue = NULL;
        } else {
            v.type = JSC_VARIANT_TYPE_OBJECT;
            v.uint64Value = 0;
            v.objectValue = object;
        }
        return v;
    }

    inline static struct jsc_variant_t jsc_variant_CString(jsc_string_t s) {
        jsc_variant_t v;
        if(s == NULL) {
            v.type = JSC_VARIANT_TYPE_NIL;
            v.uint64Value = 0;
            v.objectValue = NULL;
        } else {
            v.type = JSC_VARIANT_TYPE_STRING;
            v.stringValue = s;
            v.objectValue = NULL;
        }
        return v;
    }

    jsc_string_t jsc_variant_toCStringWithBuffer(struct jsc_variant_t v,struct jsc_buffer_t * buf);
    jsc_string_t jsc_variant_toCString(struct jsc_variant_t v);
    jsc_float64_t jsc_variant_toFloat64(struct jsc_variant_t v);
    jsc_int64_t jsc_variant_toInt64(struct jsc_variant_t v);
    jsc_boolean_t jsc_variant_toBoolean(struct jsc_variant_t v);
    jsc_long_t jsc_variant_compare(struct jsc_variant_t a,struct jsc_variant_t b);
    jsc_ulong_t jsc_variant_hashCode(struct jsc_variant_t a);
    struct jsc_object_t * jsc_variant_toObject(struct jsc_variant_t v);
    void jsc_variant_setStrong(struct jsc_variant_t * a,struct jsc_variant_t v);
    struct jsc_variant_t jsc_variant_getStrong(struct jsc_variant_t v);

#ifdef __cplusplus
}
#endif

#endif /* jsc_variant_h */
