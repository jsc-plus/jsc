//
//  jsc_DataView.c
//  jsc
//
//  Created by 张海龙 on 2022/5/4.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#include "jsc_type.h"
#include "jsc_class.h"
#include "jsc_variant.h"
#include "jsc_buffer.h"
#include "jsc_ArrayBuffer.h"
#include "jsc_DataView.h"


static void _jsc_DataView_alloc(struct jsc_class_t * isa, struct jsc_object_t * object);
static void _jsc_DataView_dealloc(struct jsc_class_t * isa, struct jsc_object_t * object);


static jsc_object_t * _jsc_DataView_buffer(jsc_class_t * isa, jsc_object_t * object);
static jsc_int_t _jsc_DataView_byteOffset(jsc_class_t * isa, jsc_object_t * object);
static jsc_int_t _jsc_DataView_byteLength(jsc_class_t * isa, jsc_object_t * object);
static jsc_int8_t _jsc_DataView_getInt8(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset);
static jsc_uint8_t _jsc_DataView_getUint8(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset);
static jsc_int16_t _jsc_DataView_getInt16(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
static jsc_uint16_t _jsc_DataView_getUint16(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
static jsc_int32_t _jsc_DataView_getInt32(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
static jsc_uint32_t _jsc_DataView_getUint32(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
static jsc_int64_t _jsc_DataView_getInt64(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
static jsc_uint64_t _jsc_DataView_getUint64(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
static jsc_float32_t _jsc_DataView_getFloat32(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
static jsc_float64_t _jsc_DataView_getFloat64(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);

static jsc_string_t _jsc_DataView_getString(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset);
static jsc_object_t * _jsc_DataView_getData(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int_t length);

static void _jsc_DataView_setInt8(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int8_t value);
static void _jsc_DataView_setUint8(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint8_t value);
static void _jsc_DataView_setInt16(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int16_t value,jsc_boolean_t littleEndian);
static void _jsc_DataView_setUint16(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint16_t value,jsc_boolean_t littleEndian);
static void _jsc_DataView_setInt32(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int32_t value,jsc_boolean_t littleEndian);
static void _jsc_DataView_setUint32(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint32_t value,jsc_boolean_t littleEndian);
static void _jsc_DataView_setInt64(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int64_t value,jsc_boolean_t littleEndian);
static void _jsc_DataView_setUint64(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint64_t value,jsc_boolean_t littleEndian);
static void _jsc_DataView_setFloat32(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_float32_t value,jsc_boolean_t littleEndian);
static void _jsc_DataView_setFloat64(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_float64_t value,jsc_boolean_t littleEndian);

static jsc_int_t _jsc_DataView_setString(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_string_t value);
static jsc_int_t _jsc_DataView_setData(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_object_t * data);

jsc_DataView_class_t jsc_DataView = { {&jsc_Object,sizeof(jsc_DataView_t),"DataView",
    _jsc_DataView_alloc,_jsc_DataView_dealloc,NULL,NULL,NULL,NULL,NULL,NULL},
    _jsc_DataView_buffer,
    _jsc_DataView_byteOffset,
    _jsc_DataView_byteLength,
    _jsc_DataView_getInt8,
    _jsc_DataView_getUint8,
    _jsc_DataView_getInt16,
    _jsc_DataView_getUint16,
    _jsc_DataView_getInt32,
    _jsc_DataView_getUint32,
    _jsc_DataView_getInt64,
    _jsc_DataView_getUint64,
    _jsc_DataView_getFloat32,
    _jsc_DataView_getFloat64,
    
    _jsc_DataView_getString,
    _jsc_DataView_getData,
    
    _jsc_DataView_setInt8,
    _jsc_DataView_setUint8,
    _jsc_DataView_setInt16,
    _jsc_DataView_setUint16,
    _jsc_DataView_setInt32,
    _jsc_DataView_setUint32,
    _jsc_DataView_setInt64,
    _jsc_DataView_setUint64,
    _jsc_DataView_setFloat32,
    _jsc_DataView_setFloat64,
    
    _jsc_DataView_setString,
    _jsc_DataView_setData,
};

jsc_object_t * jsc_DataView_buffer_(jsc_class_t * isa, jsc_object_t * object) {
    
    if(isa == NULL || object == NULL) {
        return NULL;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->buffer) {
            return (*s->buffer)(isa,object);
        } else {
            return jsc_DataView_buffer_(isa->isa,object);
        }
    }

    return NULL;
}

jsc_int_t jsc_DataView_byteOffset_(jsc_class_t * isa, jsc_object_t * object) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->byteOffset) {
            return (*s->byteOffset)(isa,object);
        } else {
            return jsc_DataView_byteOffset_(isa->isa,object);
        }
    }

    return 0;
}

jsc_int_t jsc_DataView_byteLength_(jsc_class_t * isa, jsc_object_t * object) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->byteLength) {
            return (*s->byteLength)(isa,object);
        } else {
            return jsc_DataView_byteLength_(isa->isa,object);
        }
    }

    return 0;
}

jsc_int8_t jsc_DataView_getInt8_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->getInt8) {
            return (*s->getInt8)(isa,object,offset);
        } else {
            return jsc_DataView_getInt8_(isa->isa,object,offset);
        }
    }

    return 0;
}

jsc_uint8_t jsc_DataView_getUint8_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->getUint8) {
            return (*s->getUint8)(isa,object,offset);
        } else {
            return jsc_DataView_getUint8_(isa->isa,object,offset);
        }
    }

    return 0;
}

jsc_int16_t jsc_DataView_getInt16_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->getInt16) {
            return (*s->getInt16)(isa,object,offset,littleEndian);
        } else {
            return jsc_DataView_getInt16_(isa->isa,object,offset,littleEndian);
        }
    }

    return 0;
}

jsc_uint16_t jsc_DataView_getUint16_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->getUint16) {
            return (*s->getUint16)(isa,object,offset,littleEndian);
        } else {
            return jsc_DataView_getUint16_(isa->isa,object,offset,littleEndian);
        }
    }

    return 0;
}

jsc_int32_t jsc_DataView_getInt32_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->getInt32) {
            return (*s->getInt32)(isa,object,offset,littleEndian);
        } else {
            return jsc_DataView_getInt32_(isa->isa,object,offset,littleEndian);
        }
    }

    return 0;
}

jsc_uint32_t jsc_DataView_getUint32_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->getUint32) {
            return (*s->getUint32)(isa,object,offset,littleEndian);
        } else {
            return jsc_DataView_getUint32_(isa->isa,object,offset,littleEndian);
        }
    }

    return 0;
}

jsc_int64_t jsc_DataView_getInt64_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->getInt64) {
            return (*s->getInt64)(isa,object,offset,littleEndian);
        } else {
            return jsc_DataView_getInt64_(isa->isa,object,offset,littleEndian);
        }
    }

    return 0;
}

jsc_uint64_t jsc_DataView_getUint64_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->getUint64) {
            return (*s->getUint64)(isa,object,offset,littleEndian);
        } else {
            return jsc_DataView_getUint64_(isa->isa,object,offset,littleEndian);
        }
    }

    return 0;
}

jsc_float32_t jsc_DataView_getFloat32_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->getFloat32) {
            return (*s->getFloat32)(isa,object,offset,littleEndian);
        } else {
            return jsc_DataView_getFloat32_(isa->isa,object,offset,littleEndian);
        }
    }

    return 0;
}

jsc_float64_t jsc_DataView_getFloat64_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->getFloat64) {
            return (*s->getFloat64)(isa,object,offset,littleEndian);
        } else {
            return jsc_DataView_getFloat64_(isa->isa,object,offset,littleEndian);
        }
    }

    return 0;
}

jsc_string_t jsc_DataView_getString_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset) {
    
    if(isa == NULL || object == NULL) {
        return NULL;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->getString) {
            return (*s->getString)(isa,object,offset);
        } else {
            return jsc_DataView_getString_(isa->isa,object,offset);
        }
    }

    return NULL;
    
}

jsc_object_t * jsc_DataView_getData_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int_t length) {
    
    if(isa == NULL || object == NULL) {
        return NULL;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->getData) {
            return (*s->getData)(isa,object,offset,length);
        } else {
            return jsc_DataView_getData_(isa->isa,object,offset,length);
        }
    }

    return NULL;
    
}

void jsc_DataView_setInt8_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int8_t value) {
    
    if(isa == NULL || object == NULL) {
        return ;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->setInt8) {
            (*s->setInt8)(isa,object,offset,value);
        } else {
            jsc_DataView_setInt8_(isa->isa,object,offset,value);
        }
    }

}

void jsc_DataView_setUint8_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint8_t value) {
    
    if(isa == NULL || object == NULL) {
        return ;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->setUint8) {
            (*s->setUint8)(isa,object,offset,value);
        } else {
            jsc_DataView_setUint8_(isa->isa,object,offset,value);
        }
    }
}

void jsc_DataView_setInt16_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int16_t value,jsc_boolean_t littleEndian) {
    if(isa == NULL || object == NULL) {
        return ;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->setInt16) {
            (*s->setInt16)(isa,object,offset,value,littleEndian);
        } else {
            jsc_DataView_setInt16_(isa->isa,object,offset,value,littleEndian);
        }
    }
}

void jsc_DataView_setUint16_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint16_t value,jsc_boolean_t littleEndian) {
    if(isa == NULL || object == NULL) {
        return ;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->setUint16) {
            (*s->setUint16)(isa,object,offset,value,littleEndian);
        } else {
            jsc_DataView_setUint16_(isa->isa,object,offset,value,littleEndian);
        }
    }
}

void jsc_DataView_setInt32_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int32_t value,jsc_boolean_t littleEndian) {
    
    if(isa == NULL || object == NULL) {
        return ;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->setInt32) {
            (*s->setInt32)(isa,object,offset,value,littleEndian);
        } else {
            jsc_DataView_setInt32_(isa->isa,object,offset,value,littleEndian);
        }
    }
}

void jsc_DataView_setUint32_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint32_t value,jsc_boolean_t littleEndian) {
    if(isa == NULL || object == NULL) {
        return ;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->setUint32) {
            (*s->setUint32)(isa,object,offset,value,littleEndian);
        } else {
            jsc_DataView_setUint32_(isa->isa,object,offset,value,littleEndian);
        }
    }
}

void jsc_DataView_setInt64_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int64_t value,jsc_boolean_t littleEndian) {
    if(isa == NULL || object == NULL) {
        return ;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->setInt64) {
            (*s->setInt64)(isa,object,offset,value,littleEndian);
        } else {
            jsc_DataView_setInt64_(isa->isa,object,offset,value,littleEndian);
        }
    }
}

void jsc_DataView_setUint64_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint64_t value,jsc_boolean_t littleEndian) {
    if(isa == NULL || object == NULL) {
        return ;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->setUint64) {
            (*s->setUint64)(isa,object,offset,value,littleEndian);
        } else {
            jsc_DataView_setUint64_(isa->isa,object,offset,value,littleEndian);
        }
    }
}

void jsc_DataView_setFloat32_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_float32_t value,jsc_boolean_t littleEndian) {
    if(isa == NULL || object == NULL) {
        return ;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->setFloat32) {
            (*s->setFloat32)(isa,object,offset,value,littleEndian);
        } else {
            jsc_DataView_setFloat32_(isa->isa,object,offset,value,littleEndian);
        }
    }
}

void jsc_DataView_setFloat64_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_float64_t value,jsc_boolean_t littleEndian) {
    if(isa == NULL || object == NULL) {
        return ;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->setFloat64) {
            (*s->setFloat64)(isa,object,offset,value,littleEndian);
        } else {
            jsc_DataView_setFloat64_(isa->isa,object,offset,value,littleEndian);
        }
    }
}

jsc_int_t jsc_DataView_setString_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_string_t value) {
    
    if(isa == NULL || object == NULL) {
        return -1;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->setString) {
            (*s->setString)(isa,object,offset,value);
        } else {
            jsc_DataView_setString_(isa->isa,object,offset,value);
        }
    }
    
    return -1;
}

jsc_int_t jsc_DataView_setData_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_object_t * data) {
    
    if(isa == NULL || object == NULL) {
        return -1;
    }
    
    if(jsc_class_isKind(isa, &jsc_DataView.base)) {
        jsc_DataView_class_t * s = (jsc_DataView_class_t *) isa;
        if(s->setData) {
            (*s->setData)(isa,object,offset,data);
        } else {
            jsc_DataView_setData_(isa->isa,object,offset,data);
        }
    }
    
    return -1;
    
}


jsc_object_t * jsc_DataView_buffer(jsc_object_t * object) {
    if(object == NULL) {
        return NULL;
    }
    return jsc_DataView_buffer_(object->isa,object);
}

jsc_int_t jsc_DataView_byteOffset(jsc_object_t * object) {
    if(object == NULL) {
        return 0;
    }
    return jsc_DataView_byteOffset_(object->isa,object);
}

jsc_int_t jsc_DataView_byteLength(jsc_object_t * object) {
    if(object == NULL) {
        return 0;
    }
    return jsc_DataView_byteLength_(object->isa,object);
}
jsc_int8_t jsc_DataView_getInt8(jsc_object_t * object,jsc_int_t offset) {
    if(object == NULL) {
        return 0;
    }
    return jsc_DataView_getInt8_(object->isa,object,offset);
}
jsc_uint8_t jsc_DataView_getUint8(jsc_object_t * object,jsc_int_t offset) {
    if(object == NULL) {
        return 0;
    }
    return jsc_DataView_getUint8_(object->isa,object,offset);
}
jsc_int16_t jsc_DataView_getInt16(jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    if(object == NULL) {
        return 0;
    }
    return jsc_DataView_getInt16_(object->isa,object,offset,littleEndian);
}
jsc_uint16_t jsc_DataView_getUint16(jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian){
    if(object == NULL) {
        return 0;
    }
    return jsc_DataView_getUint16_(object->isa,object,offset,littleEndian);
}
jsc_int32_t jsc_DataView_getInt32(jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    if(object == NULL) {
        return 0;
    }
    return jsc_DataView_getInt32_(object->isa,object,offset,littleEndian);
}
jsc_uint32_t jsc_DataView_getUint32(jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    if(object == NULL) {
        return 0;
    }
    return jsc_DataView_getUint32_(object->isa,object,offset,littleEndian);
}
jsc_int64_t jsc_DataView_getInt64(jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    if(object == NULL) {
        return 0;
    }
    return jsc_DataView_getInt64_(object->isa,object,offset,littleEndian);
}
jsc_uint64_t jsc_DataView_getUint64(jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    if(object == NULL) {
        return 0;
    }
    return jsc_DataView_getUint64_(object->isa,object,offset,littleEndian);
}
jsc_float32_t jsc_DataView_getFloat32(jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    if(object == NULL) {
        return 0;
    }
    return jsc_DataView_getFloat32_(object->isa,object,offset,littleEndian);
}

jsc_float64_t jsc_DataView_getFloat64(jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    if(object == NULL) {
        return 0;
    }
    return jsc_DataView_getFloat64_(object->isa,object,offset,littleEndian);
}

jsc_string_t jsc_DataView_getString(jsc_object_t * object,jsc_int_t offset) {
    if(object == NULL) {
        return NULL;
    }
    return jsc_DataView_getString_(object->isa,object,offset);
}

jsc_object_t * jsc_DataView_getData(jsc_object_t * object,jsc_int_t offset,jsc_int_t length) {
    if(object == NULL) {
        return NULL;
    }
    return jsc_DataView_getData_(object->isa,object,offset,length);
}

void jsc_DataView_setInt8(jsc_object_t * object,jsc_int_t offset,jsc_int8_t value) {
    if(object == NULL) {
        return;
    }
    jsc_DataView_setInt8_(object->isa,object,offset,value);
}
void jsc_DataView_setUint8(jsc_object_t * object,jsc_int_t offset,jsc_uint8_t value) {
    if(object == NULL) {
        return;
    }
    jsc_DataView_setUint8_(object->isa,object,offset,value);
}

void jsc_DataView_setInt16(jsc_object_t * object,jsc_int_t offset,jsc_int16_t value,jsc_boolean_t littleEndian) {
    if(object == NULL) {
        return;
    }
    jsc_DataView_setInt16_(object->isa,object,offset,value,littleEndian);
}
void jsc_DataView_setUint16(jsc_object_t * object,jsc_int_t offset,jsc_uint16_t value,jsc_boolean_t littleEndian) {
    if(object == NULL) {
        return;
    }
    jsc_DataView_setUint16_(object->isa,object,offset,value,littleEndian);
}
void jsc_DataView_setInt32(jsc_object_t * object,jsc_int_t offset,jsc_int32_t value,jsc_boolean_t littleEndian) {
    if(object == NULL) {
        return;
    }
    jsc_DataView_setInt32_(object->isa,object,offset,value,littleEndian);
}
void jsc_DataView_setUint32(jsc_object_t * object,jsc_int_t offset,jsc_uint32_t value,jsc_boolean_t littleEndian) {
    if(object == NULL) {
        return;
    }
    jsc_DataView_setUint32_(object->isa,object,offset,value,littleEndian);
}
void jsc_DataView_setInt64(jsc_object_t * object,jsc_int_t offset,jsc_int64_t value,jsc_boolean_t littleEndian) {
    if(object == NULL) {
        return;
    }
    jsc_DataView_setInt64_(object->isa,object,offset,value,littleEndian);
}
void jsc_DataView_setUint64(jsc_object_t * object,jsc_int_t offset,jsc_uint64_t value,jsc_boolean_t littleEndian) {
    if(object == NULL) {
        return;
    }
    jsc_DataView_setUint64_(object->isa,object,offset,value,littleEndian);
}
void jsc_DataView_setFloat32(jsc_object_t * object,jsc_int_t offset,jsc_float32_t value,jsc_boolean_t littleEndian) {
    if(object == NULL) {
        return;
    }
    jsc_DataView_setFloat32_(object->isa,object,offset,value,littleEndian);
}
void jsc_DataView_setFloat64(jsc_object_t * object,jsc_int_t offset,jsc_float64_t value,jsc_boolean_t littleEndian) {
    if(object == NULL) {
        return;
    }
    jsc_DataView_setFloat64_(object->isa,object,offset,value,littleEndian);
}


/* alloc */
struct jsc_DataView_t * jsc_DataView_alloc(jsc_object_t * buffer,jsc_int_t offset,jsc_int_t length) {
    
    if(buffer == NULL || !jsc_class_isKind(buffer->isa, (jsc_class_t *)&jsc_ArrayBuffer)) {
        return NULL;
    }
    
    jsc_ArrayBuffer_t * buf = (jsc_ArrayBuffer_t *) buffer;
    
    jsc_int_t len = buf->_byteLength;
    
    if( offset < 0 ) {
        offset = len + offset;
    }
    
    if(length <= 0 || length > len - offset) {
        length = len - offset;
    }
    
    if(offset <0 || offset >= len || length <= 0) {
        return NULL;
    }

    jsc_DataView_t * v = (jsc_DataView_t *) jsc_object_alloc(&jsc_DataView.base, 0);
  
    jsc_setStrong((jsc_object_t **) &v->_buffer,buffer);
    
    v->_byteOffset = offset;
    v->_byteLength = length;
    
    return v;
}

struct jsc_DataView_t * jsc_DataView_new(jsc_object_t * buffer,jsc_int_t offset,jsc_int_t length) {
    jsc_DataView_t * v = jsc_DataView_alloc(buffer,offset,length);
    jsc_object_autorelease((jsc_object_t *) v);
    return v;
}

/* implemented */

static void _jsc_DataView_alloc(struct jsc_class_t * isa, struct jsc_object_t * object) {
    
}

static void _jsc_DataView_dealloc(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    jsc_setStrong((jsc_object_t **) &v->_buffer, NULL);
}

static jsc_object_t * _jsc_DataView_buffer(jsc_class_t * isa, jsc_object_t * object) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    return (jsc_object_t *) v->_buffer;
}

static jsc_int_t _jsc_DataView_byteOffset(jsc_class_t * isa, jsc_object_t * object) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    return v->_byteOffset;
}

static jsc_int_t _jsc_DataView_byteLength(jsc_class_t * isa, jsc_object_t * object) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    return v->_byteLength;
}

static jsc_int8_t _jsc_DataView_getInt8(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    if(1 > v->_byteLength) {
        return 0;
    }
    return (jsc_int8_t) v->_buffer->_data[v->_byteOffset + offset];
}

static jsc_uint8_t _jsc_DataView_getUint8(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    if(1 > v->_byteLength) {
        return 0;
    }
    return v->_buffer->_data[v->_byteOffset + offset];
}

static jsc_int16_t _jsc_DataView_getInt16(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    if(2 > v->_byteLength) {
        return 0;
    }
    jsc_int_t i = v->_byteOffset + offset;
    if(littleEndian) {
        return (jsc_int16_t) v->_buffer->_data[i] | (jsc_int16_t) v->_buffer->_data[i+1] << 8;
    } else {
        return (jsc_int16_t) v->_buffer->_data[i+1] | (jsc_int16_t) v->_buffer->_data[i] << 8;
    }
}

static jsc_uint16_t _jsc_DataView_getUint16(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    if(2 > v->_byteLength) {
        return 0;
    }
    jsc_int_t i = v->_byteOffset + offset;
    if(littleEndian) {
        return (jsc_uint16_t) v->_buffer->_data[i] | (jsc_uint16_t) v->_buffer->_data[i+1] << 8;
    } else {
        return (jsc_uint16_t) v->_buffer->_data[i+1] | (jsc_uint16_t) v->_buffer->_data[i] << 8;
    }
}
static jsc_int32_t _jsc_DataView_getInt32(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    if(4 > v->_byteLength) {
        return 0;
    }
    jsc_int_t i = v->_byteOffset + offset;
    if(littleEndian) {
        return (jsc_int32_t) v->_buffer->_data[i] | (jsc_int32_t) v->_buffer->_data[i+1] << 8
            | (jsc_int32_t) v->_buffer->_data[i+2] << 16 | (jsc_int32_t) v->_buffer->_data[i+3] << 24;
    } else {
        return (jsc_int32_t) v->_buffer->_data[i+3] | (jsc_int32_t) v->_buffer->_data[i+2] << 8
            | (jsc_int32_t) v->_buffer->_data[i+1] << 16 | (jsc_int32_t) v->_buffer->_data[i] << 24;
    }
}
static jsc_uint32_t _jsc_DataView_getUint32(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    if(4 > v->_byteLength) {
        return 0;
    }
    jsc_int_t i = v->_byteOffset + offset;
    if(littleEndian) {
        return (jsc_uint32_t) v->_buffer->_data[i] | (jsc_uint32_t) v->_buffer->_data[i+1] << 8
            | (jsc_uint32_t) v->_buffer->_data[i+2] << 16 | (jsc_uint32_t) v->_buffer->_data[i+3] << 24;
    } else {
        return (jsc_uint32_t) v->_buffer->_data[i+3] | (jsc_uint32_t) v->_buffer->_data[i+2] << 8
            | (jsc_uint32_t) v->_buffer->_data[i+1] << 16 | (jsc_uint32_t) v->_buffer->_data[i] << 24;
    }
}

static jsc_int64_t _jsc_DataView_getInt64(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    if(8 > v->_byteLength) {
        return 0;
    }
    jsc_int_t i = v->_byteOffset + offset;
    if(littleEndian) {
        return (jsc_int64_t) v->_buffer->_data[i] | (jsc_int64_t) v->_buffer->_data[i+1] << 8
            | (jsc_int64_t) v->_buffer->_data[i+2] << 16 | (jsc_int64_t) v->_buffer->_data[i+3] << 24
            | (jsc_int64_t) v->_buffer->_data[i+4] << 32 | (jsc_int64_t) v->_buffer->_data[i+5] << 40
            | (jsc_int64_t) v->_buffer->_data[i+6] << 48 | (jsc_int64_t) v->_buffer->_data[i+7] << 56;
    } else {
        return (jsc_int64_t) v->_buffer->_data[i + 7] | (jsc_int64_t) v->_buffer->_data[i+6] << 8
            | (jsc_int64_t) v->_buffer->_data[i+5] << 16 | (jsc_int64_t) v->_buffer->_data[i+4] << 24
            | (jsc_int64_t) v->_buffer->_data[i+3] << 32 | (jsc_int64_t) v->_buffer->_data[i+2] << 40
            | (jsc_int64_t) v->_buffer->_data[i+1] << 48 | (jsc_int64_t) v->_buffer->_data[i] << 56;
    }
}

static jsc_uint64_t _jsc_DataView_getUint64(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    if(8 > v->_byteLength) {
        return 0;
    }
    jsc_int_t i = v->_byteOffset + offset;
    if(littleEndian) {
        return (jsc_uint64_t) v->_buffer->_data[i] | (jsc_uint64_t) v->_buffer->_data[i+1] << 8
            | (jsc_uint64_t) v->_buffer->_data[i+2] << 16 | (jsc_uint64_t) v->_buffer->_data[i+3] << 24
            | (jsc_uint64_t) v->_buffer->_data[i+4] << 32 | (jsc_uint64_t) v->_buffer->_data[i+5] << 40
            | (jsc_uint64_t) v->_buffer->_data[i+6] << 48 | (jsc_uint64_t) v->_buffer->_data[i+7] << 56;
    } else {
        return (jsc_uint64_t) v->_buffer->_data[i + 7] | (jsc_uint64_t) v->_buffer->_data[i+6] << 8
            | (jsc_uint64_t) v->_buffer->_data[i+5] << 16 | (jsc_uint64_t) v->_buffer->_data[i+4] << 24
            | (jsc_uint64_t) v->_buffer->_data[i+3] << 32 | (jsc_uint64_t) v->_buffer->_data[i+2] << 40
            | (jsc_uint64_t) v->_buffer->_data[i+1] << 48 | (jsc_uint64_t) v->_buffer->_data[i] << 56;
    }
}

static jsc_float32_t _jsc_DataView_getFloat32(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    jsc_uint32_t v = _jsc_DataView_getUint32(isa,object,offset,littleEndian);
    return * (jsc_float32_t *) &v;
}

static jsc_float64_t _jsc_DataView_getFloat64(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian) {
    jsc_uint64_t v = _jsc_DataView_getUint64(isa,object,offset,littleEndian);
    return * (jsc_float64_t *) &v;
}

static jsc_string_t _jsc_DataView_getString(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    return (jsc_string_t) (v->_buffer->_data + v->_byteOffset + offset);
}

static jsc_object_t * _jsc_DataView_getData(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int_t length) {
    
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    
    if(v->_buffer == NULL || offset + length > v->_byteLength) {
        return NULL;
    }
    
    return (jsc_object_t *) jsc_DataView_new((jsc_object_t *) v->_buffer, v->_byteOffset + offset, length);
}

static void _jsc_DataView_setInt8(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int8_t value) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    if(1 + offset> v->_byteLength || v->_buffer == NULL) {
        return;
    }
    jsc_int_t i = v->_byteOffset + offset;
    v->_buffer->_data[i] = value;
}

static void _jsc_DataView_setUint8(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint8_t value) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    if(1 + offset> v->_byteLength || v->_buffer == NULL) {
        return;
    }
    jsc_int_t i = v->_byteOffset + offset;
    v->_buffer->_data[i] = value;
}

static void _jsc_DataView_setInt16(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int16_t value,jsc_boolean_t littleEndian) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    if(2 + offset> v->_byteLength || v->_buffer == NULL) {
        return;
    }
    jsc_int_t i = v->_byteOffset + offset;
    if(littleEndian) {
        v->_buffer->_data[i] = (jsc_ubyte_t)(value) ;
        v->_buffer->_data[i+1] = (jsc_ubyte_t)(value >> 8) ;
    } else {
        v->_buffer->_data[i+1] = (jsc_ubyte_t)(value) ;
        v->_buffer->_data[i] = (jsc_ubyte_t)(value >> 8) ;
    }
}
static void _jsc_DataView_setUint16(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint16_t value,jsc_boolean_t littleEndian) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    if(2 + offset > v->_byteLength || v->_buffer == NULL) {
        return;
    }
    jsc_int_t i = v->_byteOffset + offset;
    if(littleEndian) {
        v->_buffer->_data[i] = (jsc_ubyte_t)(value) ;
        v->_buffer->_data[i+1] = (jsc_ubyte_t)(value >> 8) ;
    } else {
        v->_buffer->_data[i+1] = (jsc_ubyte_t)(value) ;
        v->_buffer->_data[i] = (jsc_ubyte_t)(value >> 8) ;
    }
}
static void _jsc_DataView_setInt32(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int32_t value,jsc_boolean_t littleEndian) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    if(4 + offset > v->_byteLength || v->_buffer == NULL) {
        return;
    }
    jsc_int_t i = v->_byteOffset + offset;
    if(littleEndian) {
        v->_buffer->_data[i] = (jsc_ubyte_t)(value) ;
        v->_buffer->_data[i+1] = (jsc_ubyte_t)(value >> 8) ;
        v->_buffer->_data[i+2] = (jsc_ubyte_t)(value >> 16) ;
        v->_buffer->_data[i+3] = (jsc_ubyte_t)(value >> 24) ;
    } else {
        v->_buffer->_data[i+3] = (jsc_ubyte_t)(value) ;
        v->_buffer->_data[i+2] = (jsc_ubyte_t)(value >> 8) ;
        v->_buffer->_data[i+1] = (jsc_ubyte_t)(value >> 16) ;
        v->_buffer->_data[i] = (jsc_ubyte_t)(value >> 24) ;
    }
}
static void _jsc_DataView_setUint32(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint32_t value,jsc_boolean_t littleEndian) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    if(4 + offset > v->_byteLength || v->_buffer == NULL) {
        return;
    }
    jsc_int_t i = v->_byteOffset + offset;
    if(littleEndian) {
        v->_buffer->_data[i] = (jsc_ubyte_t)(value) ;
        v->_buffer->_data[i+1] = (jsc_ubyte_t)(value >> 8) ;
        v->_buffer->_data[i+2] = (jsc_ubyte_t)(value >> 16) ;
        v->_buffer->_data[i+3] = (jsc_ubyte_t)(value >> 24) ;
    } else {
        v->_buffer->_data[i+3] = (jsc_ubyte_t)(value) ;
        v->_buffer->_data[i+2] = (jsc_ubyte_t)(value >> 8) ;
        v->_buffer->_data[i+1] = (jsc_ubyte_t)(value >> 16) ;
        v->_buffer->_data[i] = (jsc_ubyte_t)(value >> 24) ;
    }
}
static void _jsc_DataView_setInt64(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int64_t value,jsc_boolean_t littleEndian) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    if(8 + offset > v->_byteLength || v->_buffer == NULL) {
        return;
    }
    jsc_int_t i = v->_byteOffset + offset;
    if(littleEndian) {
        v->_buffer->_data[i] = (jsc_ubyte_t)(value) ;
        v->_buffer->_data[i+1] = (jsc_ubyte_t)(value >> 8) ;
        v->_buffer->_data[i+2] = (jsc_ubyte_t)(value >> 16) ;
        v->_buffer->_data[i+3] = (jsc_ubyte_t)(value >> 24) ;
        v->_buffer->_data[i+4] = (jsc_ubyte_t)(value >> 32) ;
        v->_buffer->_data[i+5] = (jsc_ubyte_t)(value >> 40) ;
        v->_buffer->_data[i+6] = (jsc_ubyte_t)(value >> 48) ;
        v->_buffer->_data[i+7] = (jsc_ubyte_t)(value >> 56) ;
    } else {
        v->_buffer->_data[i+7] = (jsc_ubyte_t)(value) ;
        v->_buffer->_data[i+6] = (jsc_ubyte_t)(value >> 8) ;
        v->_buffer->_data[i+5] = (jsc_ubyte_t)(value >> 16) ;
        v->_buffer->_data[i+4] = (jsc_ubyte_t)(value >> 24) ;
        v->_buffer->_data[i+3] = (jsc_ubyte_t)(value >> 32) ;
        v->_buffer->_data[i+2] = (jsc_ubyte_t)(value >> 40) ;
        v->_buffer->_data[i+1] = (jsc_ubyte_t)(value >> 48) ;
        v->_buffer->_data[i] = (jsc_ubyte_t)(value >> 56) ;
    }
}

static void _jsc_DataView_setUint64(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint64_t value,jsc_boolean_t littleEndian) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    if(8 + offset > v->_byteLength || v->_buffer == NULL) {
        return;
    }
    jsc_int_t i = v->_byteOffset + offset;
    if(littleEndian) {
        v->_buffer->_data[i] = (jsc_ubyte_t)(value) ;
        v->_buffer->_data[i+1] = (jsc_ubyte_t)(value >> 8) ;
        v->_buffer->_data[i+2] = (jsc_ubyte_t)(value >> 16) ;
        v->_buffer->_data[i+3] = (jsc_ubyte_t)(value >> 24) ;
        v->_buffer->_data[i+4] = (jsc_ubyte_t)(value >> 32) ;
        v->_buffer->_data[i+5] = (jsc_ubyte_t)(value >> 40) ;
        v->_buffer->_data[i+6] = (jsc_ubyte_t)(value >> 48) ;
        v->_buffer->_data[i+7] = (jsc_ubyte_t)(value >> 56) ;
    } else {
        v->_buffer->_data[i+7] = (jsc_ubyte_t)(value) ;
        v->_buffer->_data[i+6] = (jsc_ubyte_t)(value >> 8) ;
        v->_buffer->_data[i+5] = (jsc_ubyte_t)(value >> 16) ;
        v->_buffer->_data[i+4] = (jsc_ubyte_t)(value >> 24) ;
        v->_buffer->_data[i+3] = (jsc_ubyte_t)(value >> 32) ;
        v->_buffer->_data[i+2] = (jsc_ubyte_t)(value >> 40) ;
        v->_buffer->_data[i+1] = (jsc_ubyte_t)(value >> 48) ;
        v->_buffer->_data[i] = (jsc_ubyte_t)(value >> 56) ;
    }
}

static void _jsc_DataView_setFloat32(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_float32_t value,jsc_boolean_t littleEndian) {
    _jsc_DataView_setUint32(isa,object,offset,* (jsc_uint32_t *) & value,littleEndian);
}

static void _jsc_DataView_setFloat64(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_float64_t value,jsc_boolean_t littleEndian) {
    _jsc_DataView_setUint64(isa,object,offset,* (jsc_uint64_t *) & value,littleEndian);
}

static jsc_int_t _jsc_DataView_setString(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_string_t value) {
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    jsc_int_t n = value ? (jsc_int_t) strlen(value) + 1: 1;
    if(n + offset > v->_byteLength || v->_buffer == NULL) {
        return -1;
    }
    if(value) {
        memcpy(v->_buffer->_data + v->_byteOffset + offset,value,n);
    } else {
        memset(v->_buffer->_data + v->_byteOffset + offset,0,n);
    }
    
    return n;
}

static jsc_int_t _jsc_DataView_setData(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_object_t * data) {
    
    jsc_DataView_t * v = (jsc_DataView_t *) object;
    
    if(v->_buffer == NULL || data == NULL || !jsc_class_isKind(data->isa, (jsc_class_t *) &jsc_DataView)) {
        return -1;
    }
    
    jsc_DataView_t * d = (jsc_DataView_t *) data;
    
    if(offset + d->_byteLength > v->_byteLength || d->_buffer == NULL) {
        return -1;
    }
    
    memcpy(v->_buffer->_data + v->_byteOffset + offset,d->_buffer->_data + d->_byteOffset,d->_byteLength);
    
    return d->_byteLength;
}

