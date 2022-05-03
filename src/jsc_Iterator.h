//
//  jsc_Iterator.h
//  jsc
//
//  Created by 张海龙 on 2022/5/3.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#ifndef jsc_Iterator_h
#define jsc_Iterator_h


#ifdef __cplusplus
extern "C" {
#endif
    
    struct jsc_Iterator_t;
    struct jsc_variant_t;
    struct jsc_IteratorEntity_t;
    
    typedef const struct jsc_IteratorEntity_t * (*jsc_Iterator_next_t)(jsc_class_t * isa, jsc_object_t * object);

    typedef struct jsc_Iterator_class_t {
        jsc_class_t base;
        jsc_Iterator_next_t next;
    } jsc_Iterator_class_t;

    extern jsc_Iterator_class_t jsc_Iterator;
    
    typedef struct jsc_IteratorEntity_t {
        struct jsc_variant_t key;
        struct jsc_variant_t value;
    } jsc_IteratorEntity_t;

    typedef struct jsc_Iterator_t {
        jsc_object_t base;
    } jsc_Iterator_t;

    const struct jsc_IteratorEntity_t * jsc_Iterator_next_(jsc_class_t * isa, jsc_object_t * object);
    const struct jsc_IteratorEntity_t * jsc_Iterator_next(jsc_object_t * object);


#ifdef __cplusplus
}
#endif


#endif /* jsc_Iterator_h */
