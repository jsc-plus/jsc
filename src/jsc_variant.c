//
//  jsc_variant.c
//  jsc
//
//  Created by 张海龙 on 2022/1/14.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#include "jsc_type.h"
#include "jsc_class.h"
#include "jsc_buffer.h"
#include "jsc_String.h"
#include "jsc_variant.h"
#include "jsc_Number.h"
#include <zlib.h>

jsc_variant_t const jsc_Nil = {JSC_VARIANT_TYPE_NIL,0,0};


jsc_string_t jsc_variant_toCStringWithBuffer(struct jsc_variant_t v,struct jsc_buffer_t * buf) {
    switch (v.type) {
        case JSC_VARIANT_TYPE_NIL:
            return NULL;
        case JSC_VARIANT_TYPE_INT8:
            return jsc_buffer_format(buf,"%d", v.int8Value);
        case JSC_VARIANT_TYPE_UINT8:
            return jsc_buffer_format(buf,"%u", v.uint8Value);
        case JSC_VARIANT_TYPE_INT16:
            return jsc_buffer_format(buf,"%d", v.int16Value);
        case JSC_VARIANT_TYPE_UINT16:
            return jsc_buffer_format(buf,"%u", v.uint16Value);
        case JSC_VARIANT_TYPE_INT32:
            return jsc_buffer_format(buf,"%d", v.int32Value);
        case JSC_VARIANT_TYPE_UINT32:
            return jsc_buffer_format(buf,"%d", v.uint32Value);
        case JSC_VARIANT_TYPE_INT64:
            return jsc_buffer_format(buf,"%lld", v.int64Value);
        case JSC_VARIANT_TYPE_UINT64:
            return jsc_buffer_format(buf,"%llu", v.uint64Value);
        case JSC_VARIANT_TYPE_INT:
            return jsc_buffer_format(buf,"%d", v.intValue);
        case JSC_VARIANT_TYPE_UINT:
            return jsc_buffer_format(buf,"%u", v.uintValue);
        case JSC_VARIANT_TYPE_LONG:
            return jsc_buffer_format(buf,"%ld", v.longValue);
        case JSC_VARIANT_TYPE_ULONG:
            return jsc_buffer_format(buf,"%lu", v.ulongValue);
        case JSC_VARIANT_TYPE_FLOAT32:
            return jsc_buffer_format(buf,"%g", v.float32Value);
        case JSC_VARIANT_TYPE_FLOAT64:
            return jsc_buffer_format(buf,"%g", v.float64Value);
        case JSC_VARIANT_TYPE_BOOLEAN:
            return jsc_buffer_format(buf,"%s", v.booleanValue ? "true":"false");
        case JSC_VARIANT_TYPE_UNICHAR:
            return jsc_buffer_format(buf,"0x%04X", v.unicharValue);
        case JSC_VARIANT_TYPE_STRING:
            return jsc_buffer_format(buf,"%s", v.stringValue);
        case JSC_VARIANT_TYPE_OBJECT:
        {
            jsc_String_t * s = jsc_object_toString(v.objectValue);
            if(s != NULL) {
                return jsc_buffer_format(buf,"%s",jsc_String_CString((jsc_object_t *) s));
            }
        }
    }
    return NULL;
}

jsc_string_t jsc_variant_toCString(struct jsc_variant_t v) {
    switch (v.type) {
        case JSC_VARIANT_TYPE_NIL:
            return NULL;
        case JSC_VARIANT_TYPE_INT8:
            if(v.objectValue) {
                char s[64];
                snprintf(s,sizeof(s),"%d",v.int8Value);
                v.objectValue = (jsc_object_t *) jsc_String_newCString(s);
            }
            return jsc_String_CString(v.objectValue);
        case JSC_VARIANT_TYPE_UINT8:
            if(v.objectValue) {
                char s[64];
                snprintf(s,sizeof(s),"%u",v.uint8Value);
                v.objectValue = (jsc_object_t *) jsc_String_newCString(s);
            }
            return jsc_String_CString(v.objectValue);
        case JSC_VARIANT_TYPE_INT16:
            if(v.objectValue) {
                char s[64];
                snprintf(s,sizeof(s),"%d",v.int16Value);
                v.objectValue = (jsc_object_t *) jsc_String_newCString(s);
            }
            return jsc_String_CString(v.objectValue);
        case JSC_VARIANT_TYPE_UINT16:
            if(v.objectValue) {
                char s[64];
                snprintf(s,sizeof(s),"%u",v.uint16Value);
                v.objectValue = (jsc_object_t *) jsc_String_newCString(s);
            }
            return jsc_String_CString(v.objectValue);
        case JSC_VARIANT_TYPE_INT32:
            if(v.objectValue) {
                char s[64];
                snprintf(s,sizeof(s),"%d",v.int32Value);
                v.objectValue = (jsc_object_t *) jsc_String_newCString(s);
            }
            return jsc_String_CString(v.objectValue);
        case JSC_VARIANT_TYPE_UINT32:
            if(v.objectValue) {
                char s[64];
                snprintf(s,sizeof(s),"%u",v.uint32Value);
                v.objectValue = (jsc_object_t *) jsc_String_newCString(s);
            }
            return jsc_String_CString(v.objectValue);
        case JSC_VARIANT_TYPE_INT64:
            if(v.objectValue) {
                char s[64];
                snprintf(s,sizeof(s),"%lld",v.int64Value);
                v.objectValue = (jsc_object_t *) jsc_String_newCString(s);
            }
            return jsc_String_CString(v.objectValue);
        case JSC_VARIANT_TYPE_UINT64:
            if(v.objectValue) {
                char s[64];
                snprintf(s,sizeof(s),"%llu",v.uint64Value);
                v.objectValue = (jsc_object_t *) jsc_String_newCString(s);
            }
            return jsc_String_CString(v.objectValue);
        case JSC_VARIANT_TYPE_INT:
            if(v.objectValue) {
                char s[64];
                snprintf(s,sizeof(s),"%d",v.intValue);
                v.objectValue = (jsc_object_t *) jsc_String_newCString(s);
            }
            return jsc_String_CString(v.objectValue);
        case JSC_VARIANT_TYPE_UINT:
            if(v.objectValue) {
                char s[64];
                snprintf(s,sizeof(s),"%u",v.uintValue);
                v.objectValue = (jsc_object_t *) jsc_String_newCString(s);
            }
            return jsc_String_CString(v.objectValue);
        case JSC_VARIANT_TYPE_LONG:
            if(v.objectValue) {
                char s[64];
                snprintf(s,sizeof(s),"%ld",v.longValue);
                v.objectValue = (jsc_object_t *) jsc_String_newCString(s);
            }
            return jsc_String_CString(v.objectValue);
        case JSC_VARIANT_TYPE_ULONG:
            if(v.objectValue) {
                char s[64];
                snprintf(s,sizeof(s),"%lu",v.ulongValue);
                v.objectValue = (jsc_object_t *) jsc_String_newCString(s);
            }
            return jsc_String_CString(v.objectValue);
        case JSC_VARIANT_TYPE_FLOAT32:
            if(v.objectValue) {
                char s[64];
                snprintf(s,sizeof(s),"%g",v.float32Value);
                v.objectValue = (jsc_object_t *) jsc_String_newCString(s);
            }
            return jsc_String_CString(v.objectValue);
        case JSC_VARIANT_TYPE_FLOAT64:
            if(v.objectValue) {
                char s[64];
                snprintf(s,sizeof(s),"%g",v.float64Value);
                v.objectValue = (jsc_object_t *) jsc_String_newCString(s);
            }
            return jsc_String_CString(v.objectValue);
        case JSC_VARIANT_TYPE_BOOLEAN:
            if(v.objectValue) {
                v.objectValue = (jsc_object_t *) jsc_String_newCString(v.booleanValue ? "true":"false");
            }
            return jsc_String_CString(v.objectValue);
        case JSC_VARIANT_TYPE_UNICHAR:
            if(v.objectValue) {
                char s[64];
                snprintf(s,sizeof(s),"0x%04X",v.unicharValue);
                v.objectValue = (jsc_object_t *) jsc_String_newCString(s);
            }
            return jsc_String_CString(v.objectValue);
        case JSC_VARIANT_TYPE_STRING:
            return v.stringValue;
        case JSC_VARIANT_TYPE_OBJECT:
        {
            jsc_String_t * s = jsc_object_toString(v.objectValue);
            if(s != NULL) {
                return jsc_String_CString((jsc_object_t *) s);
            }
        }
    }
    return NULL;
}

#define IMP_TYPE_TO(FUNC,TYPE,ATOT,OT) \
TYPE jsc_variant_##FUNC(struct jsc_variant_t v) {\
    switch (v.type) {\
        case JSC_VARIANT_TYPE_NIL:\
            return 0;\
        case JSC_VARIANT_TYPE_INT8:\
            return (TYPE) v.int8Value;\
        case JSC_VARIANT_TYPE_UINT8:\
            return (TYPE) v.uint8Value;\
        case JSC_VARIANT_TYPE_INT16:\
            return (TYPE) v.int16Value;\
        case JSC_VARIANT_TYPE_UINT16:\
            return (TYPE) v.uint16Value;\
        case JSC_VARIANT_TYPE_INT32:\
            return (TYPE) v.int32Value;\
        case JSC_VARIANT_TYPE_UINT32:\
            return (TYPE) v.uint32Value;\
        case JSC_VARIANT_TYPE_INT:\
            return (TYPE) v.intValue;\
        case JSC_VARIANT_TYPE_UINT:\
            return (TYPE) v.uintValue;\
        case JSC_VARIANT_TYPE_LONG:\
            return (TYPE) v.longValue;\
        case JSC_VARIANT_TYPE_ULONG:\
            return (TYPE) v.ulongValue;\
        case JSC_VARIANT_TYPE_BOOLEAN:\
            return (TYPE) v.booleanValue;\
        case JSC_VARIANT_TYPE_UNICHAR:\
            return (TYPE) v.unicharValue;\
        case JSC_VARIANT_TYPE_INT64:\
            return (TYPE) v.int64Value;\
        case JSC_VARIANT_TYPE_UINT64:\
            return (TYPE) v.uint64Value;\
        case JSC_VARIANT_TYPE_FLOAT32:\
            return (TYPE) v.float32Value;\
        case JSC_VARIANT_TYPE_FLOAT64:\
            return (TYPE) v.float64Value;\
        case JSC_VARIANT_TYPE_STRING:\
            return (TYPE) ATOT(v.stringValue);\
        case JSC_VARIANT_TYPE_OBJECT:\
            return (TYPE) jsc_object_##OT(v.objectValue);\
    }\
    return 0;\
}

IMP_TYPE_TO(toInt8,jsc_int8_t,atoi,toInt64)
IMP_TYPE_TO(toUint8,jsc_uint8_t,atoi,toInt64)
IMP_TYPE_TO(toInt16,jsc_int16_t,atoi,toInt64)
IMP_TYPE_TO(toUint16,jsc_uint16_t,atoi,toInt64)
IMP_TYPE_TO(toInt32,jsc_int32_t,atoi,toInt64)
IMP_TYPE_TO(toUint32,jsc_uint32_t,atoi,toInt64)
IMP_TYPE_TO(toInt64,jsc_int64_t,atoll,toInt64)
IMP_TYPE_TO(toUint64,jsc_uint64_t,atoll,toInt64)
IMP_TYPE_TO(toFloat32,jsc_float32_t,atof,toFloat64)
IMP_TYPE_TO(toFloat64,jsc_float64_t,atof,toFloat64)


jsc_boolean_t jsc_variant_toBoolean(struct jsc_variant_t v) {
    switch (v.type) {
        case JSC_VARIANT_TYPE_NIL:
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
            return v.int64Value ? 1 : 0;
        case JSC_VARIANT_TYPE_UINT64:
            return v.uint64Value ? 1 : 0;
        case JSC_VARIANT_TYPE_FLOAT32:
            return v.float32Value ? 1 : 0;
        case JSC_VARIANT_TYPE_FLOAT64:
            return v.float64Value ? 1 : 0;
        case JSC_VARIANT_TYPE_STRING:
            return v.stringValue && * v.stringValue != 0 ? 1 : 0;
        case JSC_VARIANT_TYPE_OBJECT:
            return jsc_object_toBoolean(v.objectValue);
    }
    return 0;
}

inline static jsc_variant_type_t getCompareType(const struct jsc_variant_t * v) {
    switch (v->type) {
        case JSC_VARIANT_TYPE_NIL:
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
            return JSC_VARIANT_TYPE_INT64;
        case JSC_VARIANT_TYPE_FLOAT32:
        case JSC_VARIANT_TYPE_FLOAT64:
            return JSC_VARIANT_TYPE_FLOAT64;
        case JSC_VARIANT_TYPE_STRING:
            return JSC_VARIANT_TYPE_STRING;
        case JSC_VARIANT_TYPE_OBJECT:
            return JSC_VARIANT_TYPE_OBJECT;
    }
    return JSC_VARIANT_TYPE_INT64;
}

jsc_long_t jsc_variant_compare(struct jsc_variant_t a,struct jsc_variant_t b) {
    jsc_variant_type_t at = getCompareType(&a);
    jsc_variant_type_t bt = getCompareType(&b);
    if(at == JSC_VARIANT_TYPE_OBJECT || bt == JSC_VARIANT_TYPE_OBJECT) {
        return jsc_object_compare(jsc_variant_toObject(a), jsc_variant_toObject(b));
    } else if(a.type == JSC_VARIANT_TYPE_STRING && b.type == JSC_VARIANT_TYPE_STRING){
        return jsc_string_compare(a.stringValue,b.stringValue);
    } else if(at == JSC_VARIANT_TYPE_STRING || bt == JSC_VARIANT_TYPE_STRING) {
        jsc_buffer_t buf;
        jsc_buffer_init(&buf);
        jsc_string_t as = jsc_variant_toCStringWithBuffer(a, &buf);
        buf.length ++;
        jsc_string_t bs = jsc_variant_toCStringWithBuffer(b, &buf);
        buf.length ++;
        jsc_long_t r = jsc_string_compare(as,bs);
        jsc_buffer_destory(&buf);
        return r;
    } else if(at == JSC_VARIANT_TYPE_FLOAT64 || bt == JSC_VARIANT_TYPE_FLOAT64
              || at == JSC_VARIANT_TYPE_FLOAT32 || bt == JSC_VARIANT_TYPE_FLOAT32) {
        jsc_float64_t r = jsc_variant_toFloat64(a) - jsc_variant_toFloat64(b);
        if(r == 0.0) {
            return 0;
        } else if(r < 0.0) {
            return -1;
        } else {
            return 1;
        }
    } else {
        jsc_int64_t r = (jsc_variant_toInt64(a) - jsc_variant_toInt64(b));
        if(r == 0) {
            return 0;
        } else if(r < 0) {
            return -1;
        } else {
            return 1;
        }
    }
}


jsc_ulong_t jsc_variant_hashCode(struct jsc_variant_t v) {
    switch (v.type) {
        case JSC_VARIANT_TYPE_NIL:
            return 0;
        case JSC_VARIANT_TYPE_INT8:
        case JSC_VARIANT_TYPE_UINT8:
        case JSC_VARIANT_TYPE_INT16:
        case JSC_VARIANT_TYPE_UINT16:
        case JSC_VARIANT_TYPE_INT32:
        case JSC_VARIANT_TYPE_UINT32:
        case JSC_VARIANT_TYPE_INT64:
        case JSC_VARIANT_TYPE_UINT64:
        case JSC_VARIANT_TYPE_INT:
        case JSC_VARIANT_TYPE_UINT:
        case JSC_VARIANT_TYPE_LONG:
        case JSC_VARIANT_TYPE_ULONG:
        case JSC_VARIANT_TYPE_FLOAT32:
        case JSC_VARIANT_TYPE_FLOAT64:
        case JSC_VARIANT_TYPE_BOOLEAN:
        case JSC_VARIANT_TYPE_UNICHAR:
            return (jsc_ulong_t) v.uint64Value;
        case JSC_VARIANT_TYPE_STRING:
            return (jsc_ulong_t) crc32(0, (jsc_ubyte_t *) v.stringValue, (uInt) strlen(v.stringValue));
        case JSC_VARIANT_TYPE_OBJECT:
            return jsc_object_hashCode(v.objectValue);
    }
    return 0;
}

struct jsc_object_t * jsc_variant_toObject(struct jsc_variant_t v) {
    switch (v.type) {
        case JSC_VARIANT_TYPE_NIL:
        case JSC_VARIANT_TYPE_INT8:
        case JSC_VARIANT_TYPE_UINT8:
        case JSC_VARIANT_TYPE_INT16:
        case JSC_VARIANT_TYPE_UINT16:
        case JSC_VARIANT_TYPE_INT32:
        case JSC_VARIANT_TYPE_UINT32:
        case JSC_VARIANT_TYPE_INT64:
        case JSC_VARIANT_TYPE_UINT64:
        case JSC_VARIANT_TYPE_INT:
        case JSC_VARIANT_TYPE_UINT:
        case JSC_VARIANT_TYPE_LONG:
        case JSC_VARIANT_TYPE_ULONG:
        case JSC_VARIANT_TYPE_FLOAT32:
        case JSC_VARIANT_TYPE_FLOAT64:
        case JSC_VARIANT_TYPE_BOOLEAN:
        case JSC_VARIANT_TYPE_UNICHAR:
            if(v.objectValue == NULL) {
                v.objectValue = (jsc_object_t *) jsc_Number_new(v);
            }
            return v.objectValue;
        case JSC_VARIANT_TYPE_STRING:
            if(v.objectValue == NULL) {
                v.objectValue = (jsc_object_t *) jsc_String_newConstCString(v.stringValue);
            }
            return v.objectValue;
        case JSC_VARIANT_TYPE_OBJECT:
            return v.objectValue;
    }
    return NULL;
}

void jsc_variant_setStrong(struct jsc_variant_t * a,struct jsc_variant_t v) {
    a->type = v.type;
    a->uint64Value = v.uint64Value;
    jsc_setStrong(&a->objectValue, v.objectValue);
}

void jsc_variant_setWeak(struct jsc_variant_t * a,struct jsc_variant_t v) {
    a->type = v.type;
    a->uint64Value = v.uint64Value;
    jsc_setWeak(&a->objectValue, v.objectValue);
}

struct jsc_variant_t jsc_variant_getStrong(struct jsc_variant_t v) {
    struct jsc_variant_t r = jsc_Nil;
    jsc_variant_setStrong(&r,v);
    return r;
}


jsc_long_t jsc_variant_strict_compare(struct jsc_variant_t a, struct jsc_variant_t b) {
    jsc_long_t r = a.type - b.type;
    if(r == 0) {
        return jsc_variant_compare(a,b);
    }
    return r;
}

jsc_variant_t jsc_variant_add(struct jsc_variant_t a, struct jsc_variant_t b) {
    if(a.type == JSC_VARIANT_TYPE_STRING || b.type == JSC_VARIANT_TYPE_STRING) {
        jsc_String_t * s = jsc_string_concat(jsc_variant_toCString(a),jsc_variant_toCString(b));
        struct jsc_variant_t r = jsc_Nil;
        r.type = JSC_VARIANT_TYPE_STRING;
        r.stringValue = jsc_String_CString((jsc_object_t *) s);
        r.objectValue = (jsc_object_t *) s;
        return r;
    } else if(a.type == JSC_VARIANT_TYPE_FLOAT32 || a.type == JSC_VARIANT_TYPE_FLOAT32
              || a.type == JSC_VARIANT_TYPE_FLOAT64 || a.type == JSC_VARIANT_TYPE_FLOAT64) {
        return jsc_variant_float64(jsc_variant_toFloat64(a) + jsc_variant_toFloat64(b));
    } else {
        return jsc_variant_int64(jsc_variant_toInt64(a) + jsc_variant_toInt64(b));
    }
}

jsc_variant_t jsc_variant_sub(struct jsc_variant_t a, struct jsc_variant_t b) {
    if(a.type == JSC_VARIANT_TYPE_FLOAT32 || a.type == JSC_VARIANT_TYPE_FLOAT32
              || a.type == JSC_VARIANT_TYPE_FLOAT64 || a.type == JSC_VARIANT_TYPE_FLOAT64) {
        return jsc_variant_float64(jsc_variant_toFloat64(a) - jsc_variant_toFloat64(b));
    } else {
        return jsc_variant_int64(jsc_variant_toInt64(a) - jsc_variant_toInt64(b));
    }
}

jsc_variant_t jsc_variant_mul(struct jsc_variant_t a, struct jsc_variant_t b) {
    if(a.type == JSC_VARIANT_TYPE_FLOAT32 || a.type == JSC_VARIANT_TYPE_FLOAT32
              || a.type == JSC_VARIANT_TYPE_FLOAT64 || a.type == JSC_VARIANT_TYPE_FLOAT64) {
        return jsc_variant_float64(jsc_variant_toFloat64(a) * jsc_variant_toFloat64(b));
    } else {
        return jsc_variant_int64(jsc_variant_toInt64(a) * jsc_variant_toInt64(b));
    }
}

jsc_variant_t jsc_variant_div(struct jsc_variant_t a, struct jsc_variant_t b) {
    if(a.type == JSC_VARIANT_TYPE_FLOAT32 || a.type == JSC_VARIANT_TYPE_FLOAT32
              || a.type == JSC_VARIANT_TYPE_FLOAT64 || a.type == JSC_VARIANT_TYPE_FLOAT64) {
        return jsc_variant_float64(jsc_variant_toFloat64(a) / jsc_variant_toFloat64(b));
    } else {
        return jsc_variant_int64(jsc_variant_toInt64(a) / jsc_variant_toInt64(b));
    }
}

jsc_variant_t jsc_variant_mod(struct jsc_variant_t a, struct jsc_variant_t b) {
    return jsc_variant_int64(jsc_variant_toInt64(a) % jsc_variant_toInt64(b));
}

jsc_variant_t jsc_variant_bit_and(struct jsc_variant_t a, struct jsc_variant_t b) {
    return jsc_variant_int64(jsc_variant_toInt64(a) & jsc_variant_toInt64(b));
}

jsc_variant_t jsc_variant_bit_or(struct jsc_variant_t a, struct jsc_variant_t b) {
    return jsc_variant_int64(jsc_variant_toInt64(a) | jsc_variant_toInt64(b));
}

jsc_variant_t jsc_variant_bit_xor(struct jsc_variant_t a, struct jsc_variant_t b) {
    return jsc_variant_int64(jsc_variant_toInt64(a) ^ jsc_variant_toInt64(b));
}

jsc_variant_t jsc_variant_bit_opp(struct jsc_variant_t a) {
    return jsc_variant_int64(~jsc_variant_toInt64(a));
}

