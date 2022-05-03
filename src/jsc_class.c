//
//  jsc_class.c
//  jsc
//
//  Created by 张海龙 on 2022/1/12.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#include "jsc_type.h"
#include "jsc_class.h"
#include "jsc_String.h"
#include <pthread.h>

typedef struct jsc_weak_t {
    jsc_object_t ** dst;
    struct jsc_weak_t * next;
} jsc_weak_t;


static pthread_mutex_t _jsc_atomic;
static pthread_key_t _jsc_autorelease_pool_key;

static jsc_ulong_t _jsc_object_hashCode(struct jsc_class_t * isa, struct jsc_object_t * object) {
    return (jsc_long_t) object;
}

static jsc_long_t _jsc_object_compare(struct jsc_class_t * isa, struct jsc_object_t * object,struct jsc_object_t * v) {
    return (jsc_long_t) object - (jsc_long_t) v;
}

static struct jsc_String_t * _jsc_object_toString(struct jsc_class_t * isa, struct jsc_object_t * object) {
    return jsc_String_newConstCString(isa->name);
}

static jsc_int64_t _jsc_object_toInt64(struct jsc_class_t * isa, struct jsc_object_t * object) {
    return 0;
}

static jsc_float64_t _jsc_object_toFloat64(struct jsc_class_t * isa, struct jsc_object_t * object) {
    return 0;
}

static jsc_boolean_t _jsc_object_toBoolean(struct jsc_class_t * isa, struct jsc_object_t * object) {
    return 0;
}

jsc_class_t jsc_Object = {NULL,sizeof(jsc_object_t),"Object",NULL,NULL,_jsc_object_hashCode,_jsc_object_compare,_jsc_object_toString,_jsc_object_toInt64,_jsc_object_toFloat64,_jsc_object_toBoolean};

static void _jsc_object_alloc(jsc_class_t * isa, jsc_object_t * object) {
    if(isa->isa) {
        _jsc_object_alloc(isa->isa,object);
    }
    if(isa->alloc) {
        (*isa->alloc)(isa,object);
    }
}

static void _jsc_object_dealloc(jsc_class_t * isa, jsc_object_t * object) {
    if(isa->dealloc) {
        (*isa->dealloc)(isa,object);
    }
    if(isa->isa) {
        _jsc_object_dealloc(isa->isa,object);
    }
}

jsc_object_t * jsc_object_alloc(jsc_class_t * isa,jsc_int_t extraSize) {
    jsc_int_t n = isa->size + extraSize;
    jsc_object_t * v = (jsc_object_t *) JSC_MALLOC(n);
    memset(v,0,n);
    v->isa = isa;
    v->retainCount = 1;
    _jsc_object_alloc(isa,v);
    jsc_log("jsc_object_alloc %s 0x%x",isa->name,(long)v);
    return v;
}

void jsc_object_retain(jsc_object_t * v) {
    if(!v) {
        return;
    }
    pthread_mutex_lock(&_jsc_atomic);
    v->retainCount ++;
//    jsc_log("jsc_object_retain %s %x %d",v->isa->name,(long)v,v->retainCount);
    pthread_mutex_unlock(&_jsc_atomic);
}

void jsc_object_release(jsc_object_t * v) {
    
    if(!v) {
        return;
    }
    
    jsc_boolean_t dealloced = 0;
    
    pthread_mutex_lock(&_jsc_atomic);
    
    if(-- v->retainCount == 0) {
        
        dealloced = 1;
        
        jsc_weak_t * p = v->weak;
            
        while(p) {
            (*p->dst) = NULL;
            p = p->next;
        }
        
    }
    
//    jsc_log("jsc_object_release %s %x %d",v->isa->name,(long)v,v->retainCount);
    
    pthread_mutex_unlock(&_jsc_atomic);
    
    if(dealloced) {
        
        jsc_log("jsc_object_dealloc %s 0x%x",v->isa->name,(long)v);
        
        _jsc_object_dealloc(v->isa,v);
        
        jsc_weak_t * p = v->weak, * n;
            
        while(p) {
            n = p->next;
            JSC_FREE(p);
            p = n;
        }
        
        JSC_FREE(v);
        
    }
    
}

void jsc_object_weak(jsc_object_t * v , jsc_object_t ** dst) {
    
    if(!v || !dst) {
        return;
    }
    
    jsc_weak_t * p = (jsc_weak_t *) JSC_MALLOC(sizeof(jsc_weak_t));
    memset(p,0,sizeof(jsc_weak_t));
    p->dst = dst;
    
    pthread_mutex_lock(&_jsc_atomic);
    
    p->next = v->weak;
    v->weak = p;
    
    pthread_mutex_unlock(&_jsc_atomic);
    
}

void jsc_object_unWeak(jsc_object_t * v, jsc_object_t ** dst) {
    
    if(!v || !dst) {
        return;
    }
    
    pthread_mutex_lock(&_jsc_atomic);
    
    jsc_weak_t * p = v->weak, * prev = NULL,*n;
        
    while(p) {
        
        n = p->next;
        
        if(p->dst == dst) {
            if(prev == NULL) {
                v->weak = n;
            } else {
                prev->next = n;
            }
            // TODO: optimization
            JSC_FREE(p);
        }
        
        p = n;
        
    }
    
    pthread_mutex_unlock(&_jsc_atomic);
    
}

void jsc_setStrong(jsc_object_t ** dst, jsc_object_t * src) {
    
    if(!dst) {
        return;
    }
    
    if(* dst != src) {
        jsc_object_retain(src);
        jsc_object_release(*dst);
        * dst = src;
    }
}

void jsc_setWeak(jsc_object_t ** dst, jsc_object_t * src) {
    
    if(!dst) {
        return;
    }
    
    if(* dst != src) {
        jsc_object_weak(src,dst);
        jsc_object_unWeak(* dst,dst);
        * dst = src;
    }
    
}


jsc_boolean_t jsc_class_isKind(jsc_class_t * isa, jsc_class_t * dst) {
    while(isa) {
        if(isa == dst) {
            return 1;
        }
        isa = isa->isa;
    }
    return 0;
}


/* autorelease */
jsc_object_t * jsc_object_new(jsc_class_t * isa,jsc_int_t extraSize) {
    jsc_object_t * v = jsc_object_alloc(isa,extraSize);
    jsc_object_autorelease(v);
    return v;
}

struct jsc_autorelease_pool_object {
    jsc_object_t * object;
    struct jsc_autorelease_pool_object * next;
};

struct jsc_autorelease_pool {
    struct jsc_autorelease_pool_object * object;
    struct jsc_autorelease_pool * next;
};

static void jsc_autorelease_pool_dealloc(struct jsc_autorelease_pool *p) {
    struct jsc_autorelease_pool_object * v = p->object, * n;
    while(v) {
        n = v->next;
        jsc_object_release(v->object);
        JSC_FREE(v);
        v = n;
    }
    JSC_FREE(p);
}

static void jsc_autorelease_pool_key_dealloc(void * v) {
    JSC_ASSERT(v == NULL);
}

static void jsc_autorelease_addObject(jsc_object_t * v) {
    
    if(!v) {
        return;
    }
    
    struct jsc_autorelease_pool * p = (struct jsc_autorelease_pool *) pthread_getspecific(_jsc_autorelease_pool_key);
    
    JSC_ASSERT(p);
    
    struct jsc_autorelease_pool_object * object = (struct jsc_autorelease_pool_object *) JSC_MALLOC(sizeof(struct jsc_autorelease_pool_object));
    memset(object, 0, sizeof(struct jsc_autorelease_pool_object));
    object->object = v;
    object->next = p->object;
    p->object = object;
    
}

void jsc_object_autorelease(jsc_object_t * v) {
    jsc_autorelease_addObject(v);
}

void jsc_autorelease_pool_begin() {
    
    JSC_ASSERT(_jsc_autorelease_pool_key);
    
    struct jsc_autorelease_pool * p = (struct jsc_autorelease_pool *) JSC_MALLOC(sizeof(struct jsc_autorelease_pool));
    
    memset(p,0,sizeof(struct jsc_autorelease_pool));
    
    p->next = (struct jsc_autorelease_pool *) pthread_getspecific(_jsc_autorelease_pool_key);
    
    pthread_setspecific(_jsc_autorelease_pool_key, p);
    
}

void jsc_autorelease_pool_end() {
    
    JSC_ASSERT(_jsc_autorelease_pool_key);
    
    struct jsc_autorelease_pool * p = (struct jsc_autorelease_pool *) pthread_getspecific(_jsc_autorelease_pool_key);
    
    JSC_ASSERT(p);
    
    pthread_setspecific(_jsc_autorelease_pool_key, p->next);
    
    /*
     WARNING:
        当 pool 为当前线程最后一级 时
        dealloc 方法中若存在 autorelease 调用时会异常
     */
    jsc_autorelease_pool_dealloc(p);
}


void jsc_initialize(void) {
    pthread_mutex_init(&_jsc_atomic, NULL);
    pthread_key_create(&_jsc_autorelease_pool_key, jsc_autorelease_pool_key_dealloc);
}


/* hasCode,compare */
jsc_ulong_t jsc_object_hashCode_(jsc_class_t * isa, jsc_object_t * object) {
    
    if(isa == NULL) {
        return (jsc_ulong_t) object ;
    }
    
    if(isa->hashCode) {
        return (*isa->hashCode)(isa,object);
    } else {
        return jsc_object_hashCode_(isa->isa,object);
    }
    
}

jsc_long_t jsc_object_compare_(jsc_class_t * isa, jsc_object_t * object,jsc_object_t * v) {
    
    if(isa == NULL) {
        return (jsc_long_t) object - (jsc_long_t) v;
    }
    
    if(isa->compare) {
        return (*isa->compare)(isa,object,v);
    } else {
        return jsc_object_compare_(isa->isa,object,v);
    }
    
}

struct jsc_String_t * jsc_object_toString_(jsc_class_t * isa,jsc_object_t * object) {
    
    if(isa == NULL) {
        return NULL;
    }
    
    if(isa->toString) {
        return (*isa->toString)(isa,object);
    } else {
        return jsc_object_toString_(isa->isa,object);
    }
    
}

jsc_ulong_t jsc_object_hashCode(jsc_object_t * object) {
    
    if(object == NULL) {
        return 0;
    }
    
    return jsc_object_hashCode_(object->isa,object);
}

jsc_long_t jsc_object_compare(jsc_object_t * object,jsc_object_t * v) {
    
    if(object == NULL) {
        return 0;
    }
    
    return jsc_object_compare_(object->isa,object,v);
    
}

struct jsc_String_t * jsc_object_toString(jsc_object_t * object) {
    
    if(object == NULL) {
        return NULL;
    }
    
    return jsc_object_toString_(object->isa,object);
}


/* toInt64 */
jsc_int64_t jsc_object_toInt64_(jsc_class_t * isa,jsc_object_t * object) {
    
    if(isa == NULL) {
        return 0;
    }
    
    if(isa->toInt64) {
        return (*isa->toInt64)(isa,object);
    } else {
        return jsc_object_toInt64_(isa->isa,object);
    }
    
}

jsc_int64_t jsc_object_toInt64(jsc_object_t * object) {
    
    if(object == NULL) {
        return 0;
    }
    
    return jsc_object_toInt64_(object->isa,object);
}

/* toFloat64 */
jsc_float64_t jsc_object_toFloat64_(jsc_class_t * isa,jsc_object_t * object) {
    
    if(isa == NULL) {
        return 0.0;
    }
    
    if(isa->toInt64) {
        return (*isa->toFloat64)(isa,object);
    } else {
        return jsc_object_toFloat64_(isa->isa,object);
    }
}

jsc_float64_t jsc_object_toFloat64(jsc_object_t * object) {
    
    if(object == NULL) {
        return 0.0;
    }
    
    return jsc_object_toFloat64_(object->isa,object);
}

/* toBoolean */
jsc_boolean_t jsc_object_toBoolean_(jsc_class_t * isa,jsc_object_t * object) {
    
    if(isa == NULL) {
        return 0;
    }
    
    if(isa->toBoolean) {
        return (*isa->toBoolean)(isa,object);
    } else {
        return jsc_object_toBoolean_(isa->isa,object);
    }
}

jsc_boolean_t jsc_object_toBoolean(jsc_object_t * object) {
    
    if(object == NULL) {
        return 0;
    }
    
    return jsc_object_toBoolean_(object->isa,object);
}

