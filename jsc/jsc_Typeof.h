#ifndef jsc_Typeof_h
#define jsc_Typeof_h

#ifdef __cplusplus
extern "C" {
#endif

	jsc_boolean_t jsc_Typeof_isNil(jsc_variant_t v);
	jsc_boolean_t jsc_Typeof_isInt8(jsc_variant_t v);
	jsc_boolean_t jsc_Typeof_isUint8(jsc_variant_t v);
	jsc_boolean_t jsc_Typeof_isInt16(jsc_variant_t v);
	jsc_boolean_t jsc_Typeof_isUint16(jsc_variant_t v);
	jsc_boolean_t jsc_Typeof_isInt32(jsc_variant_t v);
	jsc_boolean_t jsc_Typeof_isUint32(jsc_variant_t v);
	jsc_boolean_t jsc_Typeof_isInt64(jsc_variant_t v);
	jsc_boolean_t jsc_Typeof_isUint64(jsc_variant_t v);
	jsc_boolean_t jsc_Typeof_isFloat32(jsc_variant_t v);
	jsc_boolean_t jsc_Typeof_isFloat64(jsc_variant_t v);
	jsc_boolean_t jsc_Typeof_isBoolean(jsc_variant_t v);
	jsc_boolean_t jsc_Typeof_isString(jsc_variant_t v);
	jsc_boolean_t jsc_Typeof_isUnichar(jsc_variant_t v);
	jsc_boolean_t jsc_Typeof_isObject(jsc_variant_t v);

#ifdef __cplusplus
}
#endif

#endif

