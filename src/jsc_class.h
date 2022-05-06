//
//  jsc_class.h
//  jsc
//
//  Created by 张海龙 on 2022/1/12.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#ifndef jsc_class_h
#define jsc_class_h


#ifdef __cplusplus
extern "C" {
#endif
    
    struct jsc_class_t;
    struct jsc_object_t;
    struct jsc_weak_t;
    struct jsc_String_t;

    typedef void (*jsc_object_alloc_t)(struct jsc_class_t * isa, struct jsc_object_t * object);
    typedef void (*jsc_object_dealloc_t)(struct jsc_class_t * isa, struct jsc_object_t * object);
    typedef jsc_ulong_t (*jsc_object_hashCode_t)(struct jsc_class_t * isa, struct jsc_object_t * object);
    typedef jsc_long_t (*jsc_object_compare_t)(struct jsc_class_t * isa, struct jsc_object_t * object,struct jsc_object_t * v);
    typedef struct jsc_String_t * (*jsc_object_toString_t)(struct jsc_class_t * isa, struct jsc_object_t * object);
    typedef jsc_int64_t (*jsc_object_toInt64_t)(struct jsc_class_t * isa, struct jsc_object_t * object);
    typedef jsc_float64_t (*jsc_object_toFloat64_t)(struct jsc_class_t * isa, struct jsc_object_t * object);
    typedef jsc_boolean_t (*jsc_object_toBoolean_t)(struct jsc_class_t * isa, struct jsc_object_t * object);

    typedef struct jsc_class_t {
        struct jsc_class_t * isa;
        jsc_int_t size;
        jsc_string_t name;
        jsc_object_alloc_t alloc;
        jsc_object_dealloc_t dealloc;
        jsc_object_hashCode_t hashCode;
        jsc_object_compare_t compare;
        jsc_object_toString_t toString;
        jsc_object_toInt64_t toInt64;
        jsc_object_toFloat64_t toFloat64;
        jsc_object_toBoolean_t toBoolean;
    } jsc_class_t;

    typedef struct jsc_object_t {
        struct jsc_class_t * isa;
        jsc_int_t retainCount;
        struct jsc_weak_t * weak;
    } jsc_object_t;

    extern jsc_class_t jsc_Object;

    jsc_object_t * jsc_object_alloc(jsc_class_t * isa,jsc_int_t extraSize);

    void jsc_object_retain(jsc_object_t * v);

    void jsc_object_release(jsc_object_t * v);

    void jsc_object_weak(jsc_object_t * v , jsc_object_t ** dst);
    
    void jsc_object_unWeak(jsc_object_t * v, jsc_object_t ** dst);

    jsc_object_t * jsc_setStrong(jsc_object_t ** dst, jsc_object_t * src);
    
    jsc_object_t * jsc_setWeak(jsc_object_t ** dst, jsc_object_t * src);
    
    jsc_boolean_t jsc_class_isKind(jsc_class_t * isa, jsc_class_t * dst);

    void jsc_initialize(void);

    
    /* autorelease */
    jsc_object_t * jsc_object_new(jsc_class_t * isa,jsc_int_t extraSize);
    void jsc_object_autorelease(jsc_object_t * v);
    void jsc_autorelease_pool_begin(void);
    void jsc_autorelease_pool_end(void);

    /* hasCode,compare */
    jsc_ulong_t jsc_object_hashCode_(jsc_class_t * isa, jsc_object_t * object);
    jsc_long_t jsc_object_compare_(jsc_class_t * isa, jsc_object_t * object,jsc_object_t * v);
    jsc_ulong_t jsc_object_hashCode(jsc_object_t * object);
    jsc_long_t jsc_object_compare(jsc_object_t * object,jsc_object_t * v);

    /* toString */
    struct jsc_String_t * jsc_object_toString_(jsc_class_t * isa,jsc_object_t * object);
    struct jsc_String_t * jsc_object_toString(jsc_object_t * object);

    /* toInt64 */
    jsc_int64_t jsc_object_toInt64_(jsc_class_t * isa,jsc_object_t * object);
    jsc_int64_t jsc_object_toInt64(jsc_object_t * object);

    /* toFloat64 */
    jsc_float64_t jsc_object_toFloat64_(jsc_class_t * isa,jsc_object_t * object);
    jsc_float64_t jsc_object_toFloat64(jsc_object_t * object);

    /* toBoolean */
    jsc_boolean_t jsc_object_toBoolean_(jsc_class_t * isa,jsc_object_t * object);
    jsc_boolean_t jsc_object_toBoolean(jsc_object_t * object);
    
#ifdef __cplusplus
}
#endif

#endif /* jsc_class_h */
