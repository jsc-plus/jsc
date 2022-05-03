//
//  jsc_Map.h
//  jsc
//
//  Created by 张海龙 on 2022/5/3.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#ifndef jsc_Map_h
#define jsc_Map_h

#ifdef __cplusplus
extern "C" {
#endif

    struct jsc_Map_t;
    struct jsc_variant_t;
    struct jsc_Iterator_t;

    typedef jsc_int_t (*jsc_Map_size_t)(jsc_class_t * isa, jsc_object_t * object);
    typedef struct jsc_variant_t (*jsc_Map___index_t)(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key);
    typedef void (*jsc_Map___newindex_t)(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key,struct jsc_variant_t value);
    typedef void (*jsc_Map_clear_t)(jsc_class_t * isa, jsc_object_t * object);
    typedef void (*jsc_Map_del_t)(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key);
    typedef struct jsc_variant_t (*jsc_Map_get_t)(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key);
    typedef jsc_boolean_t (*jsc_Map_has_t)(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key);
    typedef void (*jsc_Map_set_t)(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key,struct jsc_variant_t value);
    typedef struct jsc_Iterator_t * (*jsc_Map_Iterator_t)(jsc_class_t * isa, jsc_object_t * object);

    typedef struct jsc_Map_class_t {
        jsc_class_t base;
        jsc_Map_size_t size;
        jsc_Map___index_t __index;
        jsc_Map___newindex_t __newindex;
        jsc_Map_clear_t clear;
        jsc_Map_del_t del;
        jsc_Map_get_t get;
        jsc_Map_has_t has;
        jsc_Map_set_t set;
        jsc_Map_Iterator_t iterator;
    } jsc_Map_class_t;

    extern jsc_Map_class_t jsc_Map;

    typedef struct jsc_Map_t {
        jsc_object_t base;
        void * _internal;
    } jsc_Map_t;

    jsc_int_t jsc_Map_size_(jsc_class_t * isa, jsc_object_t * object);
    struct jsc_variant_t jsc_Map___index_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key);
    void jsc_Map___newindex_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key,struct jsc_variant_t value);
    void jsc_Map_clear_(jsc_class_t * isa, jsc_object_t * object);
    void jsc_Map_del_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key);
    struct jsc_variant_t jsc_Map_get_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key);
    jsc_boolean_t jsc_Map_has_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key);
    void jsc_Map_set_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key,struct jsc_variant_t value);
    struct jsc_Iterator_t * jsc_Map_iterator_(jsc_class_t * isa, jsc_object_t * object);

    jsc_int_t jsc_Map_size(jsc_object_t * object);
    struct jsc_variant_t jsc_Map___index(jsc_object_t * object,struct jsc_variant_t key);
    void jsc_Map___newindex(jsc_object_t * object,struct jsc_variant_t key,struct jsc_variant_t value);
    void jsc_Map_clear(jsc_object_t * object);
    void jsc_Map_del(jsc_object_t * object,struct jsc_variant_t key);
    struct jsc_variant_t jsc_Map_get(jsc_object_t * object,struct jsc_variant_t key);
    jsc_boolean_t jsc_Map_has(jsc_object_t * object,struct jsc_variant_t key);
    void jsc_Map_set(jsc_object_t * object,struct jsc_variant_t key,struct jsc_variant_t value);
    struct jsc_Iterator_t * jsc_Map_iterator(jsc_object_t * object);


#ifdef __cplusplus
}
#endif

#endif /* jsc_Map_hpp */
