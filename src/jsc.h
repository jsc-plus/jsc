//
//  jsc.h
//  jsc
//
//  Created by 张海龙 on 2022/5/4.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#ifndef jsc_h
#define jsc_h

#include "jsc_type.h"
#include "jsc_class.h"
#include "jsc_variant.h"
#include "jsc_buffer.h"
#include "jsc_String.h"
#include "jsc_Number.h"
#include "jsc_Array.h"
#include "jsc_Map.h"
#include "jsc_Iterator.h"
#include "jsc_ArrayBuffer.h"
#include "jsc_DataView.h"
#include "jsc_fs.h"
#include "jsc_crypto.h"
#include "jsc_Typeof.h"
#include "jsc_Math.h"
#include "jsc_Closures.h"

#define JSC_AS_INT_OBJECT(a) ((jsc_int_t) jsc_object_toInt64(a))
#define JSC_AS_UINT_OBJECT(a) ((jsc_uint_t) jsc_object_toInt64(a))
#define JSC_AS_LONG_OBJECT(a) ((jsc_long_t) jsc_object_toInt64(a))
#define JSC_AS_ULONG_OBJECT(a) ((jsc_ulong_t) jsc_object_toInt64(a))
#define JSC_AS_INT64_OBJECT(a) ((jsc_int64_t) jsc_object_toInt64(a))
#define JSC_AS_UINT64_OBJECT(a) ((jsc_uint64_t) jsc_object_toInt64(a))
#define JSC_AS_FLOAT64_OBJECT(a) ((jsc_float64_t) jsc_object_toFloat64(a))

#define JSC_STRING_ADD(a,b) ((jsc_object_t *) jsc_string_concat(a,b))
#define JSC_STRING_COMP(a,b) jsc_string_compare(a,b)
#define JSC_AS_STRING_OBJECT(a) jsc_String_CString((jsc_object_t *) jsc_object_toString((jsc_object_t *)(a)))
#define JSC_AS_STRING_INT(a) jsc_String_CString((jsc_object_t *) jsc_String_newFormat("%d",(a)))
#define JSC_AS_STRING_UINT(a) jsc_String_CString((jsc_object_t *) jsc_String_newFormat("%u",(a)))
#define JSC_AS_STRING_LONG(a) jsc_String_CString((jsc_object_t *) jsc_String_newFormat("%ld",(a)))
#define JSC_AS_STRING_ULONG(a) jsc_String_CString((jsc_object_t *) jsc_String_newFormat("%lu",(a)))
#define JSC_AS_STRING_INT64(a) jsc_String_CString((jsc_object_t *) jsc_String_newFormat("%lld",(a)))
#define JSC_AS_STRING_UINT64(a) jsc_String_CString((jsc_object_t *) jsc_String_newFormat("%llu",(a)))
#define JSC_AS_STRING_FLOAT32(a) jsc_String_CString((jsc_object_t *) jsc_String_newFormat("%g",(a)))
#define JSC_AS_STRING_FLOAT64(a) jsc_String_CString((jsc_object_t *) jsc_String_newFormat("%g",(a)))
#define JSC_AS_STRING_VARIANT(a) jsc_variant_toCString(a)

#define JSC_AS_OBJECT_STRING(a) ((jsc_object_t *) jsc_String_newCString(a))

#define JSC_AS_INT8_INT(a) (jsc_int8_t)(a)
#define JSC_AS_UINT8_INT(a) (jsc_uint8_t)(a)
#define JSC_AS_INT16_INT(a) (jsc_int16_t)(a)
#define JSC_AS_UINT16_INT(a) (jsc_uint16_t)(a)
#define JSC_AS_INT32_INT(a) (jsc_int32_t)(a)
#define JSC_AS_UINT32_INT(a) (jsc_uint32_t)(a)
#define JSC_AS_INT64_INT(a) (jsc_int64_t)(a)
#define JSC_AS_UINT64_INT(a) (jsc_uint64_t)(a)
#define JSC_AS_FLOAT32_INT(a) (jsc_float32_t)(a)
#define JSC_AS_FLOAT64_INT(a) (jsc_float64_t)(a)
#define JSC_AS_OBJECT_NIL(a) (jsc_object_t *)(a)
#define JSC_AS_VARIANT_NIL(a) jsc_Nil

#define JSC_AS_FLOAT64_FLOAT32(a) (jsc_float64_t)(a)
#define JSC_AS_STRING_NIL(a) NULL

#define JSC_AS_INT_UINT32(a) (jsc_int_t)(a)
#define JSC_AS_INT_UINT8(a) (jsc_int_t)(a)
#define JSC_AS_INT_FLOAT64(a) (jsc_int_t)(a)

#define JSC_AS_VARIANT_INT8(a) jsc_variant_int8(a)
#define JSC_AS_VARIANT_UINT8(a) jsc_variant_uint8(a)
#define JSC_AS_VARIANT_INT16(a) jsc_variant_int16(a)
#define JSC_AS_VARIANT_UINT16(a) jsc_variant_uint16(a)
#define JSC_AS_VARIANT_INT32(a) jsc_variant_int32(a)
#define JSC_AS_VARIANT_UINT32(a) jsc_variant_uint32(a)
#define JSC_AS_VARIANT_INT64(a) jsc_variant_int64(a)
#define JSC_AS_VARIANT_UINT64(a) jsc_variant_uint64(a)
#define JSC_AS_VARIANT_FLOAT32(a) jsc_variant_float32(a)
#define JSC_AS_VARIANT_FLOAT64(a) jsc_variant_float64(a)
#define JSC_AS_VARIANT_BOOLEAN(a) jsc_variant_boolean(a)
#define JSC_AS_VARIANT_STRING(a) jsc_variant_CString(a)
#define JSC_AS_VARIANT_OBJECT(a) jsc_variant_Object(a)

#define JSC_AS_INT8_VARIANT(a) jsc_variant_toInt8(a)
#define JSC_AS_UINT8_VARIANT(a) jsc_variant_toUint8(a)
#define JSC_AS_INT16_VARIANT(a) jsc_variant_toInt16(a)
#define JSC_AS_UINT16_VARIANT(a) jsc_variant_toUint16(a)
#define JSC_AS_INT32_VARIANT(a) jsc_variant_toInt32(a)
#define JSC_AS_UINT32_VARIANT(a) jsc_variant_toUint32(a)
#define JSC_AS_INT64_VARIANT(a) jsc_variant_toInt64(a)
#define JSC_AS_UINT64_VARIANT(a) jsc_variant_toUint64(a)
#define JSC_AS_FLOAT32_VARIANT(a) jsc_variant_toFloat32(a)
#define JSC_AS_FLOAT64_VARIANT(a) jsc_variant_toFloat64(a)
#define JSC_AS_BOOLEAN_VARIANT(a) jsc_variant_toBoolean(a)
#define JSC_AS_OBJECT_VARIANT(a) jsc_variant_toObject(a)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* jsc_h */
