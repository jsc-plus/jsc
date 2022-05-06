//
//  jsc_String.c
//  jsc
//
//  Created by 张海龙 on 2022/1/17.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#include "jsc_type.h"
#include "jsc_class.h"
#include "jsc_String.h"
#include "jsc_Array.h"
#include "jsc_buffer.h"
#include "jsc_variant.h"
#include <zlib.h>
#include <iconv.h>

static void _jsc_String_alloc(struct jsc_class_t * isa, struct jsc_object_t * object);
static void _jsc_String_dealloc(struct jsc_class_t * isa, struct jsc_object_t * object);
static jsc_ulong_t _jsc_String_hashCode(struct jsc_class_t * isa, struct jsc_object_t * object);
static jsc_long_t _jsc_String_compare(struct jsc_class_t * isa, struct jsc_object_t * object,struct jsc_object_t * v);
static struct jsc_String_t * _jsc_String_toString(struct jsc_class_t * isa, struct jsc_object_t * object) ;
static jsc_int64_t _jsc_String_toInt64(struct jsc_class_t * isa, struct jsc_object_t * object);
static jsc_float64_t _jsc_String_toFloat64(struct jsc_class_t * isa, struct jsc_object_t * object);
static jsc_boolean_t _jsc_String_toBoolean(struct jsc_class_t * isa, struct jsc_object_t * object);


static jsc_int_t _jsc_String_length(jsc_class_t * isa, jsc_object_t * object);
static jsc_unichar_t _jsc_String___index(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index);
static jsc_string_t _jsc_String_CString(jsc_class_t * isa, jsc_object_t * object);
static jsc_unichar_t _jsc_String_charAt(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index);
static jsc_int_t _jsc_String_charCodeAt(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index);
static jsc_int_t _jsc_String_codePointAt(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index);
static struct jsc_String_t * _jsc_String_concat(jsc_class_t * isa, jsc_object_t * object,jsc_string_t s);
static jsc_int_t _jsc_String_indexOf(jsc_class_t * isa, jsc_object_t * object,jsc_string_t s);
static struct jsc_String_t * _jsc_String_repeat(jsc_class_t * isa, jsc_object_t * object,jsc_int_t n);
static struct jsc_String_t * _jsc_String_replace(jsc_class_t * isa, jsc_object_t * object,jsc_string_t substr,jsc_string_t newSubstr);
static struct jsc_String_t * _jsc_String_slice(jsc_class_t * isa, jsc_object_t * object,jsc_int_t start,jsc_int_t end);
static struct jsc_Array_t * _jsc_String_split(jsc_class_t * isa, jsc_object_t * object,jsc_string_t separator,jsc_int_t limit);


jsc_String_class_t jsc_String = { {&jsc_Object,sizeof(jsc_String_t),"String",
    _jsc_String_alloc,_jsc_String_dealloc,_jsc_String_hashCode,_jsc_String_compare,_jsc_String_toString,_jsc_String_toInt64,_jsc_String_toFloat64,_jsc_String_toBoolean},
    _jsc_String_length,
    _jsc_String___index,
    _jsc_String_CString,
    _jsc_String_charAt,
    _jsc_String_charCodeAt,
    _jsc_String_codePointAt,
    _jsc_String_concat,
    _jsc_String_indexOf,
    _jsc_String_repeat,
    _jsc_String_replace,
    _jsc_String_slice,
    _jsc_String_split,
};

jsc_int_t jsc_String_length_(jsc_class_t * isa, jsc_object_t * object) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_String.base)) {
        jsc_String_class_t * s = (jsc_String_class_t *) isa;
        if(s->length) {
            return (*s->length)(isa,object);
        } else {
            return jsc_String_length_(isa->isa,object);
        }
    }

    return 0;
}

jsc_unichar_t jsc_String___index_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_String.base)) {
        jsc_String_class_t * s = (jsc_String_class_t *) isa;
        if(s->__index) {
            return (*s->__index)(isa,object,index);
        } else {
            return jsc_String___index_(isa->isa,object,index);
        }
    }

    return 0;
}

jsc_string_t jsc_String_CString_(jsc_class_t * isa, jsc_object_t * object) {
    
    if(isa == NULL || object == NULL) {
        return NULL;
    }
    
    if(jsc_class_isKind(isa, &jsc_String.base)) {
        jsc_String_class_t * s = (jsc_String_class_t *) isa;
        if(s->CString) {
            return (*s->CString)(isa,object);
        } else {
            return jsc_String_CString_(isa->isa,object);
        }
    }

    return NULL;
}

jsc_unichar_t jsc_String_charAt_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_String.base)) {
        jsc_String_class_t * s = (jsc_String_class_t *) isa;
        if(s->charAt) {
            return (*s->charAt)(isa,object,index);
        } else {
            return jsc_String_charAt_(isa->isa,object,index);
        }
    }

    return 0;
}

jsc_int_t jsc_String_charCodeAt_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_String.base)) {
        jsc_String_class_t * s = (jsc_String_class_t *) isa;
        if(s->charCodeAt) {
            return (*s->charCodeAt)(isa,object,index);
        } else {
            return jsc_String_charCodeAt_(isa->isa,object,index);
        }
    }

    return 0;
}

jsc_int_t jsc_String_codePointAt_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_String.base)) {
        jsc_String_class_t * s = (jsc_String_class_t *) isa;
        if(s->codePointAt) {
            return (*s->codePointAt)(isa,object,index);
        } else {
            return jsc_String_codePointAt_(isa->isa,object,index);
        }
    }

    return 0;
}

struct jsc_String_t * jsc_String_concat_(jsc_class_t * isa, jsc_object_t * object,jsc_string_t v) {
    
    if(isa == NULL || object == NULL) {
        return NULL;
    }
    
    if(jsc_class_isKind(isa, &jsc_String.base)) {
        jsc_String_class_t * s = (jsc_String_class_t *) isa;
        if(s->concat) {
            return (*s->concat)(isa,object,v);
        } else {
            return jsc_String_concat_(isa->isa,object,v);
        }
    }

    return NULL;
}

jsc_int_t jsc_String_indexOf_(jsc_class_t * isa, jsc_object_t * object,jsc_string_t v) {
    
    if(isa == NULL || object == NULL) {
        return -1;
    }
    
    if(jsc_class_isKind(isa, &jsc_String.base)) {
        jsc_String_class_t * s = (jsc_String_class_t *) isa;
        if(s->indexOf) {
            return (*s->indexOf)(isa,object,v);
        } else {
            return jsc_String_indexOf_(isa->isa,object,v);
        }
    }

    return -1;
}

struct jsc_String_t * jsc_String_repeat_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t n) {
    
    if(isa == NULL || object == NULL) {
        return NULL;
    }
    
    if(jsc_class_isKind(isa, &jsc_String.base)) {
        jsc_String_class_t * s = (jsc_String_class_t *) isa;
        if(s->repeat) {
            return (*s->repeat)(isa,object,n);
        } else {
            return jsc_String_repeat_(isa->isa,object,n);
        }
    }

    return NULL;
}

struct jsc_String_t * jsc_String_replace_(jsc_class_t * isa, jsc_object_t * object,jsc_string_t substr,jsc_string_t newSubstr) {
    
    if(isa == NULL || object == NULL) {
        return NULL;
    }
    
    if(jsc_class_isKind(isa, &jsc_String.base)) {
        jsc_String_class_t * s = (jsc_String_class_t *) isa;
        if(s->replace) {
            return (*s->replace)(isa,object,substr,newSubstr);
        } else {
            return jsc_String_replace_(isa->isa,object,substr,newSubstr);
        }
    }

    return NULL;
}

struct jsc_String_t * jsc_String_slice_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t start,jsc_int_t end) {
    
    if(isa == NULL || object == NULL) {
        return NULL;
    }
    
    if(jsc_class_isKind(isa, &jsc_String.base)) {
        jsc_String_class_t * s = (jsc_String_class_t *) isa;
        if(s->slice) {
            return (*s->slice)(isa,object,start,end);
        } else {
            return jsc_String_slice_(isa->isa,object,start,end);
        }
    }

    return NULL;
    
}

struct jsc_Array_t * jsc_String_split_(jsc_class_t * isa, jsc_object_t * object,jsc_string_t separator,jsc_int_t limit) {
    
    if(isa == NULL || object == NULL) {
        return NULL;
    }
    
    if(jsc_class_isKind(isa, &jsc_String.base)) {
        jsc_String_class_t * s = (jsc_String_class_t *) isa;
        if(s->split) {
            return (*s->split)(isa,object,separator,limit);
        } else {
            return jsc_String_split_(isa->isa,object,separator,limit);
        }
    }

    return NULL;
    
}


jsc_int_t jsc_String_length(jsc_object_t * object) {
    if(object == NULL) {
        return 0;
    }
    return jsc_String_length_(object->isa,object);
}

jsc_unichar_t jsc_String___index(jsc_object_t * object,jsc_int_t index) {
    if(object == NULL) {
        return 0;
    }
    return jsc_String___index_(object->isa,object,index);
}

jsc_string_t jsc_String_CString(jsc_object_t * object) {
    if(object == NULL) {
        return NULL;
    }
    return jsc_String_CString_(object->isa,object);
}

jsc_unichar_t jsc_String_charAt(jsc_object_t * object,jsc_int_t index) {
    if(object == NULL) {
        return 0;
    }
    return jsc_String_charAt_(object->isa,object,index);
}

jsc_int_t jsc_String_charCodeAt(jsc_object_t * object,jsc_int_t index) {
    if(object == NULL) {
        return 0;
    }
    return jsc_String_charCodeAt_(object->isa,object,index);
}

jsc_int_t jsc_String_codePointAt(jsc_object_t * object,jsc_int_t index) {
    if(object == NULL) {
        return 0;
    }
    return jsc_String_codePointAt_(object->isa,object,index);
}

struct jsc_String_t * jsc_String_concat(jsc_object_t * object,jsc_string_t s) {
    if(object == NULL) {
        return NULL;
    }
    return jsc_String_concat_(object->isa,object,s);
}

jsc_int_t jsc_String_indexOf(jsc_object_t * object,jsc_string_t s) {
    if(object == NULL) {
        return -1;
    }
    return jsc_String_indexOf_(object->isa,object,s);
}

struct jsc_String_t * jsc_String_repeat(jsc_object_t * object,jsc_int_t n) {
    if(object == NULL) {
        return NULL;
    }
    return jsc_String_repeat_(object->isa,object,n);
}

struct jsc_String_t * jsc_String_replace(jsc_object_t * object,jsc_string_t substr,jsc_string_t newSubstr) {
    if(object == NULL) {
        return NULL;
    }
    return jsc_String_replace_(object->isa,object,substr,newSubstr);
}

struct jsc_String_t * jsc_String_slice(jsc_object_t * object,jsc_int_t start,jsc_int_t end) {
    if(object == NULL) {
        return NULL;
    }
    return jsc_String_slice_(object->isa,object,start,end);
}

struct jsc_Array_t * jsc_String_split(jsc_object_t * object,jsc_string_t separator,jsc_int_t limit) {
    if(object == NULL) {
        return NULL;
    }
    return jsc_String_split_(object->isa,object,separator,limit);
}

/**
 implemented
 */


static void _jsc_String_alloc(struct jsc_class_t * isa, struct jsc_object_t * object) {
    
}

static void _jsc_String_dealloc(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_String_t * v = (jsc_String_t *) object;
    if(v->_CString && !v->_CStringNotFree) {
        JSC_FREE((jsc_ptr_t) v->_CString);
    }
    if(v->_UString) {
        JSC_FREE(v->_UString);
    }
}

static void _jsc_String_initUString(jsc_String_t *s) {
    if(s->_UString == NULL && s->_CString != NULL) {
        jsc_buffer_t buf;
        jsc_buffer_init(&buf);
        jsc_String_iconv("UNICODE//IGNORE","UTF-8",(jsc_byte_t *) s->_CString,strlen(s->_CString),&buf);
        s->_length = (jsc_int_t) (buf.length / 2);
        s->_UString = (jsc_unichar_t *) malloc(s->_length * 2);
        jsc_buffer_destory(&buf);
    }
}

static void _jsc_String_initCString(jsc_String_t *s) {
    if(s->_CString == NULL && s->_UString != NULL) {
        
        jsc_buffer_t buf;
        jsc_buffer_init(&buf);
        
        jsc_String_iconv("UTF-8//IGNORE","UNICODE",(jsc_byte_t *) s->_UString,s->_length * 2,&buf);
        
        jsc_byte_t * b = malloc(buf.length + 1);
        
        memcpy(b, buf.data, buf.length);
        
        b[buf.length] = 0;
        
        s->_CString = b;
        s->_CStringNotFree = 0;
        
        jsc_buffer_destory(&buf);
        
    }
}

static jsc_int_t _jsc_String_length(jsc_class_t * isa, jsc_object_t * object) {
    jsc_String_t * v = (jsc_String_t *) object;
    _jsc_String_initUString(v);
    return v->_length;
}

static jsc_unichar_t _jsc_String___index(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index) {
    jsc_String_t * v = (jsc_String_t *) object;
    _jsc_String_initUString(v);
    if(index >=0 && index < v->_length) {
        return v->_UString[index];
    }
    return 0;
}

static jsc_string_t _jsc_String_CString(jsc_class_t * isa, jsc_object_t * object) {
    jsc_String_t * v = (jsc_String_t *) object;
    _jsc_String_initCString(v);
    return v->_CString;
}

static jsc_unichar_t _jsc_String_charAt(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index) {
    jsc_String_t * v = (jsc_String_t *) object;
    _jsc_String_initUString(v);
    if(index >=0 && index < v->_length) {
        return v->_UString[index];
    }
    return 0;
}

static jsc_int_t _jsc_String_charCodeAt(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index) {
    jsc_String_t * v = (jsc_String_t *) object;
    _jsc_String_initUString(v);
    if(index >=0 && index < v->_length) {
        return v->_UString[index];
    }
    return 0;
}

/**
 参考：https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/String/codePointAt
 */
static jsc_int_t _jsc_String_codePointAt(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index) {
    jsc_String_t * v = (jsc_String_t *) object;
    _jsc_String_initUString(v);
    if(index >=0 && index < v->_length) {
        jsc_unichar_t h = v->_UString[index];
        if(index + 1 < v->_length) {
            jsc_unichar_t l = v->_UString[index+1];
            if(h >= 0xD800 && h <= 0xDBFF && l >= 0xDC00 && l <= 0xDFFF) {
                return (h - 0xD800) * 0x400 + l - 0xDC00 + 0x10000;
            }
        }
        return h;
    }
    return 0;
}

static struct jsc_String_t * _jsc_String_concat(jsc_class_t * isa, jsc_object_t * object,jsc_string_t s) {
    jsc_String_t * v = (jsc_String_t *) object;
    jsc_buffer_t buf;
    jsc_buffer_init(&buf);
    _jsc_String_initCString(v);
    
    jsc_string_t ss = jsc_buffer_format(&buf, "%s%s",v->_CString,s ? s : "");
    
    jsc_String_t * r = jsc_String_newCString(ss);
    
    jsc_buffer_destory(&buf);
    
    return r;
}

static jsc_int_t _jsc_String_indexOf(jsc_class_t * isa, jsc_object_t * object,jsc_string_t s) {
    
    if(s == NULL) {
        return -1;
    }
    
    if(*s == 0) {
        return 0;
    }
    
    jsc_String_t * v = (jsc_String_t *) object;
    _jsc_String_initUString(v);
    
    jsc_buffer_t buf;
    jsc_buffer_init(&buf);
    jsc_String_iconv("UNICODE//IGNORE","UTF-8",(jsc_byte_t *) s,strlen(s),&buf);
    
    jsc_int_t r = -1;
    size_t n = buf.length / 2;
    size_t l = n * 2;
    jsc_unichar_t * p = (jsc_unichar_t *) buf.data;
    
    for(jsc_int_t i=0; i <= v->_length - n;i++) {
        if(memcmp(v->_UString + i, p + i, l) == 0) {
            r = i;
            break;
        }
    }
    
    jsc_buffer_destory(&buf);
    
    return r;
}

static struct jsc_String_t * _jsc_String_repeat(jsc_class_t * isa, jsc_object_t * object,jsc_int_t n) {
    
    if(n <= 0) {
        return NULL;
    }
    
    jsc_String_t * v = (jsc_String_t *) object;
    jsc_buffer_t buf;
    jsc_buffer_init(&buf);
    
    _jsc_String_initCString(v);
    
    for(jsc_int_t i=0;i<n;i++) {
        jsc_buffer_format(&buf, "%s",v->_CString);
    }
    
    jsc_String_t * r = jsc_String_newCString(buf.data);
    
    jsc_buffer_destory(&buf);
    
    return r;
}

static struct jsc_String_t * _jsc_String_replace(jsc_class_t * isa, jsc_object_t * object,jsc_string_t substr,jsc_string_t newSubstr) {
    
    jsc_String_t * v = (jsc_String_t *) object;
    jsc_buffer_t buf;
    jsc_buffer_init(&buf);
    
    _jsc_String_initCString(v);
    
    if(substr == NULL || * substr == 0  || newSubstr == NULL || *newSubstr == 0) {
        jsc_buffer_format(&buf, "%s",v->_CString);
    } else {
        jsc_byte_t * p = (jsc_byte_t *) v->_CString;
        size_t n = strlen(substr);
        while(*p != 0) {
            jsc_byte_t * s = strstr(p, substr);
            if(s) {
                if(s > p) {
                    jsc_buffer_append(&buf, p, s - p);
                }
                jsc_buffer_format(&buf, "%s",newSubstr);
                p = s + n;
            } else {
                jsc_buffer_format(&buf, "%s",p);
                break;
            }
        }
    }
    
    jsc_String_t * r = jsc_String_newCString(buf.data);
    
    jsc_buffer_destory(&buf);
    
    return r;
}

static struct jsc_String_t * _jsc_String_slice(jsc_class_t * isa, jsc_object_t * object,jsc_int_t start,jsc_int_t end) {
    jsc_String_t * v = (jsc_String_t *) object;
    _jsc_String_initUString(v);

    if(v->_length == 0) {
        return jsc_String_newCString("");
    }
    
    if(start < 0) {
        start = v->_length + start;
    }
    
    if(end < 0) {
        end = v->_length + end + 1;
    }
    
    start = MIN(MAX(0,start),v->_length-1);
    end = MIN(MAX(0,end),v->_length);
    
    if(start >= end) {
        return jsc_String_newCString("");
    }
    
    return jsc_String_newUString(v->_UString + start, end - start);
}


static struct jsc_Array_t * _jsc_String_split(jsc_class_t * isa, jsc_object_t * object,jsc_string_t separator,jsc_int_t limit) {
    jsc_object_t * a = jsc_object_new((jsc_class_t *) &jsc_Array, 0);
    jsc_String_t * v = (jsc_String_t *) object;
    
    if(separator == NULL) {
        jsc_Array_push(a, jsc_variant_Object(object));
        return (struct jsc_Array_t *) a;
    }
    
    size_t n = strlen(separator);
    
    if(n == 0) {
        _jsc_String_initUString(v);
        for(jsc_int_t i =0;i<v->_length;i++){
            jsc_String_t * s = jsc_String_allocUString(v->_UString + i, 1);
            jsc_Array_push(a, jsc_variant_Object((jsc_object_t *) s));
            jsc_object_release((jsc_object_t *) s);
        }
        return (struct jsc_Array_t *) a;
    } else {
        _jsc_String_initCString(v);
        jsc_byte_t * p = (jsc_byte_t *) v->_CString;
        while(*p != 0) {
            jsc_byte_t * s = strstr(p, separator);
            if(s) {
                if(s > p) {
                    jsc_String_t * v = jsc_String_allocUTF8String(p, (jsc_int_t) (s - p));
                    jsc_Array_push(a, jsc_variant_Object((jsc_object_t *) v));
                    jsc_object_release((jsc_object_t *) v);
                } else {
                    jsc_String_t * v = jsc_String_allocUTF8String("",0);
                    jsc_Array_push(a, jsc_variant_Object((jsc_object_t *) v));
                    jsc_object_release((jsc_object_t *) v);
                }
                p = s + n;
            } else {
                jsc_String_t * v = jsc_String_allocCString(p);
                jsc_Array_push(a, jsc_variant_Object((jsc_object_t *) v));
                jsc_object_release((jsc_object_t *) v);
                break;
            }
        }
        return (struct jsc_Array_t *) a;
    }
    
    return (struct jsc_Array_t *) a;
}

static struct jsc_String_t * _jsc_String_toString(struct jsc_class_t * isa, struct jsc_object_t * object) {
    return (jsc_String_t *) object;
}

static jsc_ulong_t _jsc_String_hashCode(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_String_t * v = (jsc_String_t *) object;
    _jsc_String_initUString(v);
    return crc32(0, (jsc_ubyte_t *) v->_UString, v->_length * 2);
}

static jsc_long_t _jsc_String_compare(struct jsc_class_t * isa, struct jsc_object_t * object,struct jsc_object_t * v) {
    
    jsc_String_t * s = (jsc_String_t *) object;
    
    if(v == NULL) {
        return 1;
    }
    
    if(jsc_class_isKind(v->isa, (jsc_class_t *) &jsc_String)) {
        jsc_String_t * b = (jsc_String_t *) v;
        if(s->_CString && b->_CString) {
            return strcmp(s->_CString, b->_CString);
        } else if(s->_UString && b->_UString) {
            jsc_int_t n = MIN(s->_length,b->_length);
            jsc_int_t r = memcmp(s->_UString, b->_UString,n * 2);
            if(r == 0) {
                return s->_length - b->_length;
            } else {
                return r;
            }
        } else {
            _jsc_String_initCString(s);
            _jsc_String_initCString(b);
            return strcmp(s->_CString, b->_CString);
        }
    } else {
        return 1;
    }
}

static jsc_int64_t _jsc_String_toInt64(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_String_t * s = (jsc_String_t *) object;
    _jsc_String_initCString(s);
    return s->_CString ? atoll(s->_CString) :0;
}

static jsc_float64_t _jsc_String_toFloat64(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_String_t * s = (jsc_String_t *) object;
    _jsc_String_initCString(s);
    return s->_CString ? atof(s->_CString) :0;
}

static jsc_boolean_t _jsc_String_toBoolean(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_String_t * s = (jsc_String_t *) object;
    _jsc_String_initCString(s);
    return s->_CString && strcmp(s->_CString,"true") == 0 ? 1 : 0;
}

/**
 alloc
 */

struct jsc_String_t * jsc_String_allocCString(jsc_string_t str) {
    if(str == NULL) {
        return NULL;
    }
    jsc_ulong_t n = strlen(str) + 1;
    jsc_byte_t * s = (jsc_byte_t *) JSC_MALLOC(n);
    memcpy(s,str,n);
    jsc_String_t * v = (jsc_String_t *) jsc_object_alloc(&jsc_String.base, 0);
    v->_CString = s;
    return v;
}

struct jsc_String_t * jsc_String_allocConstCString(jsc_string_t s) {
    if(s == NULL) {
        return NULL;
    }
    jsc_String_t * v = (jsc_String_t *) jsc_object_alloc(&jsc_String.base, 0);
    v->_CString = s;
    v->_CStringNotFree = 1;
    return v;
}

struct jsc_String_t * jsc_String_allocUTF8String(jsc_string_t str,jsc_int_t n) {
    if(str == NULL) {
        return NULL;
    }
    jsc_byte_t * s = (jsc_byte_t *) JSC_MALLOC(n + 1);
    memcpy(s,str,n);
    s[n] = 0;
    jsc_String_t * v = (jsc_String_t *) jsc_object_alloc(&jsc_String.base, 0);
    v->_CString = s;
    return v;
}

struct jsc_String_t * jsc_String_allocUString(jsc_unichar_t * str, jsc_int_t length) {
    if(str == NULL || length < 0) {
        return NULL;
    }
    jsc_int_t n = sizeof(jsc_unichar_t) * length;
    jsc_unichar_t * s = (jsc_unichar_t *) JSC_MALLOC(n);
    memcpy(s,str,n);
    jsc_String_t * v = (jsc_String_t *) jsc_object_alloc(&jsc_String.base, 0);
    v->_UString = s;
    v->_length = length;
    return v;
}

struct jsc_String_t * jsc_String_allocFormat(jsc_string_t format,...) {
    jsc_buffer_t buf;
    jsc_buffer_init(&buf);
    
    va_list ap;
    va_start(ap, format);
    size_t n = vsnprintf(NULL, 0, format, ap);
    va_end(ap);
    va_start(ap, format);
    jsc_string_t v = jsc_buffer_formatv(&buf, format, ap, n);
    va_end(ap);
    
    struct jsc_String_t * s = jsc_String_allocCString(v);
    
    jsc_buffer_destory(&buf);
    
    return s;
}

struct jsc_String_t * jsc_String_newCString(jsc_string_t s) {
    jsc_String_t * v = jsc_String_allocCString(s);
    jsc_object_autorelease((jsc_object_t *) v);
    return v;
}

struct jsc_String_t * jsc_String_newConstCString(jsc_string_t s) {
    jsc_String_t * v = jsc_String_allocConstCString(s);
    jsc_object_autorelease((jsc_object_t *)v);
    return v;
}

struct jsc_String_t * jsc_String_newUTF8String(jsc_string_t s,jsc_int_t n) {
    jsc_String_t * v = jsc_String_allocUTF8String(s,n);
    jsc_object_autorelease((jsc_object_t *)v);
    return v;
}

struct jsc_String_t * jsc_String_newUString(jsc_unichar_t * s, jsc_int_t length) {
    jsc_String_t * v = jsc_String_allocUString(s,length);
    jsc_object_autorelease((jsc_object_t *)v);
    return v;
}


struct jsc_String_t * jsc_String_newFormat(jsc_string_t format,...) {
    jsc_buffer_t buf;
    jsc_buffer_init(&buf);
    
    va_list ap;
    va_start(ap, format);
    size_t n = vsnprintf(NULL, 0, format, ap);
    va_end(ap);
    va_start(ap, format);
    jsc_string_t v = jsc_buffer_formatv(&buf, format, ap, n);
    va_end(ap);
    
    struct jsc_String_t * s = jsc_String_newCString(v);
    
    jsc_buffer_destory(&buf);
    
    return s;
}

size_t jsc_String_iconv(jsc_string_t toCharset,jsc_string_t fromCharset,jsc_byte_t * inBytes,size_t inLen,struct jsc_buffer_t * dst) {
    size_t v = dst->length;
    
    jsc_byte_t * outBytes = (jsc_byte_t *) dst->data + dst->length;
    size_t outLen = (size_t) (dst->size - dst->length);
    
    iconv_t cd = iconv_open(toCharset, fromCharset);
    
    while(inLen > 0) {
        size_t r = iconv(cd, &inBytes, &inLen, &outBytes, &outLen);
        if(r == -1) {
            if(errno == E2BIG) {
                dst->length = outBytes - dst->data;
                jsc_buffer_capacity(dst, dst->size + MAX(inLen,2048));
                outBytes = dst->data + dst->length;
                outLen = dst->size - dst->length;
            } else {
                break;
            }
        } else {
            dst->length = outBytes - dst->data;
            break;
        }
    }
    
    iconv_close(cd);
    
    return dst->length - v;
}

jsc_long_t jsc_string_compare(jsc_string_t a,jsc_string_t b) {
    if(a == b) {
        return 0;
    }
    
    if(a == NULL) {
        return -1;
    }
    
    if(b == NULL) {
        return 1;
    }
    
    return strcmp(a, b);
}


struct jsc_String_t * jsc_string_concat(jsc_string_t a,jsc_string_t b) {
    jsc_buffer_t buf;
    jsc_buffer_init(&buf);
    
    if(a) {
        jsc_buffer_format(&buf, "%s",a);
    }
    
    if(b) {
        jsc_buffer_format(&buf, "%s",b);
    }
    
    struct jsc_String_t * s = jsc_String_newUTF8String(buf.data, (jsc_int_t) buf.length);
    
    jsc_buffer_destory(&buf);
    
    return s;
}
