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

#define JSC_AS_INT_OBJECT(a) ((jsc_int_t) jsc_object_toInt64(a))
#define JSC_AS_UINT_OBJECT(a) ((jsc_uint_t) jsc_object_toInt64(a))
#define JSC_AS_LONG_OBJECT(a) ((jsc_long_t) jsc_object_toInt64(a))
#define JSC_AS_ULONG_OBJECT(a) ((jsc_ulong_t) jsc_object_toInt64(a))
#define JSC_AS_INT64_OBJECT(a) ((jsc_int64_t) jsc_object_toInt64(a))
#define JSC_AS_UINT64_OBJECT(a) ((jsc_uint64_t) jsc_object_toInt64(a))
#define JSC_AS_FLOAT64_OBJECT(a) ((jsc_float64_t) jsc_object_toFloat64(a))

#define JSC_STRING_ADD(a,b) ((jsc_object_t *) jsc_string_concat(a,b))
#define JSC_STRING_CMP(a,b) (jsc_string_compare(a,b))
#define JSC_AS_STRING_OBJECT(a) (jsc_String_CString((jsc_object_t *) jsc_object_toString((jsc_object_t *)(a))))
#define JSC_AS_STRING_INT(a) (jsc_String_CString((jsc_object_t *) jsc_String_newFormat("%d",(a))))
#define JSC_AS_STRING_UINT(a) (jsc_String_CString((jsc_object_t *) jsc_String_newFormat("%u",(a))))
#define JSC_AS_STRING_LONG(a) (jsc_String_CString((jsc_object_t *) jsc_String_newFormat("%ld",(a))))
#define JSC_AS_STRING_ULONG(a) (jsc_String_CString((jsc_object_t *) jsc_String_newFormat("%lu",(a))))
#define JSC_AS_STRING_INT64(a) (jsc_String_CString((jsc_object_t *) jsc_String_newFormat("%lld",(a))))
#define JSC_AS_STRING_UINT64(a) (jsc_String_CString((jsc_object_t *) jsc_String_newFormat("%llu",(a))))
#define JSC_AS_STRING_FLOAT32(a) (jsc_String_CString((jsc_object_t *) jsc_String_newFormat("%g",(a))))
#define JSC_AS_STRING_FLOAT64(a) (jsc_String_CString((jsc_object_t *) jsc_String_newFormat("%g",(a))))

#define JSC_AS_OBJECT_STRING(a) ((jsc_object_t *) jsc_String_newCString(a))

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* jsc_h */
