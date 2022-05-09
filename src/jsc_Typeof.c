#include "jsc_type.h"
#include "jsc_class.h"
#include "jsc_String.h"
#include "jsc_variant.h"
#include "jsc_buffer.h"
#include "jsc_Typeof.h"
#include "jsc_Typeof.inc"

/* class implemented */

/* function implemented */
jsc_boolean_t jsc_Typeof_isNil(jsc_variant_t v) {
	return v.type == JSC_VARIANT_TYPE_INT;
}
jsc_boolean_t jsc_Typeof_isInt8(jsc_variant_t v) {
    return v.type == JSC_VARIANT_TYPE_INT8;
}
jsc_boolean_t jsc_Typeof_isUint8(jsc_variant_t v) {
    return v.type == JSC_VARIANT_TYPE_UINT8;
}
jsc_boolean_t jsc_Typeof_isInt16(jsc_variant_t v) {
    return v.type == JSC_VARIANT_TYPE_INT16;
}
jsc_boolean_t jsc_Typeof_isUint16(jsc_variant_t v) {
    return v.type == JSC_VARIANT_TYPE_UINT16;
}
jsc_boolean_t jsc_Typeof_isInt32(jsc_variant_t v) {
    return v.type == JSC_VARIANT_TYPE_INT32;
}
jsc_boolean_t jsc_Typeof_isUint32(jsc_variant_t v) {
    return v.type == JSC_VARIANT_TYPE_UINT32;
}
jsc_boolean_t jsc_Typeof_isInt64(jsc_variant_t v) {
    return v.type == JSC_VARIANT_TYPE_INT64;
}
jsc_boolean_t jsc_Typeof_isUint64(jsc_variant_t v) {
    return v.type == JSC_VARIANT_TYPE_UINT64;
}
jsc_boolean_t jsc_Typeof_isFloat32(jsc_variant_t v) {
    return v.type == JSC_VARIANT_TYPE_FLOAT32;
}
jsc_boolean_t jsc_Typeof_isFloat64(jsc_variant_t v) {
    return v.type == JSC_VARIANT_TYPE_FLOAT64;
}
jsc_boolean_t jsc_Typeof_isBoolean(jsc_variant_t v) {
    return v.type == JSC_VARIANT_TYPE_BOOLEAN;
}
jsc_boolean_t jsc_Typeof_isString(jsc_variant_t v) {
    return v.type == JSC_VARIANT_TYPE_STRING;
}
jsc_boolean_t jsc_Typeof_isUnichar(jsc_variant_t v) {
    return v.type == JSC_VARIANT_TYPE_UNICHAR;
}
jsc_boolean_t jsc_Typeof_isObject(jsc_variant_t v) {
    return v.type == JSC_VARIANT_TYPE_OBJECT;
}
