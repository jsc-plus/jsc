//
//  jsc_Number.h
//  jsc
//
//  Created by 张海龙 on 2022/5/3.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#ifndef jsc_Number_h
#define jsc_Number_h

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct jsc_Number_class_t {
        jsc_class_t base;
    } jsc_Number_class_t;

    extern jsc_Number_class_t jsc_Number;
    
    typedef struct jsc_Number_t {
        jsc_object_t base;
        jsc_variant_t value;
    } jsc_Number_t;

    jsc_Number_t * jsc_Number_alloc(jsc_variant_t v);
    jsc_Number_t * jsc_Number_new(jsc_variant_t v);

#ifdef __cplusplus
}
#endif

#endif /* jsc_Number_h */
