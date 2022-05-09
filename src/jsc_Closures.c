//
//  jsc_Closures.c
//  jsc
//
//  Created by 张海龙 on 2022/5/8.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#include "jsc_type.h"
#include "jsc_class.h"
#include "jsc_variant.h"
#include "jsc_buffer.h"
#include "jsc_String.h"
#include "jsc_Closures.h"

static void _jsc_Closures_alloc(struct jsc_class_t * isa, struct jsc_object_t * object);
static void _jsc_Closures_dealloc(struct jsc_class_t * isa, struct jsc_object_t * object);

jsc_Closures_class_t jsc_Closures = { {&jsc_Object,sizeof(jsc_Closures_t),"Closures",
    _jsc_Closures_alloc,_jsc_Closures_dealloc,NULL,NULL,NULL,NULL,NULL,NULL},
};


static void _jsc_Closures_alloc(struct jsc_class_t * isa, struct jsc_object_t * object) {

}

static void _jsc_Closures_dealloc(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_Closures_t * v = (jsc_Closures_t *) object;
    jsc_ClosuresVar_t * p = v->_vars;
    jsc_int_t n = v->_length;
    
    while(p && n >0){
        if(p->weak) {
            jsc_variant_setWeak(&p->var,jsc_Nil);
        } else {
            jsc_variant_setStrong(&p->var,jsc_Nil);
        }
        p ++;
        n --;
    }
    
    if(v->_vars) {
        JSC_FREE(v->_vars);
    }
}

struct jsc_variant_t jsc_Closures_get(jsc_Closures_t * closures,jsc_int_t index) {
    
    if(closures == NULL) {
        return jsc_Nil;
    }
    
    if(index >=0 && index < closures->_length) {
        return (closures->_vars + index)->var;
    }
    
    return jsc_Nil;
}

void jsc_Closures_set(jsc_Closures_t * closures,jsc_int_t index,struct jsc_variant_t v) {
    
    if(closures == NULL) {
        return;
    }
    
    if(index >=0 && index < closures->_length) {
        
        jsc_ClosuresVar_t * item = closures->_vars + index;
        
        if(item->weak) {
            jsc_variant_setWeak(&item->var,v);
        } else {
            jsc_variant_setStrong(&item->var,v);
        }
        
    }
    
    
}

jsc_Closures_t * jsc_Closures_new(void * imp,jsc_int_t type,...){
    
    jsc_int_t n = 0;
    
    
    va_list ap;
    
    va_start(ap, type);
    
    jsc_int_t t = type;
    
    while(t != JSC_VARIANT_TYPE_END) {
        va_arg(ap, jsc_int_t);
        switch(t) {
            case JSC_VARIANT_TYPE_NIL:
                JSC_ASSERT(0);
                break;
            case JSC_VARIANT_TYPE_INT8:
            case JSC_VARIANT_TYPE_UINT8:
            case JSC_VARIANT_TYPE_INT16:
            case JSC_VARIANT_TYPE_UINT16:
            case JSC_VARIANT_TYPE_INT32:
            case JSC_VARIANT_TYPE_UINT32:
            case JSC_VARIANT_TYPE_INT64:
            case JSC_VARIANT_TYPE_INT:
            case JSC_VARIANT_TYPE_UINT:
            case JSC_VARIANT_TYPE_LONG:
            case JSC_VARIANT_TYPE_ULONG:
            case JSC_VARIANT_TYPE_BOOLEAN:
            case JSC_VARIANT_TYPE_UNICHAR:
            case JSC_VARIANT_TYPE_UINT64:
            case JSC_VARIANT_TYPE_FLOAT32:
            case JSC_VARIANT_TYPE_FLOAT64:
            case JSC_VARIANT_TYPE_STRING:
            case JSC_VARIANT_TYPE_OBJECT:
            case JSC_VARIANT_TYPE_VARIANT:
                va_arg(ap,jsc_ptr_t);
                n ++;
                break;
            default:
                JSC_ASSERT(0);
                break;
        }
        t = va_arg(ap, jsc_int_t);
    }
    
    va_end(ap);

    jsc_Closures_t * v = (jsc_Closures_t *) jsc_object_new((jsc_class_t *)&jsc_Closures, 0);
    
    if(n > 0) {
        v->_length = n;
        v->_vars = (jsc_ClosuresVar_t *) JSC_MALLOC(sizeof(jsc_ClosuresVar_t) * n);
        memset(v->_vars,0,sizeof(jsc_ClosuresVar_t) * n);
        
        jsc_ClosuresVar_t * p = v->_vars;
        
        t = type;
        
        while(t != JSC_VARIANT_TYPE_END) {
            p->weak = (jsc_boolean_t) va_arg(ap, jsc_int_t);
            switch(t) {
                case JSC_VARIANT_TYPE_NIL:
                    JSC_ASSERT(0);
                    break;
                case JSC_VARIANT_TYPE_INT8:
                    p->var.type = t;
                    p->var.int8Value = * (jsc_int8_t *) va_arg(ap, jsc_int8_t *);
                    p ++;
                    break;
                case JSC_VARIANT_TYPE_UINT8:
                    p->var.type = t;
                    p->var.uint8Value = * (jsc_uint8_t *) va_arg(ap, jsc_uint8_t *);
                    p ++;
                    break;
                case JSC_VARIANT_TYPE_INT16:
                    p->var.type = t;
                    p->var.int16Value = * (jsc_int16_t *) va_arg(ap, jsc_int16_t *);
                    p ++;
                    break;
                case JSC_VARIANT_TYPE_UINT16:
                    p->var.type = t;
                    p->var.uint16Value = * (jsc_uint16_t *) va_arg(ap, jsc_uint16_t *);
                    p ++;
                    break;
                case JSC_VARIANT_TYPE_INT32:
                    p->var.type = t;
                    p->var.int32Value = * (jsc_int32_t *) va_arg(ap, jsc_int32_t *);
                    p ++;
                    break;
                case JSC_VARIANT_TYPE_UINT32:
                    p->var.type = t;
                    p->var.uint32Value = * (jsc_uint32_t *) va_arg(ap, jsc_uint32_t *);
                    p ++;
                    break;
                case JSC_VARIANT_TYPE_INT64:
                    p->var.type = t;
                    p->var.int64Value = * (jsc_int64_t *) va_arg(ap, jsc_int64_t *);
                    p ++;
                    break;
                case JSC_VARIANT_TYPE_INT:
                    p->var.type = t;
                    p->var.intValue = * (jsc_int_t *) va_arg(ap, jsc_int_t *);
                    p ++;
                    break;
                case JSC_VARIANT_TYPE_UINT:
                    p->var.type = t;
                    p->var.uintValue = * (jsc_uint_t *) va_arg(ap, jsc_uint_t *);
                    p ++;
                    break;
                case JSC_VARIANT_TYPE_LONG:
                    p->var.type = t;
                    p->var.longValue = * (jsc_long_t *) va_arg(ap, jsc_long_t *);
                    p ++;
                    break;
                case JSC_VARIANT_TYPE_ULONG:
                    p->var.type = t;
                    p->var.ulongValue = * (jsc_ulong_t *) va_arg(ap, jsc_ulong_t *);
                    p ++;
                    break;
                case JSC_VARIANT_TYPE_BOOLEAN:
                    p->var.type = t;
                    p->var.booleanValue = * (jsc_boolean_t *) va_arg(ap, jsc_boolean_t *);
                    p ++;
                    break;
                case JSC_VARIANT_TYPE_UNICHAR:
                    p->var.type = t;
                    p->var.unicharValue = * (jsc_unichar_t *) va_arg(ap, jsc_unichar_t *);
                    p ++;
                    break;
                case JSC_VARIANT_TYPE_UINT64:
                    p->var.type = t;
                    p->var.uint64Value = * (jsc_uint64_t *) va_arg(ap, jsc_uint64_t *);
                    p ++;
                    break;
                case JSC_VARIANT_TYPE_FLOAT32:
                    p->var.type = t;
                    p->var.float32Value = * (jsc_float32_t *) va_arg(ap, jsc_float32_t *);
                    p ++;
                    break;
                case JSC_VARIANT_TYPE_FLOAT64:
                    p->var.type = t;
                    p->var.float64Value = * (jsc_float64_t *) va_arg(ap, jsc_float64_t *);
                    p ++;
                    break;
                case JSC_VARIANT_TYPE_STRING:
                    p->weak = 0;
                    p->var.type = t;
                    p->var.stringValue = * (jsc_string_t *) va_arg(ap, jsc_string_t *);
                    if(p->var.stringValue){
                        p->var.objectValue = (jsc_object_t *) jsc_String_allocCString(p->var.stringValue);
                        p->var.stringValue = jsc_String_CString(p->var.objectValue);
                    }
                    p ++;
                    break;
                case JSC_VARIANT_TYPE_OBJECT:
                    p->var.type = t;
                    if(p->weak) {
                        jsc_setWeak(&p->var.objectValue, * (jsc_object_t **) va_arg(ap, jsc_object_t **));
                    } else {
                        jsc_setStrong(&p->var.objectValue, * (jsc_object_t **) va_arg(ap, jsc_object_t **));
                    }
                    p ++;
                    break;
                case JSC_VARIANT_TYPE_VARIANT:
                    if(p->weak) {
                        jsc_variant_setWeak(&p->var, * (jsc_variant_t *) va_arg(ap, jsc_variant_t *));
                    } else {
                        jsc_variant_setStrong(&p->var, * (jsc_variant_t *) va_arg(ap, jsc_variant_t *));
                    }
                default:
                    JSC_ASSERT(0);
                    break;
            }
            t = va_arg(ap, jsc_int_t);
        }
        
        va_end(ap);
    }
    
    return v;
}

