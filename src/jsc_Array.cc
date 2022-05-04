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

#include <vector>

typedef jsc_IteratorEntity_t jsc_Array_Entry;

class jsc_Array_Compare {
public:
    bool operator ()(const jsc_variant_t & left,const jsc_variant_t & right) const {
        return jsc_variant_compare(left, right) < 0;
    }
};


typedef std::vector<jsc_variant_t> jsc_Array_EntrySet;


/* iterator */

typedef struct jsc_ArrayIterator_t {
    jsc_Iterator_t base;
    jsc_Array_EntrySet * s;
    jsc_Array_EntrySet::iterator i;
    jsc_IteratorEntity_t entity;
} jsc_ArrayIterator_t;


static const struct jsc_IteratorEntity_t * _jsc_ArrayIterator_next(jsc_class_t * isa, jsc_object_t * object);

jsc_Iterator_class_t jsc_ArrayIterator = { {(jsc_class_t *) &jsc_Iterator,sizeof(jsc_ArrayIterator_t),"ArrayIterator",
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
static struct jsc_Iterator_t * _jsc_Array_iterator(jsc_class_t * isa, jsc_object_t * object);


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
    _jsc_Array_iterator,
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

struct jsc_Iterator_t * jsc_Array_iterator_(jsc_class_t * isa, jsc_object_t * object) {
    
    if(isa == NULL || object == NULL) {
        return NULL;
    }
    
    if(jsc_class_isKind(isa, &jsc_Array.base)) {
        jsc_Array_class_t * s = (jsc_Array_class_t *) isa;
        if(s->iterator) {
            return (*s->iterator)(isa,object);
        } else {
            return jsc_Array_iterator_(isa->isa,object);
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

struct jsc_Iterator_t * jsc_Array_iterator(jsc_object_t * object) {
    if(object == NULL) {
        return NULL;
    }
    return jsc_Array_iterator_(object->isa,object);
}

/**
 implemented
 */


static void _jsc_Array_alloc(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_Array_t * v = (jsc_Array_t *) object;
    v->_internal = (void *) new jsc_Array_EntrySet();
}

static void _jsc_Array_dealloc(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_Array_t * v = (jsc_Array_t *) object;
    jsc_Array_EntrySet * s = (jsc_Array_EntrySet *) v->_internal;
    jsc_Array_EntrySet::iterator i = s->begin();
    
    while(i != s->end()) {
        jsc_variant_t & vv = *i;
        jsc_setStrong(&vv.objectValue, NULL);
        i ++;
    }
    
    delete s;
    
}

static jsc_int_t _jsc_Array_length(jsc_class_t * isa, jsc_object_t * object) {
    jsc_Array_t * v = (jsc_Array_t *) object;
    jsc_Array_EntrySet * s = (jsc_Array_EntrySet *) v->_internal;
    return (jsc_int_t) s->size();
}

static jsc_variant_t _jsc_Array___index(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index) {
    jsc_Array_t * v = (jsc_Array_t *) object;
    jsc_Array_EntrySet * s = (jsc_Array_EntrySet *) v->_internal;
    if(index >=0 && index < s->size()) {
        return (*s)[index];
    }
    return jsc_Nil;
}

static void _jsc_Array___newindex(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index,jsc_variant_t value) {
    
    jsc_Array_t * v = (jsc_Array_t *) object;
    jsc_Array_EntrySet * s = (jsc_Array_EntrySet *) v->_internal;
    
    if(index < 0) {
        return;
    }
    
    while(index >= s->size()) {
        s->push_back(jsc_Nil);
    }
    
    (*s)[index] = jsc_variant_getStrong(value);
    
}

static void _jsc_Array_push(jsc_class_t * isa, jsc_object_t * object,jsc_variant_t value) {
    
    jsc_Array_t * v = (jsc_Array_t *) object;
    jsc_Array_EntrySet * s = (jsc_Array_EntrySet *) v->_internal;
    
    s->push_back(jsc_variant_getStrong(value));
}

static jsc_variant_t _jsc_Array_pop(jsc_class_t * isa, jsc_object_t * object) {
    jsc_Array_t * v = (jsc_Array_t *) object;
    jsc_Array_EntrySet * s = (jsc_Array_EntrySet *) v->_internal;
    
    if(!s->empty()) {
        jsc_variant_t r = s->back();
        if(r.objectValue) {
            jsc_object_autorelease(r.objectValue);
        }
        s->pop_back();
        return r;
    }
    
    return jsc_Nil;
}

static jsc_variant_t _jsc_Array_shift(jsc_class_t * isa, jsc_object_t * object) {
    jsc_Array_t * v = (jsc_Array_t *) object;
    jsc_Array_EntrySet * s = (jsc_Array_EntrySet *) v->_internal;
    
    if(!s->empty()) {
        jsc_variant_t r = s->front();
        if(r.objectValue) {
            jsc_object_autorelease(r.objectValue);
        }
        s->erase(s->begin());
        return r;
    }
    
    return jsc_Nil;
}

static void _jsc_Array_unshift(jsc_class_t * isa, jsc_object_t * object,jsc_variant_t value) {
    jsc_Array_t * v = (jsc_Array_t *) object;
    jsc_Array_EntrySet * s = (jsc_Array_EntrySet *) v->_internal;
    s->insert(s->begin(), jsc_variant_getStrong(value));
}

static void _jsc_Array_splice(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index,jsc_int_t count) {
    jsc_Array_t * v = (jsc_Array_t *) object;
    jsc_Array_EntrySet * s = (jsc_Array_EntrySet *) v->_internal;
    
    jsc_int_t length = (jsc_int_t) s->size();
    
    if( index < 0 ) {
        index = length + index;
    }
    
    if(index <0 || index >= length) {
        return;
    }
    
    jsc_int_t n = (count <=0 || count > length - index) ? length - index : count;

    if(n > 0) {
        jsc_Array_EntrySet::iterator i = s->begin() + index;
        while(n >0 && i != s->end()) {
            jsc_variant_t & vv = * i;
            jsc_variant_setStrong(&vv, jsc_Nil);
            i = s->erase(i);
            n --;
        }
    }

}

static jsc_Array_t * _jsc_Array_slice(jsc_class_t * isa, jsc_object_t * object,jsc_int_t start,jsc_int_t end) {
    
    jsc_Array_t * v = (jsc_Array_t *) object;
    jsc_Array_EntrySet * s = (jsc_Array_EntrySet *) v->_internal;
    
    jsc_int_t length = (jsc_int_t) s->size();
    
    
    if( start < 0 ) {
        start = length + start;
    }
    
    if(start <0 || start >= length) {
        return NULL;
    }
    
    jsc_Array_t * dst = (jsc_Array_t *) jsc_object_new(&jsc_Array.base, 0);
    jsc_int_t n = (end < 0 || end > length) ? length - start : end - start;
    
    if(n > 0) {
        jsc_Array_EntrySet * ss = (jsc_Array_EntrySet *) dst->_internal;
        jsc_Array_EntrySet::iterator i = s->begin() + start;
        while(n > 0 && i != s->end()) {
            jsc_variant_t & vv = * i;
            ss->push_back(jsc_variant_getStrong(vv));
            i ++;
            n --;
        }
    }
    
    return dst;
}

static struct jsc_String_t * _jsc_Array_join(jsc_class_t * isa, jsc_object_t * object,jsc_string_t separator) {
    jsc_Array_t * v = (jsc_Array_t *) object;
    jsc_Array_EntrySet * s = (jsc_Array_EntrySet *) v->_internal;
    
    jsc_buffer_t buf;
    jsc_buffer_init(&buf);
    
    if(separator == NULL) {
        separator = ",";
    }
    
    jsc_Array_EntrySet::iterator i = s->begin();
    jsc_int_t n = 0;
    
    while(i != s->end()) {
        if(n != 0) {
            jsc_buffer_format(&buf, "%s",separator);
        }
        jsc_variant_toCString(*i, &buf);
        n ++;
        i ++;
    }
    
    jsc_String_t * r = jsc_String_newUTF8String(buf.data, (jsc_int_t) buf.length);
    
    jsc_buffer_destory(&buf);
    
    return r;
}

static jsc_int_t _jsc_Array_indexOf(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t value) {
    jsc_Array_t * v = (jsc_Array_t *) object;
    jsc_Array_EntrySet * s = (jsc_Array_EntrySet *) v->_internal;
    
    jsc_Array_EntrySet::iterator i = s->begin();
    jsc_int_t n = 0;
    
    while(i != s->end()) {
        
        if(jsc_variant_compare(*i,value) == 0) {
            return n;
        }
        
        n ++;
        i ++;
    }
    
    return -1;
}

static struct jsc_Iterator_t * _jsc_Array_iterator(jsc_class_t * isa, jsc_object_t * object) {
    jsc_Array_t * v = (jsc_Array_t *) object;
    jsc_Array_EntrySet * s = (jsc_Array_EntrySet *) v->_internal;
    jsc_ArrayIterator_t * i = (jsc_ArrayIterator_t *) jsc_object_new((jsc_class_t *) &jsc_ArrayIterator, 0);
    i->s = s;
    i->i = s->begin();
    return (jsc_Iterator_t *) i;
}


/* iterator implemented */

static const struct jsc_IteratorEntity_t * _jsc_ArrayIterator_next(jsc_class_t * isa, jsc_object_t * object) {
    jsc_ArrayIterator_t * s = (jsc_ArrayIterator_t *) object;
    if(s->i != s->s->end()) {
        s->entity.key.type = JSC_VARIANT_TYPE_INT;
        s->entity.key.intValue ++;
        s->entity.value = *(s->i);
        s->i ++;
        return &s->entity;
    }
    return NULL;
}
