//
//  jsc_Array.c
//  jsc
//
//  Created by 张海龙 on 2022/1/14.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#include "jsc_type.h"
#include "jsc_class.h"
#include "jsc_variant.h"
#include "jsc_String.h"
#include "jsc_Iterator.h"
#include "jsc_Array.h"
#include "jsc_buffer.h"


#define CAPACITY 64

/* iterator */

typedef struct jsc_ArrayIterator_t {
    jsc_Iterator_t base;
    jsc_Array_t * a;
    jsc_int_t i;
    jsc_IteratorEntity_t entity;
} jsc_ArrayIterator_t;


static const struct jsc_IteratorEntity_t * _jsc_ArrayIterator_next(jsc_class_t * isa, jsc_object_t * object);

jsc_Iterator_class_t jsc_ArrayIterator = { {(jsc_class_t *) &jsc_Iterator,sizeof(jsc_ArrayIterator_t),"ArratIterator",
    NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    _jsc_ArrayIterator_next,
};



/* iterator */

static void _jsc_Array_alloc(struct jsc_class_t * isa, struct jsc_object_t * object);
static void _jsc_Array_dealloc(struct jsc_class_t * isa, struct jsc_object_t * object);

static jsc_int_t _jsc_Array_length(jsc_class_t * isa, jsc_object_t * object);
static jsc_variant_t _jsc_Array___index(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index);
static void _jsc_Array___newindex(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index,jsc_variant_t v);
static void _jsc_Array_push(jsc_class_t * isa, jsc_object_t * object,jsc_variant_t v);
static jsc_variant_t _jsc_Array_pop(jsc_class_t * isa, jsc_object_t * object);
static jsc_variant_t _jsc_Array_shift(jsc_class_t * isa, jsc_object_t * object);
static void _jsc_Array_unshift(jsc_class_t * isa, jsc_object_t * object,jsc_variant_t v);
static void _jsc_Array_splice(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index,jsc_int_t count);
static jsc_Array_t * _jsc_Array_slice(jsc_class_t * isa, jsc_object_t * object,jsc_int_t start,jsc_int_t end);
static struct jsc_String_t * _jsc_Array_join(jsc_class_t * isa, jsc_object_t * object,jsc_string_t separator);
static jsc_int_t _jsc_Array_indexOf(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t v);
static struct jsc_Iterator_t * _jsc_Array_Iterator(jsc_class_t * isa, jsc_object_t * object);


jsc_Array_class_t jsc_Array = { {&jsc_Object,sizeof(jsc_Array_t),"Array",_jsc_Array_alloc,_jsc_Array_dealloc},
    _jsc_Array_length,
    _jsc_Array___index,
    _jsc_Array___newindex,
    _jsc_Array_push,
    _jsc_Array_pop,
    _jsc_Array_shift,
    _jsc_Array_unshift,
    _jsc_Array_splice,
    _jsc_Array_slice,
    _jsc_Array_join,
    _jsc_Array_indexOf,
    _jsc_Array_Iterator,
};

jsc_int_t jsc_Array_length_(jsc_class_t * isa, jsc_object_t * object) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_Array.base)) {
        jsc_Array_class_t * s = (jsc_Array_class_t *) isa;
        if(s->length) {
            return (*s->length)(isa,object);
        } else {
            return jsc_Array_length_(isa->isa,object);
        }
    }

    return 0;
}

jsc_variant_t jsc_Array___index_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index) {
    
    if(isa == NULL || object == NULL) {
        return jsc_Nil;
    }
    
    if(jsc_class_isKind(isa, &jsc_Array.base)) {
        jsc_Array_class_t * s = (jsc_Array_class_t *) isa;
        if(s->__index) {
            return (*s->__index)(isa,object,index);
        } else {
            return jsc_Array___index_(isa->isa,object,index);
        }
    }

    return jsc_Nil;
}

void jsc_Array___newindex_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index,jsc_variant_t v) {
    
    if(isa == NULL || object == NULL) {
        return;
    }
    
    if(jsc_class_isKind(isa, &jsc_Array.base)) {
        jsc_Array_class_t * s = (jsc_Array_class_t *) isa;
        if(s->__newindex) {
            (*s->__newindex)(isa,object,index,v);
        } else {
            jsc_Array___newindex_(isa->isa,object,index,v);
        }
    }

    return;
}

void jsc_Array_push_(jsc_class_t * isa, jsc_object_t * object,jsc_variant_t v) {
    
    if(isa == NULL || object == NULL) {
        return;
    }
    
    if(jsc_class_isKind(isa, &jsc_Array.base)) {
        jsc_Array_class_t * s = (jsc_Array_class_t *) isa;
        if(s->push) {
            (*s->push)(isa,object,v);
        } else {
            jsc_Array_push_(isa->isa,object,v);
        }
    }

    return;
    
}

jsc_variant_t jsc_Array_pop_(jsc_class_t * isa, jsc_object_t * object) {
    if(isa == NULL || object == NULL) {
        return jsc_Nil;
    }
    
    if(jsc_class_isKind(isa, &jsc_Array.base)) {
        jsc_Array_class_t * s = (jsc_Array_class_t *) isa;
        if(s->pop) {
            return (*s->pop)(isa,object);
        } else {
            return jsc_Array_pop_(isa->isa,object);
        }
    }

    return jsc_Nil;
}

jsc_variant_t jsc_Array_shift_(jsc_class_t * isa, jsc_object_t * object) {
    
    if(isa == NULL || object == NULL) {
        return jsc_Nil;
    }
    
    if(jsc_class_isKind(isa, &jsc_Array.base)) {
        jsc_Array_class_t * s = (jsc_Array_class_t *) isa;
        if(s->shift) {
            return (*s->shift)(isa,object);
        } else {
            return jsc_Array_shift_(isa->isa,object);
        }
    }

    return jsc_Nil;
}

void jsc_Array_unshift_(jsc_class_t * isa, jsc_object_t * object,jsc_variant_t v) {
    
    if(isa == NULL || object == NULL) {
        return;
    }
    
    if(jsc_class_isKind(isa, &jsc_Array.base)) {
        jsc_Array_class_t * s = (jsc_Array_class_t *) isa;
        if(s->unshift) {
            (*s->unshift)(isa,object,v);
        } else {
            jsc_Array_unshift_(isa->isa,object,v);
        }
    }

    return;
}

void jsc_Array_splice_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index,jsc_int_t count) {
    
    if(isa == NULL || object == NULL) {
        return;
    }
    
    if(jsc_class_isKind(isa, &jsc_Array.base)) {
        jsc_Array_class_t * s = (jsc_Array_class_t *) isa;
        if(s->splice) {
            (*s->splice)(isa,object,index,count);
        } else {
            jsc_Array_splice_(isa->isa,object,index,count);
        }
    }

    return;
}

jsc_Array_t * jsc_Array_slice_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t start,jsc_int_t end) {
    
    if(isa == NULL || object == NULL) {
        return NULL;
    }
    
    if(jsc_class_isKind(isa, &jsc_Array.base)) {
        jsc_Array_class_t * s = (jsc_Array_class_t *) isa;
        if(s->slice) {
            return (*s->slice)(isa,object,start,end);
        } else {
            return jsc_Array_slice_(isa->isa,object,start,end);
        }
    }

    return NULL;
}

struct jsc_String_t * jsc_Array_join_(jsc_class_t * isa, jsc_object_t * object,jsc_string_t separator) {
    
    if(isa == NULL || object == NULL) {
        return NULL;
    }
    
    if(jsc_class_isKind(isa, &jsc_Array.base)) {
        jsc_Array_class_t * s = (jsc_Array_class_t *) isa;
        if(s->join) {
            return (*s->join)(isa,object,separator);
        } else {
            return jsc_Array_join_(isa->isa,object,separator);
        }
    }

    return NULL;
}

jsc_int_t jsc_Array_indexOf_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t v) {
    
    if(isa == NULL || object == NULL) {
        return -1;
    }
    
    if(jsc_class_isKind(isa, &jsc_Array.base)) {
        jsc_Array_class_t * s = (jsc_Array_class_t *) isa;
        if(s->indexOf) {
            return (*s->indexOf)(isa,object,v);
        } else {
            return jsc_Array_indexOf_(isa->isa,object,v);
        }
    }

    return -1;
}

struct jsc_Iterator_t * jsc_Array_Iterator_(jsc_class_t * isa, jsc_object_t * object) {
    
    if(isa == NULL || object == NULL) {
        return NULL;
    }
    
    if(jsc_class_isKind(isa, &jsc_Array.base)) {
        jsc_Array_class_t * s = (jsc_Array_class_t *) isa;
        if(s->iterator) {
            return (*s->iterator)(isa,object);
        } else {
            return jsc_Array_Iterator_(isa->isa,object);
        }
    }

    return NULL;
}

jsc_int_t jsc_Array_length(jsc_object_t * object) {
    if(object == NULL) {
        return 0;
    }
    return jsc_Array_length_(object->isa,object);
}

jsc_variant_t jsc_Array___index(jsc_object_t * object,jsc_int_t index) {
    if(object == NULL) {
        return jsc_Nil;
    }
    return jsc_Array___index_(object->isa,object,index);
}

void jsc_Array___newindex(jsc_object_t * object,jsc_int_t index,jsc_variant_t v) {
    if(object == NULL) {
        return ;
    }
    jsc_Array___newindex_(object->isa,object,index,v);
}

void jsc_Array_push(jsc_object_t * object,jsc_variant_t v) {
    if(object == NULL) {
        return ;
    }
    jsc_Array_push_(object->isa,object,v);
}

jsc_variant_t jsc_Array_pop(jsc_object_t * object) {
    if(object == NULL) {
        return jsc_Nil;
    }
    return jsc_Array_pop_(object->isa,object);
}

jsc_variant_t jsc_Array_shift(jsc_object_t * object) {
    if(object == NULL) {
        return jsc_Nil;
    }
    return jsc_Array_shift_(object->isa,object);
}

void jsc_Array_unshift(jsc_object_t * object,jsc_variant_t v) {
    if(object == NULL) {
        return ;
    }
    jsc_Array_unshift_(object->isa,object,v);
}

void jsc_Array_splice(jsc_object_t * object,jsc_int_t index,jsc_int_t count) {
    if(object == NULL) {
        return ;
    }
    jsc_Array_splice_(object->isa,object,index,count);
}

jsc_Array_t * jsc_Array_slice(jsc_object_t * object,jsc_int_t start,jsc_int_t end) {
    if(object == NULL) {
        return NULL;
    }
    return jsc_Array_slice_(object->isa,object,start,end);
}

struct jsc_String_t * jsc_Array_join(jsc_object_t * object,jsc_string_t separator) {
    if(object == NULL) {
        return NULL;
    }
    return jsc_Array_join_(object->isa,object,separator);
}

jsc_int_t jsc_Array_indexOf(jsc_object_t * object,struct jsc_variant_t v) {
    if(object == NULL) {
        return -1;
    }
    return jsc_Array_indexOf_(object->isa,object,v);
}

struct jsc_Iterator_t * jsc_Array_Iterator(jsc_object_t * object) {
    if(object == NULL) {
        return NULL;
    }
    return jsc_Array_Iterator_(object->isa,object);
}

/**
 implemented
 */


static void _jsc_Array_alloc(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_Array_t * v = (jsc_Array_t *) object;
    v->_size = CAPACITY;
    v->_length = 0;
    jsc_int_t n = sizeof(jsc_variant_t) * v->_size;
    v->_items = (jsc_variant_t *) JSC_MALLOC(n);
    memset(v->_items, 0, n);
}

static void _jsc_Array_dealloc(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_Array_t * v = (jsc_Array_t *) object;
    jsc_variant_t * p = v->_items;
    jsc_int_t n = v->_length;
    while(n >0) {
        jsc_setStrong(&p->objectValue, NULL);
        n --;
        p ++;
    }
    free(v->_items);
}

static void _jsc_Array_extend(jsc_Array_t * s,jsc_int_t maxSize) {
    if(s->_size < maxSize) {
        s->_size = MAX(s->_size + CAPACITY,maxSize);
        s->_items = JSC_REALLOC(s->_items,s->_size);
        memset(s->_items + s->_length, 0, sizeof(jsc_variant_t) * (s->_size - s->_length));
    }
}

static jsc_int_t _jsc_Array_length(jsc_class_t * isa, jsc_object_t * object) {
    jsc_Array_t * s = (jsc_Array_t *) object;
    return s->_length;
}

static jsc_variant_t _jsc_Array___index(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index) {
    jsc_Array_t * s = (jsc_Array_t *) object;
    if(index < 0 || index >= s->_length) {
        return jsc_Nil;
    }
    return s->_items[index];
}

static void _jsc_Array___newindex(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index,jsc_variant_t v) {
    
    jsc_Array_t * s = (jsc_Array_t *) object;
    
    if(index < 0) {
        return;
    }
    jsc_int_t n = index + 1;
    _jsc_Array_extend(s,n);
    jsc_variant_t * p = s->_items + index;
    p->type = v.type;
    p->uint64Value = v.uint64Value;
    jsc_setStrong(&p->objectValue, v.objectValue);
    
    if(n > s->_length) {
        s->_length = 0;
    }
}

static void _jsc_Array_push(jsc_class_t * isa, jsc_object_t * object,jsc_variant_t v) {
    
    jsc_Array_t * s = (jsc_Array_t *) object;

    _jsc_Array_extend(s,s->_length + 1);
    
    jsc_variant_t * p = s->_items + s->_length;
    p->type = v.type;
    p->uint64Value = v.uint64Value;
    jsc_setStrong(&p->objectValue, v.objectValue);
    s->_length ++;
    
}

static jsc_variant_t _jsc_Array_pop(jsc_class_t * isa, jsc_object_t * object) {
    jsc_Array_t * s = (jsc_Array_t *) object;
    if(s->_length <=0 ){
        return jsc_Nil;
    }
    jsc_int_t i = s->_length-1;
    jsc_variant_t p = s->_items[i];
    s->_items[i] = jsc_Nil;
    s->_length --;
    jsc_object_autorelease(p.objectValue);
    return p;
}

static jsc_variant_t _jsc_Array_shift(jsc_class_t * isa, jsc_object_t * object) {
    jsc_Array_t * s = (jsc_Array_t *) object;
    if( s->_length <= 0 ){
        return jsc_Nil;
    }
    jsc_variant_t p = s->_items[0];
    s->_items[0] = jsc_Nil;
    if(s->_length > 1) {
        jsc_int_t n = s->_length -1;
        for(jsc_int_t i=0;i<n;i++) {
            s->_items[i] = s->_items[i+1];
        }
        s->_items[n] = jsc_Nil;
    }
    s->_length --;
    jsc_object_autorelease(p.objectValue);
    return p;
}

static void _jsc_Array_unshift(jsc_class_t * isa, jsc_object_t * object,jsc_variant_t v) {
    jsc_Array_t * s = (jsc_Array_t *) object;
    jsc_int_t n = s->_length + 1;
    _jsc_Array_extend(s,n);
    for(jsc_int_t i = s->_length;i>0;i--) {
        s->_items[i] = s->_items[i-1];
    }
    s->_items[0] = v;
    jsc_object_retain(v.objectValue);
    s->_length ++;
}

static void _jsc_Array_splice(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index,jsc_int_t count) {
    jsc_Array_t * s = (jsc_Array_t *) object;
    
    if( index <0 ) {
        index = s->_length + index;
    }
    
    if(index <0 || index >= s->_length) {
        return;
    }
    
    jsc_int_t n = (count <=0 || count > s->_length - index) ? s->_length - index : count;
    jsc_int_t end = index + n;
    jsc_variant_t * p;
    for(jsc_int_t i=index;i<end;i++) {
        p = s->_items + i;
        jsc_object_release(p->objectValue);
        jsc_int_t e = end + i - index;
        if(e < s->_length) {
            * p = s->_items[e];
            s->_items[e] = jsc_Nil;
        } else {
            * p = jsc_Nil;
        }
    }
    s->_length -= n;
}

static jsc_Array_t * _jsc_Array_slice(jsc_class_t * isa, jsc_object_t * object,jsc_int_t start,jsc_int_t end) {
    jsc_Array_t * s = (jsc_Array_t *) object;
    
    if( start <0 ) {
        start = s->_length + start;
    }
    
    if(start <0 || start >= s->_length) {
        return NULL;
    }
    jsc_Array_t * dst = (jsc_Array_t *) jsc_object_new(&jsc_Array.base, 0);
    jsc_int_t n = (end < 0 || end > s->_length) ? s->_length - start : end - start;
    _jsc_Array_extend(dst, n);
    
    for(jsc_int_t i=0;i<n;i++) {
        jsc_variant_t p = dst->_items[i] = s->_items[i + start];
        jsc_object_retain(p.objectValue);
    }
    
    dst->_length = n;
    
    return dst;
}

static struct jsc_String_t * _jsc_Array_join(jsc_class_t * isa, jsc_object_t * object,jsc_string_t separator) {
    jsc_Array_t * s = (jsc_Array_t *) object;
    jsc_buffer_t buf;
    jsc_buffer_init(&buf);
    
    if(separator == NULL) {
        separator = ",";
    }
    
    for(jsc_int_t i=0;i<s->_length;i++) {
        if(i != 0) {
            jsc_buffer_format(&buf, "%s",separator);
        }
        jsc_variant_toCString(s->_items[i], &buf);
    }
    
    jsc_String_t * r = jsc_String_newUTF8String(buf.data, (jsc_int_t) buf.length);
    
    jsc_buffer_destory(&buf);
    
    return r;
}

static jsc_int_t _jsc_Array_indexOf(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t v) {
    jsc_Array_t * a = (jsc_Array_t *) object;
    for(jsc_int_t i=0;i<a->_length;i++) {
        if(jsc_variant_compare(a->_items[i], v) == 0) {
            return i;
        }
    }
    return -1;
}

static struct jsc_Iterator_t * _jsc_Array_Iterator(jsc_class_t * isa, jsc_object_t * object) {
    jsc_Array_t * a = (jsc_Array_t *) object;
    jsc_ArrayIterator_t * i = (jsc_ArrayIterator_t *) jsc_object_new((jsc_class_t *) &jsc_ArrayIterator, 0);
    i->a = a;
    i->i = 0;
    return (jsc_Iterator_t *) i;
}


/* iterator implemented */

static const struct jsc_IteratorEntity_t * _jsc_ArrayIterator_next(jsc_class_t * isa, jsc_object_t * object) {
    jsc_ArrayIterator_t * s = (jsc_ArrayIterator_t *) object;
    if(s->i < s->a->_length) {
        s->entity.key.type = JSC_VARIANT_TYPE_INT;
        s->entity.key.intValue = s->i;
        s->entity.value = s->a->_items[s->i];
        s->i ++;
        return &s->entity;
    }
    return NULL;
}
