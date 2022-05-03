//
//  jsc_Iterator.c
//  jsc
//
//  Created by 张海龙 on 2022/5/3.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#include "jsc_type.h"
#include "jsc_class.h"
#include "jsc_variant.h"
#include "jsc_buffer.h"
#include "jsc_Iterator.h"


jsc_Iterator_class_t jsc_Iterator = { {&jsc_Object,sizeof(jsc_Iterator_t),"Iterator",
    NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    NULL,
};

const struct jsc_IteratorEntity_t * jsc_Iterator_next_(jsc_class_t * isa, jsc_object_t * object) {
   
    if(isa == NULL || object == NULL) {
        return NULL;
    }
    
    if(jsc_class_isKind(isa, &jsc_Iterator.base)) {
        jsc_Iterator_class_t * s = (jsc_Iterator_class_t *) isa;
        if(s->next) {
            return (*s->next)(isa,object);
        } else {
            return jsc_Iterator_next_(isa->isa,object);
        }
    }

    return NULL;
    
}

const struct jsc_IteratorEntity_t * jsc_Iterator_next(jsc_object_t * object) {
    
    if(object == NULL) {
        return NULL;
    }
    
    return jsc_Iterator_next_(object->isa,object);
}
