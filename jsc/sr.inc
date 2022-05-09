#include "jsc.h"
#include "sr.h"

/* var implemented */

/* class implemented */
static void _jsc_ChunkReadStream_alloc(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkReadStream_dealloc(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkReadStream___init(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * data);
static jsc_uint8_t _jsc_ChunkReadStream_err(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_boolean_t _jsc_ChunkReadStream_valid(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t n);
static jsc_int8_t _jsc_ChunkReadStream_getInt8(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_uint8_t _jsc_ChunkReadStream_getUint8(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_int16_t _jsc_ChunkReadStream_getInt16(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_uint16_t _jsc_ChunkReadStream_getUint16(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_int32_t _jsc_ChunkReadStream_getInt32(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_uint32_t _jsc_ChunkReadStream_getUint32(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_float32_t _jsc_ChunkReadStream_getFloat32(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_float64_t _jsc_ChunkReadStream_getFloat64(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_string_t _jsc_ChunkReadStream_getString(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_boolean_t _jsc_ChunkReadStream_getBoolean(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_object_t * _jsc_ChunkReadStream_getBytes(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_variant_t _jsc_ChunkReadStream_getValue(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_object_t * _jsc_ChunkReadStream_getObject(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_object_t * _jsc_ChunkReadStream_getArray(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_variant_t _jsc_ChunkReadStream_getValueWithType(jsc_class_t * __isa, jsc_object_t * __object, jsc_uint8_t type);
static void _jsc_ChunkReadStream_seekInt8(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkReadStream_seekUint8(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkReadStream_seekInt16(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkReadStream_seekUint16(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkReadStream_seekInt32(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkReadStream_seekUint32(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkReadStream_seekFloat32(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkReadStream_seekFloat64(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkReadStream_seekString(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkReadStream_seekBoolean(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkReadStream_seekBytes(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkReadStream_seekValue(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkReadStream_seekObject(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkReadStream_seekArray(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkReadStream_seekValueWithType(jsc_class_t * __isa, jsc_object_t * __object, jsc_uint8_t type);
static jsc_int_t _jsc_ChunkReadStream_offset(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkReadStream_setOffset(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t off);
static void _jsc_ChunkReadStream_alloc(jsc_class_t * __isa, jsc_object_t * __object) {}
static void _jsc_ChunkReadStream_dealloc(jsc_class_t * __isa, jsc_object_t * __object) {
	jsc_sr_ChunkReadStream_t * __v = (jsc_sr_ChunkReadStream_t *) __object;
	jsc_setStrong(&__v->_data,NULL);
}
jsc_sr_ChunkReadStream_class_t jsc_sr_ChunkReadStream = {{(jsc_class_t *)&jsc_Object,sizeof(jsc_sr_ChunkReadStream_t),"sr_ChunkReadStream",_jsc_ChunkReadStream_alloc,_jsc_ChunkReadStream_dealloc,NULL,NULL,NULL,NULL,NULL,NULL},_jsc_ChunkReadStream___init,_jsc_ChunkReadStream_err,_jsc_ChunkReadStream_valid,_jsc_ChunkReadStream_getInt8,_jsc_ChunkReadStream_getUint8,_jsc_ChunkReadStream_getInt16,_jsc_ChunkReadStream_getUint16,_jsc_ChunkReadStream_getInt32,_jsc_ChunkReadStream_getUint32,_jsc_ChunkReadStream_getFloat32,_jsc_ChunkReadStream_getFloat64,_jsc_ChunkReadStream_getString,_jsc_ChunkReadStream_getBoolean,_jsc_ChunkReadStream_getBytes,_jsc_ChunkReadStream_getValue,_jsc_ChunkReadStream_getObject,_jsc_ChunkReadStream_getArray,_jsc_ChunkReadStream_getValueWithType,_jsc_ChunkReadStream_seekInt8,_jsc_ChunkReadStream_seekUint8,_jsc_ChunkReadStream_seekInt16,_jsc_ChunkReadStream_seekUint16,_jsc_ChunkReadStream_seekInt32,_jsc_ChunkReadStream_seekUint32,_jsc_ChunkReadStream_seekFloat32,_jsc_ChunkReadStream_seekFloat64,_jsc_ChunkReadStream_seekString,_jsc_ChunkReadStream_seekBoolean,_jsc_ChunkReadStream_seekBytes,_jsc_ChunkReadStream_seekValue,_jsc_ChunkReadStream_seekObject,_jsc_ChunkReadStream_seekArray,_jsc_ChunkReadStream_seekValueWithType,_jsc_ChunkReadStream_offset,_jsc_ChunkReadStream_setOffset};
void jsc_sr_ChunkReadStream___init_(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * data) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->__init) {
            (*s->__init)(__isa,__object,data);
        } else {
            jsc_sr_ChunkReadStream___init_(__isa->isa,__object,data);
        }
    }

    
}
void jsc_sr_ChunkReadStream___init(jsc_object_t * __object, jsc_object_t * data) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkReadStream___init_(__object->isa,__object,data);
}

jsc_uint8_t jsc_sr_ChunkReadStream_err_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->err) {
            return (*s->err)(__isa,__object);
        } else {
            return jsc_sr_ChunkReadStream_err_(__isa->isa,__object);
        }
    }

    return 0;
}
jsc_uint8_t jsc_sr_ChunkReadStream_err(jsc_object_t * __object) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_sr_ChunkReadStream_err_(__object->isa,__object);
}

jsc_boolean_t jsc_sr_ChunkReadStream_valid_(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t n) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->valid) {
            return (*s->valid)(__isa,__object,n);
        } else {
            return jsc_sr_ChunkReadStream_valid_(__isa->isa,__object,n);
        }
    }

    return 0;
}
jsc_boolean_t jsc_sr_ChunkReadStream_valid(jsc_object_t * __object, jsc_int_t n) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_sr_ChunkReadStream_valid_(__object->isa,__object,n);
}

jsc_int8_t jsc_sr_ChunkReadStream_getInt8_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->getInt8) {
            return (*s->getInt8)(__isa,__object);
        } else {
            return jsc_sr_ChunkReadStream_getInt8_(__isa->isa,__object);
        }
    }

    return 0;
}
jsc_int8_t jsc_sr_ChunkReadStream_getInt8(jsc_object_t * __object) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_sr_ChunkReadStream_getInt8_(__object->isa,__object);
}

jsc_uint8_t jsc_sr_ChunkReadStream_getUint8_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->getUint8) {
            return (*s->getUint8)(__isa,__object);
        } else {
            return jsc_sr_ChunkReadStream_getUint8_(__isa->isa,__object);
        }
    }

    return 0;
}
jsc_uint8_t jsc_sr_ChunkReadStream_getUint8(jsc_object_t * __object) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_sr_ChunkReadStream_getUint8_(__object->isa,__object);
}

jsc_int16_t jsc_sr_ChunkReadStream_getInt16_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->getInt16) {
            return (*s->getInt16)(__isa,__object);
        } else {
            return jsc_sr_ChunkReadStream_getInt16_(__isa->isa,__object);
        }
    }

    return 0;
}
jsc_int16_t jsc_sr_ChunkReadStream_getInt16(jsc_object_t * __object) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_sr_ChunkReadStream_getInt16_(__object->isa,__object);
}

jsc_uint16_t jsc_sr_ChunkReadStream_getUint16_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->getUint16) {
            return (*s->getUint16)(__isa,__object);
        } else {
            return jsc_sr_ChunkReadStream_getUint16_(__isa->isa,__object);
        }
    }

    return 0;
}
jsc_uint16_t jsc_sr_ChunkReadStream_getUint16(jsc_object_t * __object) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_sr_ChunkReadStream_getUint16_(__object->isa,__object);
}

jsc_int32_t jsc_sr_ChunkReadStream_getInt32_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->getInt32) {
            return (*s->getInt32)(__isa,__object);
        } else {
            return jsc_sr_ChunkReadStream_getInt32_(__isa->isa,__object);
        }
    }

    return 0;
}
jsc_int32_t jsc_sr_ChunkReadStream_getInt32(jsc_object_t * __object) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_sr_ChunkReadStream_getInt32_(__object->isa,__object);
}

jsc_uint32_t jsc_sr_ChunkReadStream_getUint32_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->getUint32) {
            return (*s->getUint32)(__isa,__object);
        } else {
            return jsc_sr_ChunkReadStream_getUint32_(__isa->isa,__object);
        }
    }

    return 0;
}
jsc_uint32_t jsc_sr_ChunkReadStream_getUint32(jsc_object_t * __object) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_sr_ChunkReadStream_getUint32_(__object->isa,__object);
}

jsc_float32_t jsc_sr_ChunkReadStream_getFloat32_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->getFloat32) {
            return (*s->getFloat32)(__isa,__object);
        } else {
            return jsc_sr_ChunkReadStream_getFloat32_(__isa->isa,__object);
        }
    }

    return 0;
}
jsc_float32_t jsc_sr_ChunkReadStream_getFloat32(jsc_object_t * __object) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_sr_ChunkReadStream_getFloat32_(__object->isa,__object);
}

jsc_float64_t jsc_sr_ChunkReadStream_getFloat64_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->getFloat64) {
            return (*s->getFloat64)(__isa,__object);
        } else {
            return jsc_sr_ChunkReadStream_getFloat64_(__isa->isa,__object);
        }
    }

    return 0;
}
jsc_float64_t jsc_sr_ChunkReadStream_getFloat64(jsc_object_t * __object) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_sr_ChunkReadStream_getFloat64_(__object->isa,__object);
}

jsc_string_t jsc_sr_ChunkReadStream_getString_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return NULL;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->getString) {
            return (*s->getString)(__isa,__object);
        } else {
            return jsc_sr_ChunkReadStream_getString_(__isa->isa,__object);
        }
    }

    return NULL;
}
jsc_string_t jsc_sr_ChunkReadStream_getString(jsc_object_t * __object) {
	if(__object == NULL) {
        return NULL;
    }
    return jsc_sr_ChunkReadStream_getString_(__object->isa,__object);
}

jsc_boolean_t jsc_sr_ChunkReadStream_getBoolean_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->getBoolean) {
            return (*s->getBoolean)(__isa,__object);
        } else {
            return jsc_sr_ChunkReadStream_getBoolean_(__isa->isa,__object);
        }
    }

    return 0;
}
jsc_boolean_t jsc_sr_ChunkReadStream_getBoolean(jsc_object_t * __object) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_sr_ChunkReadStream_getBoolean_(__object->isa,__object);
}

jsc_object_t * jsc_sr_ChunkReadStream_getBytes_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return NULL;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->getBytes) {
            return (*s->getBytes)(__isa,__object);
        } else {
            return jsc_sr_ChunkReadStream_getBytes_(__isa->isa,__object);
        }
    }

    return NULL;
}
jsc_object_t * jsc_sr_ChunkReadStream_getBytes(jsc_object_t * __object) {
	if(__object == NULL) {
        return NULL;
    }
    return jsc_sr_ChunkReadStream_getBytes_(__object->isa,__object);
}

jsc_variant_t jsc_sr_ChunkReadStream_getValue_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return jsc_Nil;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->getValue) {
            return (*s->getValue)(__isa,__object);
        } else {
            return jsc_sr_ChunkReadStream_getValue_(__isa->isa,__object);
        }
    }

    return jsc_Nil;
}
jsc_variant_t jsc_sr_ChunkReadStream_getValue(jsc_object_t * __object) {
	if(__object == NULL) {
        return jsc_Nil;
    }
    return jsc_sr_ChunkReadStream_getValue_(__object->isa,__object);
}

jsc_object_t * jsc_sr_ChunkReadStream_getObject_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return NULL;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->getObject) {
            return (*s->getObject)(__isa,__object);
        } else {
            return jsc_sr_ChunkReadStream_getObject_(__isa->isa,__object);
        }
    }

    return NULL;
}
jsc_object_t * jsc_sr_ChunkReadStream_getObject(jsc_object_t * __object) {
	if(__object == NULL) {
        return NULL;
    }
    return jsc_sr_ChunkReadStream_getObject_(__object->isa,__object);
}

jsc_object_t * jsc_sr_ChunkReadStream_getArray_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return NULL;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->getArray) {
            return (*s->getArray)(__isa,__object);
        } else {
            return jsc_sr_ChunkReadStream_getArray_(__isa->isa,__object);
        }
    }

    return NULL;
}
jsc_object_t * jsc_sr_ChunkReadStream_getArray(jsc_object_t * __object) {
	if(__object == NULL) {
        return NULL;
    }
    return jsc_sr_ChunkReadStream_getArray_(__object->isa,__object);
}

jsc_variant_t jsc_sr_ChunkReadStream_getValueWithType_(jsc_class_t * __isa, jsc_object_t * __object, jsc_uint8_t type) {
	if(__isa == NULL || __object == NULL) {
        return jsc_Nil;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->getValueWithType) {
            return (*s->getValueWithType)(__isa,__object,type);
        } else {
            return jsc_sr_ChunkReadStream_getValueWithType_(__isa->isa,__object,type);
        }
    }

    return jsc_Nil;
}
jsc_variant_t jsc_sr_ChunkReadStream_getValueWithType(jsc_object_t * __object, jsc_uint8_t type) {
	if(__object == NULL) {
        return jsc_Nil;
    }
    return jsc_sr_ChunkReadStream_getValueWithType_(__object->isa,__object,type);
}

void jsc_sr_ChunkReadStream_seekInt8_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->seekInt8) {
            (*s->seekInt8)(__isa,__object);
        } else {
            jsc_sr_ChunkReadStream_seekInt8_(__isa->isa,__object);
        }
    }

    
}
void jsc_sr_ChunkReadStream_seekInt8(jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkReadStream_seekInt8_(__object->isa,__object);
}

void jsc_sr_ChunkReadStream_seekUint8_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->seekUint8) {
            (*s->seekUint8)(__isa,__object);
        } else {
            jsc_sr_ChunkReadStream_seekUint8_(__isa->isa,__object);
        }
    }

    
}
void jsc_sr_ChunkReadStream_seekUint8(jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkReadStream_seekUint8_(__object->isa,__object);
}

void jsc_sr_ChunkReadStream_seekInt16_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->seekInt16) {
            (*s->seekInt16)(__isa,__object);
        } else {
            jsc_sr_ChunkReadStream_seekInt16_(__isa->isa,__object);
        }
    }

    
}
void jsc_sr_ChunkReadStream_seekInt16(jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkReadStream_seekInt16_(__object->isa,__object);
}

void jsc_sr_ChunkReadStream_seekUint16_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->seekUint16) {
            (*s->seekUint16)(__isa,__object);
        } else {
            jsc_sr_ChunkReadStream_seekUint16_(__isa->isa,__object);
        }
    }

    
}
void jsc_sr_ChunkReadStream_seekUint16(jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkReadStream_seekUint16_(__object->isa,__object);
}

void jsc_sr_ChunkReadStream_seekInt32_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->seekInt32) {
            (*s->seekInt32)(__isa,__object);
        } else {
            jsc_sr_ChunkReadStream_seekInt32_(__isa->isa,__object);
        }
    }

    
}
void jsc_sr_ChunkReadStream_seekInt32(jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkReadStream_seekInt32_(__object->isa,__object);
}

void jsc_sr_ChunkReadStream_seekUint32_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->seekUint32) {
            (*s->seekUint32)(__isa,__object);
        } else {
            jsc_sr_ChunkReadStream_seekUint32_(__isa->isa,__object);
        }
    }

    
}
void jsc_sr_ChunkReadStream_seekUint32(jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkReadStream_seekUint32_(__object->isa,__object);
}

void jsc_sr_ChunkReadStream_seekFloat32_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->seekFloat32) {
            (*s->seekFloat32)(__isa,__object);
        } else {
            jsc_sr_ChunkReadStream_seekFloat32_(__isa->isa,__object);
        }
    }

    
}
void jsc_sr_ChunkReadStream_seekFloat32(jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkReadStream_seekFloat32_(__object->isa,__object);
}

void jsc_sr_ChunkReadStream_seekFloat64_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->seekFloat64) {
            (*s->seekFloat64)(__isa,__object);
        } else {
            jsc_sr_ChunkReadStream_seekFloat64_(__isa->isa,__object);
        }
    }

    
}
void jsc_sr_ChunkReadStream_seekFloat64(jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkReadStream_seekFloat64_(__object->isa,__object);
}

void jsc_sr_ChunkReadStream_seekString_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->seekString) {
            (*s->seekString)(__isa,__object);
        } else {
            jsc_sr_ChunkReadStream_seekString_(__isa->isa,__object);
        }
    }

    
}
void jsc_sr_ChunkReadStream_seekString(jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkReadStream_seekString_(__object->isa,__object);
}

void jsc_sr_ChunkReadStream_seekBoolean_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->seekBoolean) {
            (*s->seekBoolean)(__isa,__object);
        } else {
            jsc_sr_ChunkReadStream_seekBoolean_(__isa->isa,__object);
        }
    }

    
}
void jsc_sr_ChunkReadStream_seekBoolean(jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkReadStream_seekBoolean_(__object->isa,__object);
}

void jsc_sr_ChunkReadStream_seekBytes_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->seekBytes) {
            (*s->seekBytes)(__isa,__object);
        } else {
            jsc_sr_ChunkReadStream_seekBytes_(__isa->isa,__object);
        }
    }

    
}
void jsc_sr_ChunkReadStream_seekBytes(jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkReadStream_seekBytes_(__object->isa,__object);
}

void jsc_sr_ChunkReadStream_seekValue_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->seekValue) {
            (*s->seekValue)(__isa,__object);
        } else {
            jsc_sr_ChunkReadStream_seekValue_(__isa->isa,__object);
        }
    }

    
}
void jsc_sr_ChunkReadStream_seekValue(jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkReadStream_seekValue_(__object->isa,__object);
}

void jsc_sr_ChunkReadStream_seekObject_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->seekObject) {
            (*s->seekObject)(__isa,__object);
        } else {
            jsc_sr_ChunkReadStream_seekObject_(__isa->isa,__object);
        }
    }

    
}
void jsc_sr_ChunkReadStream_seekObject(jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkReadStream_seekObject_(__object->isa,__object);
}

void jsc_sr_ChunkReadStream_seekArray_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->seekArray) {
            (*s->seekArray)(__isa,__object);
        } else {
            jsc_sr_ChunkReadStream_seekArray_(__isa->isa,__object);
        }
    }

    
}
void jsc_sr_ChunkReadStream_seekArray(jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkReadStream_seekArray_(__object->isa,__object);
}

void jsc_sr_ChunkReadStream_seekValueWithType_(jsc_class_t * __isa, jsc_object_t * __object, jsc_uint8_t type) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->seekValueWithType) {
            (*s->seekValueWithType)(__isa,__object,type);
        } else {
            jsc_sr_ChunkReadStream_seekValueWithType_(__isa->isa,__object,type);
        }
    }

    
}
void jsc_sr_ChunkReadStream_seekValueWithType(jsc_object_t * __object, jsc_uint8_t type) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkReadStream_seekValueWithType_(__object->isa,__object,type);
}

jsc_int_t jsc_sr_ChunkReadStream_offset_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->offset) {
            return (*s->offset)(__isa,__object);
        } else {
            return jsc_sr_ChunkReadStream_offset_(__isa->isa,__object);
        }
    }

    return 0;
}
jsc_int_t jsc_sr_ChunkReadStream_offset(jsc_object_t * __object) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_sr_ChunkReadStream_offset_(__object->isa,__object);
}

void jsc_sr_ChunkReadStream_setOffset_(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t off) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkReadStream)) {
        jsc_sr_ChunkReadStream_class_t * s = (jsc_sr_ChunkReadStream_class_t *) __isa;
        if(s->setOffset) {
            (*s->setOffset)(__isa,__object,off);
        } else {
            jsc_sr_ChunkReadStream_setOffset_(__isa->isa,__object,off);
        }
    }

    
}
void jsc_sr_ChunkReadStream_setOffset(jsc_object_t * __object, jsc_int_t off) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkReadStream_setOffset_(__object->isa,__object,off);
}

jsc_object_t * jsc_sr_ChunkReadStream_new(jsc_object_t * data) {
	jsc_object_t * __object = jsc_object_new((jsc_class_t *)&jsc_sr_ChunkReadStream,0);
	jsc_sr_ChunkReadStream___init_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,data);
	return __object;
}
static void _jsc_Buffer_alloc(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_Buffer_dealloc(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_Buffer___init(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t capacity);
static void _jsc_Buffer_capacity(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t v);
static jsc_int_t _jsc_Buffer_length(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_Buffer_setLength(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t v);
static jsc_object_t * _jsc_Buffer_toDataView(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_Buffer_alloc(jsc_class_t * __isa, jsc_object_t * __object) {}
static void _jsc_Buffer_dealloc(jsc_class_t * __isa, jsc_object_t * __object) {
	jsc_sr_Buffer_t * __v = (jsc_sr_Buffer_t *) __object;
	jsc_setStrong(&__v->_buffer,NULL);
	jsc_setStrong(&__v->_view,NULL);
}
jsc_sr_Buffer_class_t jsc_sr_Buffer = {{(jsc_class_t *)&jsc_Object,sizeof(jsc_sr_Buffer_t),"sr_Buffer",_jsc_Buffer_alloc,_jsc_Buffer_dealloc,NULL,NULL,NULL,NULL,NULL,NULL},_jsc_Buffer___init,_jsc_Buffer_capacity,_jsc_Buffer_length,_jsc_Buffer_setLength,_jsc_Buffer_toDataView};
void jsc_sr_Buffer___init_(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t capacity) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_Buffer)) {
        jsc_sr_Buffer_class_t * s = (jsc_sr_Buffer_class_t *) __isa;
        if(s->__init) {
            (*s->__init)(__isa,__object,capacity);
        } else {
            jsc_sr_Buffer___init_(__isa->isa,__object,capacity);
        }
    }

    
}
void jsc_sr_Buffer___init(jsc_object_t * __object, jsc_int_t capacity) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_Buffer___init_(__object->isa,__object,capacity);
}

void jsc_sr_Buffer_capacity_(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t v) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_Buffer)) {
        jsc_sr_Buffer_class_t * s = (jsc_sr_Buffer_class_t *) __isa;
        if(s->capacity) {
            (*s->capacity)(__isa,__object,v);
        } else {
            jsc_sr_Buffer_capacity_(__isa->isa,__object,v);
        }
    }

    
}
void jsc_sr_Buffer_capacity(jsc_object_t * __object, jsc_int_t v) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_Buffer_capacity_(__object->isa,__object,v);
}

jsc_int_t jsc_sr_Buffer_length_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_Buffer)) {
        jsc_sr_Buffer_class_t * s = (jsc_sr_Buffer_class_t *) __isa;
        if(s->length) {
            return (*s->length)(__isa,__object);
        } else {
            return jsc_sr_Buffer_length_(__isa->isa,__object);
        }
    }

    return 0;
}
jsc_int_t jsc_sr_Buffer_length(jsc_object_t * __object) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_sr_Buffer_length_(__object->isa,__object);
}

void jsc_sr_Buffer_setLength_(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t v) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_Buffer)) {
        jsc_sr_Buffer_class_t * s = (jsc_sr_Buffer_class_t *) __isa;
        if(s->setLength) {
            (*s->setLength)(__isa,__object,v);
        } else {
            jsc_sr_Buffer_setLength_(__isa->isa,__object,v);
        }
    }

    
}
void jsc_sr_Buffer_setLength(jsc_object_t * __object, jsc_int_t v) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_Buffer_setLength_(__object->isa,__object,v);
}

jsc_object_t * jsc_sr_Buffer_toDataView_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return NULL;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_Buffer)) {
        jsc_sr_Buffer_class_t * s = (jsc_sr_Buffer_class_t *) __isa;
        if(s->toDataView) {
            return (*s->toDataView)(__isa,__object);
        } else {
            return jsc_sr_Buffer_toDataView_(__isa->isa,__object);
        }
    }

    return NULL;
}
jsc_object_t * jsc_sr_Buffer_toDataView(jsc_object_t * __object) {
	if(__object == NULL) {
        return NULL;
    }
    return jsc_sr_Buffer_toDataView_(__object->isa,__object);
}

jsc_object_t * jsc_sr_Buffer_new(jsc_int_t capacity) {
	jsc_object_t * __object = jsc_object_new((jsc_class_t *)&jsc_sr_Buffer,0);
	jsc_sr_Buffer___init_((jsc_class_t *)&jsc_sr_Buffer,__object,capacity);
	return __object;
}
static void _jsc_ChunkWriteStream_alloc(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkWriteStream_dealloc(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkWriteStream___init(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_uint8_t _jsc_ChunkWriteStream_err(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_ChunkWriteStream_setInt8(jsc_class_t * __isa, jsc_object_t * __object, jsc_int8_t v);
static void _jsc_ChunkWriteStream_setUint8(jsc_class_t * __isa, jsc_object_t * __object, jsc_uint8_t v);
static void _jsc_ChunkWriteStream_setInt16(jsc_class_t * __isa, jsc_object_t * __object, jsc_int16_t v);
static void _jsc_ChunkWriteStream_setUint16(jsc_class_t * __isa, jsc_object_t * __object, jsc_uint16_t v);
static void _jsc_ChunkWriteStream_setInt32(jsc_class_t * __isa, jsc_object_t * __object, jsc_int32_t v);
static void _jsc_ChunkWriteStream_setUint32(jsc_class_t * __isa, jsc_object_t * __object, jsc_uint32_t v);
static void _jsc_ChunkWriteStream_setFloat32(jsc_class_t * __isa, jsc_object_t * __object, jsc_float32_t v);
static void _jsc_ChunkWriteStream_setFloat64(jsc_class_t * __isa, jsc_object_t * __object, jsc_float32_t v);
static void _jsc_ChunkWriteStream_setString(jsc_class_t * __isa, jsc_object_t * __object, jsc_string_t v);
static void _jsc_ChunkWriteStream_setBoolean(jsc_class_t * __isa, jsc_object_t * __object, jsc_boolean_t v);
static void _jsc_ChunkWriteStream_setBytes(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * b);
static void _jsc_ChunkWriteStream_setValue(jsc_class_t * __isa, jsc_object_t * __object, jsc_variant_t v);
static void _jsc_ChunkWriteStream_setObject(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * v);
static void _jsc_ChunkWriteStream_setArray(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * v);
static void _jsc_ChunkWriteStream_alloc(jsc_class_t * __isa, jsc_object_t * __object) {}
static void _jsc_ChunkWriteStream_dealloc(jsc_class_t * __isa, jsc_object_t * __object) {
}
jsc_sr_ChunkWriteStream_class_t jsc_sr_ChunkWriteStream = {{{(jsc_class_t *)&jsc_sr_Buffer,sizeof(jsc_sr_ChunkWriteStream_t),"sr_ChunkWriteStream",_jsc_ChunkWriteStream_alloc,_jsc_ChunkWriteStream_dealloc,NULL,NULL,NULL,NULL,NULL,NULL},NULL,NULL,NULL,NULL,NULL},_jsc_ChunkWriteStream___init,_jsc_ChunkWriteStream_err,_jsc_ChunkWriteStream_setInt8,_jsc_ChunkWriteStream_setUint8,_jsc_ChunkWriteStream_setInt16,_jsc_ChunkWriteStream_setUint16,_jsc_ChunkWriteStream_setInt32,_jsc_ChunkWriteStream_setUint32,_jsc_ChunkWriteStream_setFloat32,_jsc_ChunkWriteStream_setFloat64,_jsc_ChunkWriteStream_setString,_jsc_ChunkWriteStream_setBoolean,_jsc_ChunkWriteStream_setBytes,_jsc_ChunkWriteStream_setValue,_jsc_ChunkWriteStream_setObject,_jsc_ChunkWriteStream_setArray};
void jsc_sr_ChunkWriteStream___init_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkWriteStream)) {
        jsc_sr_ChunkWriteStream_class_t * s = (jsc_sr_ChunkWriteStream_class_t *) __isa;
        if(s->__init) {
            (*s->__init)(__isa,__object);
        } else {
            jsc_sr_ChunkWriteStream___init_(__isa->isa,__object);
        }
    }

    
}
void jsc_sr_ChunkWriteStream___init(jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkWriteStream___init_(__object->isa,__object);
}

jsc_uint8_t jsc_sr_ChunkWriteStream_err_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkWriteStream)) {
        jsc_sr_ChunkWriteStream_class_t * s = (jsc_sr_ChunkWriteStream_class_t *) __isa;
        if(s->err) {
            return (*s->err)(__isa,__object);
        } else {
            return jsc_sr_ChunkWriteStream_err_(__isa->isa,__object);
        }
    }

    return 0;
}
jsc_uint8_t jsc_sr_ChunkWriteStream_err(jsc_object_t * __object) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_sr_ChunkWriteStream_err_(__object->isa,__object);
}

void jsc_sr_ChunkWriteStream_setInt8_(jsc_class_t * __isa, jsc_object_t * __object, jsc_int8_t v) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkWriteStream)) {
        jsc_sr_ChunkWriteStream_class_t * s = (jsc_sr_ChunkWriteStream_class_t *) __isa;
        if(s->setInt8) {
            (*s->setInt8)(__isa,__object,v);
        } else {
            jsc_sr_ChunkWriteStream_setInt8_(__isa->isa,__object,v);
        }
    }

    
}
void jsc_sr_ChunkWriteStream_setInt8(jsc_object_t * __object, jsc_int8_t v) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkWriteStream_setInt8_(__object->isa,__object,v);
}

void jsc_sr_ChunkWriteStream_setUint8_(jsc_class_t * __isa, jsc_object_t * __object, jsc_uint8_t v) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkWriteStream)) {
        jsc_sr_ChunkWriteStream_class_t * s = (jsc_sr_ChunkWriteStream_class_t *) __isa;
        if(s->setUint8) {
            (*s->setUint8)(__isa,__object,v);
        } else {
            jsc_sr_ChunkWriteStream_setUint8_(__isa->isa,__object,v);
        }
    }

    
}
void jsc_sr_ChunkWriteStream_setUint8(jsc_object_t * __object, jsc_uint8_t v) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkWriteStream_setUint8_(__object->isa,__object,v);
}

void jsc_sr_ChunkWriteStream_setInt16_(jsc_class_t * __isa, jsc_object_t * __object, jsc_int16_t v) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkWriteStream)) {
        jsc_sr_ChunkWriteStream_class_t * s = (jsc_sr_ChunkWriteStream_class_t *) __isa;
        if(s->setInt16) {
            (*s->setInt16)(__isa,__object,v);
        } else {
            jsc_sr_ChunkWriteStream_setInt16_(__isa->isa,__object,v);
        }
    }

    
}
void jsc_sr_ChunkWriteStream_setInt16(jsc_object_t * __object, jsc_int16_t v) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkWriteStream_setInt16_(__object->isa,__object,v);
}

void jsc_sr_ChunkWriteStream_setUint16_(jsc_class_t * __isa, jsc_object_t * __object, jsc_uint16_t v) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkWriteStream)) {
        jsc_sr_ChunkWriteStream_class_t * s = (jsc_sr_ChunkWriteStream_class_t *) __isa;
        if(s->setUint16) {
            (*s->setUint16)(__isa,__object,v);
        } else {
            jsc_sr_ChunkWriteStream_setUint16_(__isa->isa,__object,v);
        }
    }

    
}
void jsc_sr_ChunkWriteStream_setUint16(jsc_object_t * __object, jsc_uint16_t v) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkWriteStream_setUint16_(__object->isa,__object,v);
}

void jsc_sr_ChunkWriteStream_setInt32_(jsc_class_t * __isa, jsc_object_t * __object, jsc_int32_t v) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkWriteStream)) {
        jsc_sr_ChunkWriteStream_class_t * s = (jsc_sr_ChunkWriteStream_class_t *) __isa;
        if(s->setInt32) {
            (*s->setInt32)(__isa,__object,v);
        } else {
            jsc_sr_ChunkWriteStream_setInt32_(__isa->isa,__object,v);
        }
    }

    
}
void jsc_sr_ChunkWriteStream_setInt32(jsc_object_t * __object, jsc_int32_t v) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkWriteStream_setInt32_(__object->isa,__object,v);
}

void jsc_sr_ChunkWriteStream_setUint32_(jsc_class_t * __isa, jsc_object_t * __object, jsc_uint32_t v) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkWriteStream)) {
        jsc_sr_ChunkWriteStream_class_t * s = (jsc_sr_ChunkWriteStream_class_t *) __isa;
        if(s->setUint32) {
            (*s->setUint32)(__isa,__object,v);
        } else {
            jsc_sr_ChunkWriteStream_setUint32_(__isa->isa,__object,v);
        }
    }

    
}
void jsc_sr_ChunkWriteStream_setUint32(jsc_object_t * __object, jsc_uint32_t v) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkWriteStream_setUint32_(__object->isa,__object,v);
}

void jsc_sr_ChunkWriteStream_setFloat32_(jsc_class_t * __isa, jsc_object_t * __object, jsc_float32_t v) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkWriteStream)) {
        jsc_sr_ChunkWriteStream_class_t * s = (jsc_sr_ChunkWriteStream_class_t *) __isa;
        if(s->setFloat32) {
            (*s->setFloat32)(__isa,__object,v);
        } else {
            jsc_sr_ChunkWriteStream_setFloat32_(__isa->isa,__object,v);
        }
    }

    
}
void jsc_sr_ChunkWriteStream_setFloat32(jsc_object_t * __object, jsc_float32_t v) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkWriteStream_setFloat32_(__object->isa,__object,v);
}

void jsc_sr_ChunkWriteStream_setFloat64_(jsc_class_t * __isa, jsc_object_t * __object, jsc_float32_t v) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkWriteStream)) {
        jsc_sr_ChunkWriteStream_class_t * s = (jsc_sr_ChunkWriteStream_class_t *) __isa;
        if(s->setFloat64) {
            (*s->setFloat64)(__isa,__object,v);
        } else {
            jsc_sr_ChunkWriteStream_setFloat64_(__isa->isa,__object,v);
        }
    }

    
}
void jsc_sr_ChunkWriteStream_setFloat64(jsc_object_t * __object, jsc_float32_t v) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkWriteStream_setFloat64_(__object->isa,__object,v);
}

void jsc_sr_ChunkWriteStream_setString_(jsc_class_t * __isa, jsc_object_t * __object, jsc_string_t v) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkWriteStream)) {
        jsc_sr_ChunkWriteStream_class_t * s = (jsc_sr_ChunkWriteStream_class_t *) __isa;
        if(s->setString) {
            (*s->setString)(__isa,__object,v);
        } else {
            jsc_sr_ChunkWriteStream_setString_(__isa->isa,__object,v);
        }
    }

    
}
void jsc_sr_ChunkWriteStream_setString(jsc_object_t * __object, jsc_string_t v) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkWriteStream_setString_(__object->isa,__object,v);
}

void jsc_sr_ChunkWriteStream_setBoolean_(jsc_class_t * __isa, jsc_object_t * __object, jsc_boolean_t v) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkWriteStream)) {
        jsc_sr_ChunkWriteStream_class_t * s = (jsc_sr_ChunkWriteStream_class_t *) __isa;
        if(s->setBoolean) {
            (*s->setBoolean)(__isa,__object,v);
        } else {
            jsc_sr_ChunkWriteStream_setBoolean_(__isa->isa,__object,v);
        }
    }

    
}
void jsc_sr_ChunkWriteStream_setBoolean(jsc_object_t * __object, jsc_boolean_t v) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkWriteStream_setBoolean_(__object->isa,__object,v);
}

void jsc_sr_ChunkWriteStream_setBytes_(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * b) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkWriteStream)) {
        jsc_sr_ChunkWriteStream_class_t * s = (jsc_sr_ChunkWriteStream_class_t *) __isa;
        if(s->setBytes) {
            (*s->setBytes)(__isa,__object,b);
        } else {
            jsc_sr_ChunkWriteStream_setBytes_(__isa->isa,__object,b);
        }
    }

    
}
void jsc_sr_ChunkWriteStream_setBytes(jsc_object_t * __object, jsc_object_t * b) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkWriteStream_setBytes_(__object->isa,__object,b);
}

void jsc_sr_ChunkWriteStream_setValue_(jsc_class_t * __isa, jsc_object_t * __object, jsc_variant_t v) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkWriteStream)) {
        jsc_sr_ChunkWriteStream_class_t * s = (jsc_sr_ChunkWriteStream_class_t *) __isa;
        if(s->setValue) {
            (*s->setValue)(__isa,__object,v);
        } else {
            jsc_sr_ChunkWriteStream_setValue_(__isa->isa,__object,v);
        }
    }

    
}
void jsc_sr_ChunkWriteStream_setValue(jsc_object_t * __object, jsc_variant_t v) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkWriteStream_setValue_(__object->isa,__object,v);
}

void jsc_sr_ChunkWriteStream_setObject_(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * v) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkWriteStream)) {
        jsc_sr_ChunkWriteStream_class_t * s = (jsc_sr_ChunkWriteStream_class_t *) __isa;
        if(s->setObject) {
            (*s->setObject)(__isa,__object,v);
        } else {
            jsc_sr_ChunkWriteStream_setObject_(__isa->isa,__object,v);
        }
    }

    
}
void jsc_sr_ChunkWriteStream_setObject(jsc_object_t * __object, jsc_object_t * v) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkWriteStream_setObject_(__object->isa,__object,v);
}

void jsc_sr_ChunkWriteStream_setArray_(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * v) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_sr_ChunkWriteStream)) {
        jsc_sr_ChunkWriteStream_class_t * s = (jsc_sr_ChunkWriteStream_class_t *) __isa;
        if(s->setArray) {
            (*s->setArray)(__isa,__object,v);
        } else {
            jsc_sr_ChunkWriteStream_setArray_(__isa->isa,__object,v);
        }
    }

    
}
void jsc_sr_ChunkWriteStream_setArray(jsc_object_t * __object, jsc_object_t * v) {
	if(__object == NULL) {
        return ;
    }
    jsc_sr_ChunkWriteStream_setArray_(__object->isa,__object,v);
}

jsc_object_t * jsc_sr_ChunkWriteStream_new() {
	jsc_object_t * __object = jsc_object_new((jsc_class_t *)&jsc_sr_ChunkWriteStream,0);
	jsc_sr_ChunkWriteStream___init_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object);
	return __object;
}
