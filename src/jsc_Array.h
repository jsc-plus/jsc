//
//  jsc_Array.h
//  jsc
//
//  Created by 张海龙 on 2022/1/14.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#ifndef jsc_Array_h
#define jsc_Array_h

#ifdef __cplusplus
extern "C" {
#endif

    struct jsc_Array_t;
    struct jsc_String_t;
    struct jsc_variant_t;

    typedef jsc_int_t (*jsc_Array_length_t)(jsc_class_t * isa, jsc_object_t * object);
    typedef struct jsc_variant_t (*jsc_Array___index_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index);
    typedef void (*jsc_Array___newindex_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index,struct jsc_variant_t v);
    typedef void (*jsc_Array_push_t)(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t v);
    typedef struct jsc_variant_t (*jsc_Array_pop_t)(jsc_class_t * isa, jsc_object_t * object);
    typedef struct jsc_variant_t (*jsc_Array_shift_t)(jsc_class_t * isa, jsc_object_t * object);
    typedef void (*jsc_Array_unshift_t)(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t v);
    typedef void (*jsc_Array_splice_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index,jsc_int_t count);
    typedef struct jsc_Array_t * (*jsc_Array_slice_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t start,jsc_int_t end);
    typedef struct jsc_String_t * (*jsc_Array_join_t)(jsc_class_t * isa, jsc_object_t * object,jsc_string_t separator);
    typedef jsc_int_t (*jsc_Array_indexOf_t)(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t v);
    typedef struct jsc_Iterator_t * (*jsc_Array_Iterator_t)(jsc_class_t * isa, jsc_object_t * object);

    typedef struct jsc_Array_class_t {
        jsc_class_t base;
        jsc_Array_length_t length;
        jsc_Array___index_t __index;
        jsc_Array___newindex_t __newindex;
        jsc_Array_push_t push;
        jsc_Array_pop_t pop;
        jsc_Array_shift_t shift;
        jsc_Array_unshift_t unshift;
        jsc_Array_splice_t splice;
        jsc_Array_slice_t slice;
        jsc_Array_join_t join;
        jsc_Array_indexOf_t indexOf;
        jsc_Array_Iterator_t iterator;
    } jsc_Array_class_t;

    extern jsc_Array_class_t jsc_Array;
    
    typedef struct jsc_Array_t {
        jsc_object_t base;
        struct jsc_variant_t * _items;
        jsc_int_t _size;
        jsc_int_t _length;
    } jsc_Array_t;

    jsc_int_t jsc_Array_length_(jsc_class_t * isa, jsc_object_t * object);
    struct jsc_variant_t jsc_Array___index_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index);
    void jsc_Array___newindex_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index,struct jsc_variant_t v);
    void jsc_Array_push_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t v);
    struct jsc_variant_t jsc_Array_pop_(jsc_class_t * isa, jsc_object_t * object);
    struct jsc_variant_t jsc_Array_shift_(jsc_class_t * isa, jsc_object_t * object);
    void jsc_Array_unshift_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t v);
    void jsc_Array_splice_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index,jsc_int_t count);
    jsc_Array_t * jsc_Array_slice_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t start,jsc_int_t end);
    struct jsc_String_t * jsc_Array_join_(jsc_class_t * isa, jsc_object_t * object,jsc_string_t separator);
    jsc_int_t jsc_Array_indexOf_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t v);
    struct jsc_Iterator_t * jsc_Array_Iterator_(jsc_class_t * isa, jsc_object_t * object);

    jsc_int_t jsc_Array_length(jsc_object_t * object);
    struct jsc_variant_t jsc_Array___index(jsc_object_t * object,jsc_int_t index);
    void jsc_Array___newindex(jsc_object_t * object,jsc_int_t index,struct jsc_variant_t v);
    void jsc_Array_push(jsc_object_t * object,struct jsc_variant_t v);
    struct jsc_variant_t jsc_Array_pop(jsc_object_t * object);
    struct jsc_variant_t jsc_Array_shift(jsc_object_t * object);
    void jsc_Array_unshift(jsc_object_t * object,struct jsc_variant_t v);
    void jsc_Array_splice(jsc_object_t * object,jsc_int_t index,jsc_int_t count);
    jsc_Array_t * jsc_Array_slice(jsc_object_t * object,jsc_int_t start,jsc_int_t end);
    struct jsc_String_t * jsc_Array_join(jsc_object_t * object,jsc_string_t separator);
    jsc_int_t jsc_Array_indexOf(jsc_object_t * object,struct jsc_variant_t v);
    struct jsc_Iterator_t * jsc_Array_Iterator(jsc_object_t * object);

#ifdef __cplusplus
}
#endif


#endif /* jsc_Array_h */
