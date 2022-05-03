//
//  jsc_Set.h
//  jsc
//
//  Created by 张海龙 on 2022/5/3.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#ifndef jsc_Set_h
#define jsc_Set_h

#ifdef __cplusplus
extern "C" {
#endif

    struct jsc_Set_t;
    struct jsc_variant_t;
    struct jsc_Iterator_t;

    typedef jsc_int_t (*jsc_Set_size_t)(jsc_class_t * isa, jsc_object_t * object);
    typedef void (*jsc_Set_clear_t)(jsc_class_t * isa, jsc_object_t * object);
    typedef void (*jsc_Set_del_t)(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t value);
    typedef jsc_boolean_t (*jsc_Set_has_t)(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t value);
    typedef void (*jsc_Set_add_t)(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t value);
    typedef struct jsc_Iterator_t * (*jsc_Set_Iterator_t)(jsc_class_t * isa, jsc_object_t * object);

    typedef struct jsc_Set_class_t {
        jsc_class_t base;
        jsc_Set_size_t size;
        jsc_Set_clear_t clear;
        jsc_Set_del_t del;
        jsc_Set_has_t has;
        jsc_Set_add_t add;
        jsc_Set_Iterator_t iterator;
    } jsc_Set_class_t;

    extern jsc_Set_class_t jsc_Set;

    typedef struct jsc_Set_t {
        jsc_object_t base;
        void * _internal;
    } jsc_Set_t;

    jsc_int_t jsc_Set_size_(jsc_class_t * isa, jsc_object_t * object);
    void jsc_Set_clear_(jsc_class_t * isa, jsc_object_t * object);
    void jsc_Set_del_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t value);
    jsc_boolean_t jsc_Set_has_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t value);
    void jsc_Set_add_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t value);
    struct jsc_Iterator_t * jsc_Set_iterator_(jsc_class_t * isa, jsc_object_t * object);

    jsc_int_t jsc_Set_size(jsc_object_t * object);
    void jsc_Set_clear(jsc_object_t * object);
    void jsc_Set_del(jsc_object_t * object,struct jsc_variant_t value);
    jsc_boolean_t jsc_Set_has(jsc_object_t * object,struct jsc_variant_t value);
    void jsc_Set_add(jsc_object_t * object,struct jsc_variant_t value);
    struct jsc_Iterator_t * jsc_Set_iterator(jsc_object_t * object);


#ifdef __cplusplus
}
#endif

#endif /* jsc_Set_hpp */
