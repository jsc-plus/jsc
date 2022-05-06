//
//  jsc_variant.c
//  jsc
//
//  Created by 张海龙 on 2022/1/14.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#include "jsc_type.h"
#include "jsc_class.h"
#include "jsc_variant.h"
#include "jsc_buffer.h"
#include "jsc_String.h"
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

jsc_float64_t jsc_variant_toFloat64(struct jsc_variant_t v) {
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
            return (jsc_float64_t) v.int64Value;
        case JSC_VARIANT_TYPE_UINT64:
            return (jsc_float64_t) v.uint64Value;
        case JSC_VARIANT_TYPE_FLOAT32:
            return (jsc_float64_t) v.float32Value;
        case JSC_VARIANT_TYPE_FLOAT64:
            return (jsc_float64_t) v.float64Value;
        case JSC_VARIANT_TYPE_STRING:
            return atof(v.stringValue);
        case JSC_VARIANT_TYPE_OBJECT:
            return jsc_object_toFloat64(v.objectValue);
    }
    return 0;
}

jsc_int64_t jsc_variant_toInt64(struct jsc_variant_t v) {
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
            return v.int64Value;
        case JSC_VARIANT_TYPE_UINT64:
            return (jsc_int64_t) v.uint64Value;
        case JSC_VARIANT_TYPE_FLOAT32:
            return (jsc_int64_t) v.float32Value;
        case JSC_VARIANT_TYPE_FLOAT64:
            return (jsc_int64_t) v.float64Value;
        case JSC_VARIANT_TYPE_STRING:
            return atoll(v.stringValue);
        case JSC_VARIANT_TYPE_OBJECT:
            return jsc_object_toInt64(v.objectValue);
    }
    return 0;
}

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
    } else if(at == JSC_VARIANT_TYPE_FLOAT64 || bt == JSC_VARIANT_TYPE_FLOAT64) {
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

struct jsc_variant_t jsc_variant_getStrong(struct jsc_variant_t v) {
    struct jsc_variant_t r = jsc_Nil;
    jsc_variant_setStrong(&r,v);
    return r;
}

