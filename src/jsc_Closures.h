//
//  jsc_Closures.h
//  jsc
//
//  Created by 张海龙 on 2022/5/8.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#ifndef jsc_Closures_h
#define jsc_Closures_h

#ifdef __cplusplus
extern "C" {
#endif

    struct jsc_Closures_t;
    
    typedef struct jsc_Closures_class_t {
        jsc_class_t base;
    } jsc_Closures_class_t;

    extern jsc_Closures_class_t jsc_Closures;

#define JSC_VARIANT_TYPE_VARIANT 0xf2
#define JSC_VARIANT_TYPE_END 0xff

    typedef struct jsc_ClosuresVar_t {
        jsc_variant_t var;
        jsc_boolean_t weak;
    } jsc_ClosuresVar_t;

    typedef struct jsc_Closures_t {
        jsc_object_t base;
        jsc_ClosuresVar_t * _vars;
        jsc_int_t _length;
        void * imp;
    } jsc_Closures_t;

    struct jsc_variant_t jsc_Closures_get(jsc_Closures_t * closures,jsc_int_t index);
    void jsc_Closures_set(jsc_Closures_t * closures,jsc_int_t index,struct jsc_variant_t v);
    
    jsc_Closures_t * jsc_Closures_new(void * imp,jsc_int_t type,...);

#ifdef __cplusplus
}
#endif

#endif /* jsc_Closures_h */
