//
//  jsc_Number.c
//  jsc
//
//  Created by 张海龙 on 2022/5/3.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#include "jsc_type.h"
#include "jsc_class.h"
#include "jsc_variant.h"
#include "jsc_buffer.h"
#include "jsc_String.h"
#include "jsc_Number.h"


static void _jsc_Number_alloc(struct jsc_class_t * isa, struct jsc_object_t * object);
static void _jsc_Number_dealloc(struct jsc_class_t * isa, struct jsc_object_t * object);
static jsc_ulong_t _jsc_Number_hashCode(struct jsc_class_t * isa, struct jsc_object_t * object);
static jsc_long_t _jsc_Number_compare(struct jsc_class_t * isa, struct jsc_object_t * object,struct jsc_object_t * v);
static struct jsc_String_t * _jsc_Number_toString(struct jsc_class_t * isa, struct jsc_object_t * object) ;
static jsc_int64_t _jsc_Number_toInt64(struct jsc_class_t * isa, struct jsc_object_t * object);
static jsc_float64_t _jsc_Number_toFloat64(struct jsc_class_t * isa, struct jsc_object_t * object);
static jsc_boolean_t _jsc_Number_toBoolean(struct jsc_class_t * isa, struct jsc_object_t * object);

jsc_Number_class_t jsc_Number = { {&jsc_Object,sizeof(jsc_Number_t),"Number",
    _jsc_Number_alloc,_jsc_Number_dealloc,_jsc_Number_hashCode,_jsc_Number_compare,_jsc_Number_toString,_jsc_Number_toInt64,_jsc_Number_toFloat64,_jsc_Number_toBoolean},
};

static void _jsc_Number_alloc(struct jsc_class_t * isa, struct jsc_object_t * object) {
    
}

static void _jsc_Number_dealloc(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_Number_t * v = (jsc_Number_t *) object;
    jsc_setStrong(&v->value.objectValue, NULL);
}

static jsc_ulong_t _jsc_Number_hashCode(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_Number_t * v = (jsc_Number_t *) object;
    return jsc_variant_hashCode(v->value);
}

static jsc_long_t _jsc_Number_compare(struct jsc_class_t * isa, struct jsc_object_t * object,struct jsc_object_t * v) {
    jsc_Number_t * a = (jsc_Number_t *) object;
    jsc_Number_t * b = (jsc_Number_t *) v;
    return jsc_variant_compare(a->value, b == NULL ? jsc_Nil : b->value);
}

static struct jsc_String_t * _jsc_Number_toString(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_Number_t * v = (jsc_Number_t *) object;
    if(v->value.objectValue == NULL) {
        jsc_buffer_t buf;
        jsc_buffer_init(&buf);
        jsc_string_t s = jsc_variant_toCString(v->value, &buf);
        v->value.objectValue = (jsc_object_t *) jsc_String_allocCString(s);
        jsc_buffer_destory(&buf);
    }
    return (jsc_String_t *) v->value.objectValue;
}

static jsc_int64_t _jsc_Number_toInt64(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_Number_t * v = (jsc_Number_t *) object;
    return jsc_variant_toInt64(v->value);
}

static jsc_float64_t _jsc_Number_toFloat64(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_Number_t * v = (jsc_Number_t *) object;
    return jsc_variant_toFloat64(v->value);
}

static jsc_boolean_t _jsc_Number_toBoolean(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_Number_t * v = (jsc_Number_t *) object;
    return jsc_variant_toBoolean(v->value);
}


jsc_Number_t * jsc_Number_alloc(jsc_variant_t v) {
    jsc_Number_t * n = (jsc_Number_t *) jsc_object_alloc((jsc_class_t *)&jsc_Number, 0);
    n->value.type = v.type;
    n->value.uint64Value = v.uint64Value;
    switch(v.type) {
        case JSC_VARIANT_TYPE_STRING:
            n->value.type = JSC_VARIANT_TYPE_NIL;
            n->value.uint64Value = 0;
            break;
        case JSC_VARIANT_TYPE_OBJECT:
            n->value.type = JSC_VARIANT_TYPE_NIL;
            n->value.uint64Value = 0;
            break;
    }
    return n;
}

jsc_Number_t * jsc_Number_new(jsc_variant_t v) {
    jsc_Number_t * n = jsc_Number_alloc(v);
    jsc_object_autorelease((jsc_object_t *) n);
    return n;
}
