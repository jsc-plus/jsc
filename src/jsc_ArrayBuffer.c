//
//  jsc_ArrayBuffer.c
//  jsc
//
//  Created by 张海龙 on 2022/5/4.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#include "jsc_type.h"
#include "jsc_class.h"
#include "jsc_variant.h"
#include "jsc_buffer.h"
#include "jsc_String.h"
#include "jsc_ArrayBuffer.h"


static void _jsc_ArrayBuffer_alloc(struct jsc_class_t * isa, struct jsc_object_t * object);
static void _jsc_ArrayBuffer_dealloc(struct jsc_class_t * isa, struct jsc_object_t * object);
static struct jsc_String_t * _jsc_ArrayBuffer_toString(struct jsc_class_t * isa, struct jsc_object_t * object);

static jsc_int_t _jsc_ArrayBuffer_byteLength(jsc_class_t * isa, jsc_object_t * object);
static struct jsc_ArrayBuffer_t * _jsc_ArrayBuffer_slice(jsc_class_t * isa, jsc_object_t * object,jsc_int_t begin,jsc_int_t end);


jsc_ArrayBuffer_class_t jsc_ArrayBuffer = { {&jsc_Object,sizeof(jsc_ArrayBuffer_t),"ArrayBuffer",
    _jsc_ArrayBuffer_alloc,_jsc_ArrayBuffer_dealloc,NULL,NULL,_jsc_ArrayBuffer_toString,NULL,NULL,NULL},
    _jsc_ArrayBuffer_byteLength,
    _jsc_ArrayBuffer_slice,
};


jsc_int_t jsc_ArrayBuffer_byteLength_(jsc_class_t * isa, jsc_object_t * object) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_ArrayBuffer.base)) {
        jsc_ArrayBuffer_class_t * s = (jsc_ArrayBuffer_class_t *) isa;
        if(s->byteLength) {
            return (*s->byteLength)(isa,object);
        } else {
            return jsc_ArrayBuffer_byteLength_(isa->isa,object);
        }
    }

    return 0;
}

struct jsc_ArrayBuffer_t * jsc_ArrayBuffer_slice_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t begin,jsc_int_t end) {
    
    if(isa == NULL || object == NULL) {
        return NULL;
    }
    
    if(jsc_class_isKind(isa, &jsc_ArrayBuffer.base)) {
        jsc_ArrayBuffer_class_t * s = (jsc_ArrayBuffer_class_t *) isa;
        if(s->slice) {
            return (*s->slice)(isa,object,begin,end);
        } else {
            return jsc_ArrayBuffer_slice_(isa->isa,object,begin,end);
        }
    }

    return NULL;
}

jsc_int_t jsc_ArrayBuffer_byteLength(jsc_object_t * object) {
    if(object == NULL) {
        return 0;
    }
    return jsc_ArrayBuffer_byteLength_(object->isa,object);
}

struct jsc_ArrayBuffer_t * jsc_ArrayBuffer_slice(jsc_object_t * object,jsc_int_t begin,jsc_int_t end) {
    if(object == NULL) {
        return NULL;
    }
    return jsc_ArrayBuffer_slice_(object->isa,object,begin,end);
}

/* alloc */
struct jsc_ArrayBuffer_t * jsc_ArrayBuffer_alloc(jsc_int_t length) {
    jsc_ArrayBuffer_t * r = (jsc_ArrayBuffer_t *) jsc_object_alloc(&jsc_ArrayBuffer.base, 0);
    if(length > 0) {
        r->_data = JSC_MALLOC(length);
        r->_byteLength = length;
        memset(r->_data,0,length);
    }
    return r;
}

struct jsc_ArrayBuffer_t * jsc_ArrayBuffer_new(jsc_int_t length) {
    jsc_ArrayBuffer_t * r = jsc_ArrayBuffer_alloc(length);
    jsc_object_autorelease((jsc_object_t *) r);
    return r;
}

/* implemented */


static void _jsc_ArrayBuffer_alloc(struct jsc_class_t * isa, struct jsc_object_t * object) {
    
}

static void _jsc_ArrayBuffer_dealloc(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_ArrayBuffer_t * v = (jsc_ArrayBuffer_t *) object;
    if(v->_data) {
        JSC_FREE(v->_data);
    }
}

static struct jsc_String_t * _jsc_ArrayBuffer_toString(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_ArrayBuffer_t * v = (jsc_ArrayBuffer_t *) object;
    jsc_buffer_t buf;
    jsc_buffer_init(&buf);
    
    jsc_ubyte_t * p = v->_data;
    jsc_int_t i = 0;
    
    jsc_buffer_format(&buf,"(%d)<",v->_byteLength);
    
    while(i < v->_byteLength && i < 16) {
        
        if(i != 0) {
            jsc_buffer_format(&buf," %02x", *p);
        } else {
            jsc_buffer_format(&buf,"%02x", *p);
        }
        
        p ++;
        i ++;
    }
    
    if(i < v->_byteLength) {
        jsc_buffer_format(&buf," ...>");
    } else {
        jsc_buffer_format(&buf,">");
    }
    
    jsc_String_t * r = jsc_String_newUTF8String(buf.data, (jsc_int_t) buf.length);
    
    jsc_buffer_destory(&buf);
    
    return r;
}

static jsc_int_t _jsc_ArrayBuffer_byteLength(jsc_class_t * isa, jsc_object_t * object) {
    jsc_ArrayBuffer_t * v = (jsc_ArrayBuffer_t *) object;
    return v->_byteLength;
}

static struct jsc_ArrayBuffer_t * _jsc_ArrayBuffer_slice(jsc_class_t * isa, jsc_object_t * object,jsc_int_t begin,jsc_int_t end) {
    
    jsc_ArrayBuffer_t * v = (jsc_ArrayBuffer_t *) object;
    
    jsc_int_t length = v->_byteLength;
    
    if( begin < 0 ) {
        begin = length + begin;
    }
    
    if(begin <0 || begin >= length) {
        return NULL;
    }

    jsc_int_t n = (end < 0 || end > length) ? length - begin : end - begin;
  
    
    jsc_ArrayBuffer_t * dst = jsc_ArrayBuffer_new(n);
    
    memcpy(v->_data + begin, dst->_data, n);
    
    return dst;
}



