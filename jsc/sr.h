#ifndef jsc_sr_h
#define jsc_sr_h

#ifdef __cplusplus
extern "C" {
#endif

	enum {
		jsc_Type_NIL,
		jsc_Type_INT8,
		jsc_Type_UINT8,
		jsc_Type_INT16,
		jsc_Type_UINT16,
		jsc_Type_INT32,
		jsc_Type_UINT32,
		jsc_Type_FLOAT32,
		jsc_Type_FLOAT64,
		jsc_Type_BOOLEAN,
		jsc_Type_STRING,
		jsc_Type_BYTES,
		jsc_Type_OBJECT,
		jsc_Type_ARRAY,
		jsc_Type_END,
	};
	enum {
		jsc_Error_NONE,
		jsc_Error_EOF,
		jsc_Error_STREAM,
	};
	typedef void (*jsc_sr_ChunkReadStream___init_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * data);
	typedef jsc_uint8_t (*jsc_sr_ChunkReadStream_err_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_boolean_t (*jsc_sr_ChunkReadStream_valid_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_int_t n);
	typedef jsc_int8_t (*jsc_sr_ChunkReadStream_getInt8_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_uint8_t (*jsc_sr_ChunkReadStream_getUint8_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_int16_t (*jsc_sr_ChunkReadStream_getInt16_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_uint16_t (*jsc_sr_ChunkReadStream_getUint16_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_int32_t (*jsc_sr_ChunkReadStream_getInt32_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_uint32_t (*jsc_sr_ChunkReadStream_getUint32_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_float32_t (*jsc_sr_ChunkReadStream_getFloat32_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_float64_t (*jsc_sr_ChunkReadStream_getFloat64_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_string_t (*jsc_sr_ChunkReadStream_getString_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_boolean_t (*jsc_sr_ChunkReadStream_getBoolean_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_object_t * (*jsc_sr_ChunkReadStream_getBytes_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_variant_t (*jsc_sr_ChunkReadStream_getValue_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_object_t * (*jsc_sr_ChunkReadStream_getObject_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_object_t * (*jsc_sr_ChunkReadStream_getArray_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_variant_t (*jsc_sr_ChunkReadStream_getValueWithType_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_uint8_t type);
	typedef void (*jsc_sr_ChunkReadStream_seekInt8_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef void (*jsc_sr_ChunkReadStream_seekUint8_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef void (*jsc_sr_ChunkReadStream_seekInt16_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef void (*jsc_sr_ChunkReadStream_seekUint16_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef void (*jsc_sr_ChunkReadStream_seekInt32_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef void (*jsc_sr_ChunkReadStream_seekUint32_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef void (*jsc_sr_ChunkReadStream_seekFloat32_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef void (*jsc_sr_ChunkReadStream_seekFloat64_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef void (*jsc_sr_ChunkReadStream_seekString_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef void (*jsc_sr_ChunkReadStream_seekBoolean_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef void (*jsc_sr_ChunkReadStream_seekBytes_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef void (*jsc_sr_ChunkReadStream_seekValue_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef void (*jsc_sr_ChunkReadStream_seekObject_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef void (*jsc_sr_ChunkReadStream_seekArray_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef void (*jsc_sr_ChunkReadStream_seekValueWithType_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_uint8_t type);
	typedef jsc_int_t (*jsc_sr_ChunkReadStream_offset_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef void (*jsc_sr_ChunkReadStream_setOffset_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_int_t off);
	typedef struct jsc_sr_ChunkReadStream_class_t {
		jsc_class_t base;
		jsc_sr_ChunkReadStream___init_t __init;
		jsc_sr_ChunkReadStream_err_t err;
		jsc_sr_ChunkReadStream_valid_t valid;
		jsc_sr_ChunkReadStream_getInt8_t getInt8;
		jsc_sr_ChunkReadStream_getUint8_t getUint8;
		jsc_sr_ChunkReadStream_getInt16_t getInt16;
		jsc_sr_ChunkReadStream_getUint16_t getUint16;
		jsc_sr_ChunkReadStream_getInt32_t getInt32;
		jsc_sr_ChunkReadStream_getUint32_t getUint32;
		jsc_sr_ChunkReadStream_getFloat32_t getFloat32;
		jsc_sr_ChunkReadStream_getFloat64_t getFloat64;
		jsc_sr_ChunkReadStream_getString_t getString;
		jsc_sr_ChunkReadStream_getBoolean_t getBoolean;
		jsc_sr_ChunkReadStream_getBytes_t getBytes;
		jsc_sr_ChunkReadStream_getValue_t getValue;
		jsc_sr_ChunkReadStream_getObject_t getObject;
		jsc_sr_ChunkReadStream_getArray_t getArray;
		jsc_sr_ChunkReadStream_getValueWithType_t getValueWithType;
		jsc_sr_ChunkReadStream_seekInt8_t seekInt8;
		jsc_sr_ChunkReadStream_seekUint8_t seekUint8;
		jsc_sr_ChunkReadStream_seekInt16_t seekInt16;
		jsc_sr_ChunkReadStream_seekUint16_t seekUint16;
		jsc_sr_ChunkReadStream_seekInt32_t seekInt32;
		jsc_sr_ChunkReadStream_seekUint32_t seekUint32;
		jsc_sr_ChunkReadStream_seekFloat32_t seekFloat32;
		jsc_sr_ChunkReadStream_seekFloat64_t seekFloat64;
		jsc_sr_ChunkReadStream_seekString_t seekString;
		jsc_sr_ChunkReadStream_seekBoolean_t seekBoolean;
		jsc_sr_ChunkReadStream_seekBytes_t seekBytes;
		jsc_sr_ChunkReadStream_seekValue_t seekValue;
		jsc_sr_ChunkReadStream_seekObject_t seekObject;
		jsc_sr_ChunkReadStream_seekArray_t seekArray;
		jsc_sr_ChunkReadStream_seekValueWithType_t seekValueWithType;
		jsc_sr_ChunkReadStream_offset_t offset;
		jsc_sr_ChunkReadStream_setOffset_t setOffset;
	} jsc_sr_ChunkReadStream_class_t;
	extern jsc_sr_ChunkReadStream_class_t jsc_sr_ChunkReadStream;

	typedef struct sr_ChunkReadStream_t {
		jsc_object_t base;
		jsc_object_t * _data;
		jsc_int_t _index;
		jsc_uint8_t _err;
	} jsc_sr_ChunkReadStream_t;

	void jsc_sr_ChunkReadStream___init_(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * data);
	jsc_uint8_t jsc_sr_ChunkReadStream_err_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_boolean_t jsc_sr_ChunkReadStream_valid_(jsc_class_t * __isa,jsc_object_t * __object, jsc_int_t n);
	jsc_int8_t jsc_sr_ChunkReadStream_getInt8_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_uint8_t jsc_sr_ChunkReadStream_getUint8_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_int16_t jsc_sr_ChunkReadStream_getInt16_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_uint16_t jsc_sr_ChunkReadStream_getUint16_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_int32_t jsc_sr_ChunkReadStream_getInt32_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_uint32_t jsc_sr_ChunkReadStream_getUint32_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_float32_t jsc_sr_ChunkReadStream_getFloat32_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_float64_t jsc_sr_ChunkReadStream_getFloat64_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_string_t jsc_sr_ChunkReadStream_getString_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_boolean_t jsc_sr_ChunkReadStream_getBoolean_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_object_t * jsc_sr_ChunkReadStream_getBytes_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_variant_t jsc_sr_ChunkReadStream_getValue_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_object_t * jsc_sr_ChunkReadStream_getObject_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_object_t * jsc_sr_ChunkReadStream_getArray_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_variant_t jsc_sr_ChunkReadStream_getValueWithType_(jsc_class_t * __isa,jsc_object_t * __object, jsc_uint8_t type);
	void jsc_sr_ChunkReadStream_seekInt8_(jsc_class_t * __isa,jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekUint8_(jsc_class_t * __isa,jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekInt16_(jsc_class_t * __isa,jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekUint16_(jsc_class_t * __isa,jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekInt32_(jsc_class_t * __isa,jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekUint32_(jsc_class_t * __isa,jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekFloat32_(jsc_class_t * __isa,jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekFloat64_(jsc_class_t * __isa,jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekString_(jsc_class_t * __isa,jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekBoolean_(jsc_class_t * __isa,jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekBytes_(jsc_class_t * __isa,jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekValue_(jsc_class_t * __isa,jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekObject_(jsc_class_t * __isa,jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekArray_(jsc_class_t * __isa,jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekValueWithType_(jsc_class_t * __isa,jsc_object_t * __object, jsc_uint8_t type);
	jsc_int_t jsc_sr_ChunkReadStream_offset_(jsc_class_t * __isa,jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_setOffset_(jsc_class_t * __isa,jsc_object_t * __object, jsc_int_t off);

	void jsc_sr_ChunkReadStream___init(jsc_object_t * __object, jsc_object_t * data);
	jsc_uint8_t jsc_sr_ChunkReadStream_err(jsc_object_t * __object);
	jsc_boolean_t jsc_sr_ChunkReadStream_valid(jsc_object_t * __object, jsc_int_t n);
	jsc_int8_t jsc_sr_ChunkReadStream_getInt8(jsc_object_t * __object);
	jsc_uint8_t jsc_sr_ChunkReadStream_getUint8(jsc_object_t * __object);
	jsc_int16_t jsc_sr_ChunkReadStream_getInt16(jsc_object_t * __object);
	jsc_uint16_t jsc_sr_ChunkReadStream_getUint16(jsc_object_t * __object);
	jsc_int32_t jsc_sr_ChunkReadStream_getInt32(jsc_object_t * __object);
	jsc_uint32_t jsc_sr_ChunkReadStream_getUint32(jsc_object_t * __object);
	jsc_float32_t jsc_sr_ChunkReadStream_getFloat32(jsc_object_t * __object);
	jsc_float64_t jsc_sr_ChunkReadStream_getFloat64(jsc_object_t * __object);
	jsc_string_t jsc_sr_ChunkReadStream_getString(jsc_object_t * __object);
	jsc_boolean_t jsc_sr_ChunkReadStream_getBoolean(jsc_object_t * __object);
	jsc_object_t * jsc_sr_ChunkReadStream_getBytes(jsc_object_t * __object);
	jsc_variant_t jsc_sr_ChunkReadStream_getValue(jsc_object_t * __object);
	jsc_object_t * jsc_sr_ChunkReadStream_getObject(jsc_object_t * __object);
	jsc_object_t * jsc_sr_ChunkReadStream_getArray(jsc_object_t * __object);
	jsc_variant_t jsc_sr_ChunkReadStream_getValueWithType(jsc_object_t * __object, jsc_uint8_t type);
	void jsc_sr_ChunkReadStream_seekInt8(jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekUint8(jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekInt16(jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekUint16(jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekInt32(jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekUint32(jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekFloat32(jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekFloat64(jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekString(jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekBoolean(jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekBytes(jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekValue(jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekObject(jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekArray(jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_seekValueWithType(jsc_object_t * __object, jsc_uint8_t type);
	jsc_int_t jsc_sr_ChunkReadStream_offset(jsc_object_t * __object);
	void jsc_sr_ChunkReadStream_setOffset(jsc_object_t * __object, jsc_int_t off);

	jsc_object_t * jsc_sr_ChunkReadStream_new(jsc_object_t * data);
	typedef void (*jsc_sr_Buffer___init_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_int_t capacity);
	typedef void (*jsc_sr_Buffer_capacity_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_int_t v);
	typedef jsc_int_t (*jsc_sr_Buffer_length_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef void (*jsc_sr_Buffer_setLength_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_int_t v);
	typedef jsc_object_t * (*jsc_sr_Buffer_toDataView_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef struct jsc_sr_Buffer_class_t {
		jsc_class_t base;
		jsc_sr_Buffer___init_t __init;
		jsc_sr_Buffer_capacity_t capacity;
		jsc_sr_Buffer_length_t length;
		jsc_sr_Buffer_setLength_t setLength;
		jsc_sr_Buffer_toDataView_t toDataView;
	} jsc_sr_Buffer_class_t;
	extern jsc_sr_Buffer_class_t jsc_sr_Buffer;

	typedef struct sr_Buffer_t {
		jsc_object_t base;
		jsc_object_t * _buffer;
		jsc_object_t * _view;
		jsc_int_t _length;
		jsc_int_t _capacity;
	} jsc_sr_Buffer_t;

	void jsc_sr_Buffer___init_(jsc_class_t * __isa,jsc_object_t * __object, jsc_int_t capacity);
	void jsc_sr_Buffer_capacity_(jsc_class_t * __isa,jsc_object_t * __object, jsc_int_t v);
	jsc_int_t jsc_sr_Buffer_length_(jsc_class_t * __isa,jsc_object_t * __object);
	void jsc_sr_Buffer_setLength_(jsc_class_t * __isa,jsc_object_t * __object, jsc_int_t v);
	jsc_object_t * jsc_sr_Buffer_toDataView_(jsc_class_t * __isa,jsc_object_t * __object);

	void jsc_sr_Buffer___init(jsc_object_t * __object, jsc_int_t capacity);
	void jsc_sr_Buffer_capacity(jsc_object_t * __object, jsc_int_t v);
	jsc_int_t jsc_sr_Buffer_length(jsc_object_t * __object);
	void jsc_sr_Buffer_setLength(jsc_object_t * __object, jsc_int_t v);
	jsc_object_t * jsc_sr_Buffer_toDataView(jsc_object_t * __object);

	jsc_object_t * jsc_sr_Buffer_new(jsc_int_t capacity);
	typedef void (*jsc_sr_ChunkWriteStream___init_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_uint8_t (*jsc_sr_ChunkWriteStream_err_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef void (*jsc_sr_ChunkWriteStream_setInt8_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_int8_t v);
	typedef void (*jsc_sr_ChunkWriteStream_setUint8_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_uint8_t v);
	typedef void (*jsc_sr_ChunkWriteStream_setInt16_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_int16_t v);
	typedef void (*jsc_sr_ChunkWriteStream_setUint16_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_uint16_t v);
	typedef void (*jsc_sr_ChunkWriteStream_setInt32_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_int32_t v);
	typedef void (*jsc_sr_ChunkWriteStream_setUint32_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_uint32_t v);
	typedef void (*jsc_sr_ChunkWriteStream_setFloat32_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_float32_t v);
	typedef void (*jsc_sr_ChunkWriteStream_setFloat64_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_float32_t v);
	typedef void (*jsc_sr_ChunkWriteStream_setString_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_string_t v);
	typedef void (*jsc_sr_ChunkWriteStream_setBoolean_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_boolean_t v);
	typedef void (*jsc_sr_ChunkWriteStream_setBytes_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * b);
	typedef void (*jsc_sr_ChunkWriteStream_setValue_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_variant_t v);
	typedef void (*jsc_sr_ChunkWriteStream_setObject_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * v);
	typedef void (*jsc_sr_ChunkWriteStream_setArray_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * v);
	typedef struct jsc_sr_ChunkWriteStream_class_t {
		jsc_sr_Buffer_class_t base;
		jsc_sr_ChunkWriteStream___init_t __init;
		jsc_sr_ChunkWriteStream_err_t err;
		jsc_sr_ChunkWriteStream_setInt8_t setInt8;
		jsc_sr_ChunkWriteStream_setUint8_t setUint8;
		jsc_sr_ChunkWriteStream_setInt16_t setInt16;
		jsc_sr_ChunkWriteStream_setUint16_t setUint16;
		jsc_sr_ChunkWriteStream_setInt32_t setInt32;
		jsc_sr_ChunkWriteStream_setUint32_t setUint32;
		jsc_sr_ChunkWriteStream_setFloat32_t setFloat32;
		jsc_sr_ChunkWriteStream_setFloat64_t setFloat64;
		jsc_sr_ChunkWriteStream_setString_t setString;
		jsc_sr_ChunkWriteStream_setBoolean_t setBoolean;
		jsc_sr_ChunkWriteStream_setBytes_t setBytes;
		jsc_sr_ChunkWriteStream_setValue_t setValue;
		jsc_sr_ChunkWriteStream_setObject_t setObject;
		jsc_sr_ChunkWriteStream_setArray_t setArray;
	} jsc_sr_ChunkWriteStream_class_t;
	extern jsc_sr_ChunkWriteStream_class_t jsc_sr_ChunkWriteStream;

	typedef struct sr_ChunkWriteStream_t {
		jsc_sr_Buffer_t base;
		jsc_uint8_t _err;
	} jsc_sr_ChunkWriteStream_t;

	void jsc_sr_ChunkWriteStream___init_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_uint8_t jsc_sr_ChunkWriteStream_err_(jsc_class_t * __isa,jsc_object_t * __object);
	void jsc_sr_ChunkWriteStream_setInt8_(jsc_class_t * __isa,jsc_object_t * __object, jsc_int8_t v);
	void jsc_sr_ChunkWriteStream_setUint8_(jsc_class_t * __isa,jsc_object_t * __object, jsc_uint8_t v);
	void jsc_sr_ChunkWriteStream_setInt16_(jsc_class_t * __isa,jsc_object_t * __object, jsc_int16_t v);
	void jsc_sr_ChunkWriteStream_setUint16_(jsc_class_t * __isa,jsc_object_t * __object, jsc_uint16_t v);
	void jsc_sr_ChunkWriteStream_setInt32_(jsc_class_t * __isa,jsc_object_t * __object, jsc_int32_t v);
	void jsc_sr_ChunkWriteStream_setUint32_(jsc_class_t * __isa,jsc_object_t * __object, jsc_uint32_t v);
	void jsc_sr_ChunkWriteStream_setFloat32_(jsc_class_t * __isa,jsc_object_t * __object, jsc_float32_t v);
	void jsc_sr_ChunkWriteStream_setFloat64_(jsc_class_t * __isa,jsc_object_t * __object, jsc_float32_t v);
	void jsc_sr_ChunkWriteStream_setString_(jsc_class_t * __isa,jsc_object_t * __object, jsc_string_t v);
	void jsc_sr_ChunkWriteStream_setBoolean_(jsc_class_t * __isa,jsc_object_t * __object, jsc_boolean_t v);
	void jsc_sr_ChunkWriteStream_setBytes_(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * b);
	void jsc_sr_ChunkWriteStream_setValue_(jsc_class_t * __isa,jsc_object_t * __object, jsc_variant_t v);
	void jsc_sr_ChunkWriteStream_setObject_(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * v);
	void jsc_sr_ChunkWriteStream_setArray_(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * v);

	void jsc_sr_ChunkWriteStream___init(jsc_object_t * __object);
	jsc_uint8_t jsc_sr_ChunkWriteStream_err(jsc_object_t * __object);
	void jsc_sr_ChunkWriteStream_setInt8(jsc_object_t * __object, jsc_int8_t v);
	void jsc_sr_ChunkWriteStream_setUint8(jsc_object_t * __object, jsc_uint8_t v);
	void jsc_sr_ChunkWriteStream_setInt16(jsc_object_t * __object, jsc_int16_t v);
	void jsc_sr_ChunkWriteStream_setUint16(jsc_object_t * __object, jsc_uint16_t v);
	void jsc_sr_ChunkWriteStream_setInt32(jsc_object_t * __object, jsc_int32_t v);
	void jsc_sr_ChunkWriteStream_setUint32(jsc_object_t * __object, jsc_uint32_t v);
	void jsc_sr_ChunkWriteStream_setFloat32(jsc_object_t * __object, jsc_float32_t v);
	void jsc_sr_ChunkWriteStream_setFloat64(jsc_object_t * __object, jsc_float32_t v);
	void jsc_sr_ChunkWriteStream_setString(jsc_object_t * __object, jsc_string_t v);
	void jsc_sr_ChunkWriteStream_setBoolean(jsc_object_t * __object, jsc_boolean_t v);
	void jsc_sr_ChunkWriteStream_setBytes(jsc_object_t * __object, jsc_object_t * b);
	void jsc_sr_ChunkWriteStream_setValue(jsc_object_t * __object, jsc_variant_t v);
	void jsc_sr_ChunkWriteStream_setObject(jsc_object_t * __object, jsc_object_t * v);
	void jsc_sr_ChunkWriteStream_setArray(jsc_object_t * __object, jsc_object_t * v);

	jsc_object_t * jsc_sr_ChunkWriteStream_new(void);

#ifdef __cplusplus
}
#endif

#endif

