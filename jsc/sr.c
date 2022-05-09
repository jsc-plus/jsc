#include "sr.inc"

/* class implemented */
static void _jsc_ChunkReadStream___init(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * data) {
	jsc_setStrong(&(((jsc_sr_ChunkReadStream_t *)(__object))->_data),data);
	((jsc_sr_ChunkReadStream_t *)(__object))->_index = 0;
	((jsc_sr_ChunkReadStream_t *)(__object))->_err = jsc_Error_NONE;
}
static jsc_uint8_t _jsc_ChunkReadStream_err(jsc_class_t * __isa, jsc_object_t * __object) {
	return ((jsc_sr_ChunkReadStream_t *)(__object))->_err;
}
static jsc_boolean_t _jsc_ChunkReadStream_valid(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t n) {
	return ((jsc_sr_ChunkReadStream_t *)(__object))->_err==jsc_Error_NONE&&(((jsc_sr_ChunkReadStream_t *)(__object))->_index+n<=jsc_DataView_byteLength(((jsc_sr_ChunkReadStream_t *)(__object))->_data));
}
static jsc_int8_t _jsc_ChunkReadStream_getInt8(jsc_class_t * __isa, jsc_object_t * __object) {
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,1)) {
		jsc_int8_t v=jsc_DataView_getInt8_((jsc_class_t *)&jsc_DataView,((jsc_sr_ChunkReadStream_t *)(__object))->_data,((jsc_sr_ChunkReadStream_t *)(__object))->_index);
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=1;
		return v;
	}
	
	return JSC_AS_INT8_INT(0);
}
static jsc_uint8_t _jsc_ChunkReadStream_getUint8(jsc_class_t * __isa, jsc_object_t * __object) {
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,1)) {
		jsc_uint8_t v=jsc_DataView_getUint8_((jsc_class_t *)&jsc_DataView,((jsc_sr_ChunkReadStream_t *)(__object))->_data,((jsc_sr_ChunkReadStream_t *)(__object))->_index);
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=1;
		return v;
	}
	
	return JSC_AS_UINT8_INT(0);
}
static jsc_int16_t _jsc_ChunkReadStream_getInt16(jsc_class_t * __isa, jsc_object_t * __object) {
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,2)) {
		jsc_int16_t v=jsc_DataView_getInt16_((jsc_class_t *)&jsc_DataView,((jsc_sr_ChunkReadStream_t *)(__object))->_data,((jsc_sr_ChunkReadStream_t *)(__object))->_index,1);
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=2;
		return v;
	}
	
	return JSC_AS_INT16_INT(0);
}
static jsc_uint16_t _jsc_ChunkReadStream_getUint16(jsc_class_t * __isa, jsc_object_t * __object) {
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,2)) {
		jsc_uint16_t v=jsc_DataView_getUint16_((jsc_class_t *)&jsc_DataView,((jsc_sr_ChunkReadStream_t *)(__object))->_data,((jsc_sr_ChunkReadStream_t *)(__object))->_index,1);
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=2;
		return v;
	}
	
	return JSC_AS_UINT16_INT(0);
}
static jsc_int32_t _jsc_ChunkReadStream_getInt32(jsc_class_t * __isa, jsc_object_t * __object) {
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,4)) {
		jsc_int32_t v=jsc_DataView_getInt32_((jsc_class_t *)&jsc_DataView,((jsc_sr_ChunkReadStream_t *)(__object))->_data,((jsc_sr_ChunkReadStream_t *)(__object))->_index,1);
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=4;
		return v;
	}
	
	return JSC_AS_INT32_INT(0);
}
static jsc_uint32_t _jsc_ChunkReadStream_getUint32(jsc_class_t * __isa, jsc_object_t * __object) {
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,4)) {
		jsc_uint32_t v=jsc_DataView_getUint32_((jsc_class_t *)&jsc_DataView,((jsc_sr_ChunkReadStream_t *)(__object))->_data,((jsc_sr_ChunkReadStream_t *)(__object))->_index,1);
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=4;
		return v;
	}
	
	return JSC_AS_UINT32_INT(0);
}
static jsc_float32_t _jsc_ChunkReadStream_getFloat32(jsc_class_t * __isa, jsc_object_t * __object) {
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,4)) {
		jsc_float32_t v=jsc_DataView_getFloat32_((jsc_class_t *)&jsc_DataView,((jsc_sr_ChunkReadStream_t *)(__object))->_data,((jsc_sr_ChunkReadStream_t *)(__object))->_index,1);
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=4;
		return v;
	}
	
	return JSC_AS_FLOAT32_INT(0);
}
static jsc_float64_t _jsc_ChunkReadStream_getFloat64(jsc_class_t * __isa, jsc_object_t * __object) {
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,8)) {
		jsc_float32_t v=jsc_DataView_getFloat64_((jsc_class_t *)&jsc_DataView,((jsc_sr_ChunkReadStream_t *)(__object))->_data,((jsc_sr_ChunkReadStream_t *)(__object))->_index,1);
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=8;
		return JSC_AS_FLOAT64_FLOAT32(v);
	}
	
	return JSC_AS_FLOAT64_INT(0);
}
static jsc_string_t _jsc_ChunkReadStream_getString(jsc_class_t * __isa, jsc_object_t * __object) {
	jsc_uint32_t n=jsc_sr_ChunkReadStream_getUint32_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
	if(JSC_AS_INT_UINT32(n)>0&&jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,JSC_AS_INT_UINT32(n))) {
		jsc_string_t s=jsc_DataView_getString_((jsc_class_t *)&jsc_DataView,((jsc_sr_ChunkReadStream_t *)(__object))->_data,((jsc_sr_ChunkReadStream_t *)(__object))->_index);
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=JSC_AS_INT_UINT32(n);
		return s;
	}
	
	return JSC_AS_STRING_NIL(NULL);
}
static jsc_boolean_t _jsc_ChunkReadStream_getBoolean(jsc_class_t * __isa, jsc_object_t * __object) {
	return JSC_AS_INT_UINT8(jsc_sr_ChunkReadStream_getUint8_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object))!=0;
}
static jsc_object_t * _jsc_ChunkReadStream_getBytes(jsc_class_t * __isa, jsc_object_t * __object) {
	jsc_uint32_t n=jsc_sr_ChunkReadStream_getUint32_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
	if(JSC_AS_INT_UINT32(n)>0&&jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,JSC_AS_INT_UINT32(n))) {
		jsc_object_t * v=(jsc_object_t *) jsc_DataView_new(jsc_DataView_buffer(((jsc_sr_ChunkReadStream_t *)(__object))->_data),jsc_DataView_byteOffset(((jsc_sr_ChunkReadStream_t *)(__object))->_data)+((jsc_sr_ChunkReadStream_t *)(__object))->_index,JSC_AS_INT_UINT32(n));
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=JSC_AS_INT_UINT32(n);
		return v;
	}
	
	return JSC_AS_OBJECT_NIL(NULL);
}
static jsc_variant_t _jsc_ChunkReadStream_getValue(jsc_class_t * __isa, jsc_object_t * __object) {
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,1)) {
		return jsc_sr_ChunkReadStream_getValueWithType_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,jsc_sr_ChunkReadStream_getUint8_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object));
	}
	
	return JSC_AS_VARIANT_NIL(NULL);
}
static jsc_object_t * _jsc_ChunkReadStream_getObject(jsc_class_t * __isa, jsc_object_t * __object) {
	jsc_object_t * m=jsc_object_new((jsc_class_t*)&jsc_Map,0);
	while(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,1)) {
		jsc_uint8_t type=jsc_sr_ChunkReadStream_getUint8_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
		if(type==jsc_Type_END) {
			break;
		}
		else {
			if(type!=jsc_Type_STRING) {
				((jsc_sr_ChunkReadStream_t *)(__object))->_err = jsc_Error_STREAM;
				break;
			}
			
			jsc_string_t key=jsc_sr_ChunkReadStream_getString_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
			jsc_variant_t value=jsc_sr_ChunkReadStream_getValue_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
			if(JSC_STRING_COMP(key,JSC_AS_STRING_NIL(NULL)) != 0&&jsc_variant_strict_compare(value,JSC_AS_VARIANT_NIL(NULL)) != 0) {
				jsc_Map_set_((jsc_class_t *)&jsc_Map,m,JSC_AS_VARIANT_STRING(key),value);
			}
			
		}
		
	}
	
	return m;
}
static jsc_object_t * _jsc_ChunkReadStream_getArray(jsc_class_t * __isa, jsc_object_t * __object) {
	jsc_object_t * a=jsc_object_new((jsc_class_t *) &jsc_Array,0);
	while(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,1)) {
		jsc_uint8_t type=jsc_sr_ChunkReadStream_getUint8_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
		if(type==jsc_Type_END) {
			break;
		}
		else {
			jsc_variant_t value=jsc_sr_ChunkReadStream_getValueWithType_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,type);
			jsc_Array_push_((jsc_class_t *)&jsc_Array,a,value);
		}
		
	}
	
	return a;
}
static jsc_variant_t _jsc_ChunkReadStream_getValueWithType(jsc_class_t * __isa, jsc_object_t * __object, jsc_uint8_t type) {
	switch(type) {
	case jsc_Type_NIL:
		break;
	case jsc_Type_INT8:
		return JSC_AS_VARIANT_INT8(jsc_sr_ChunkReadStream_getInt8_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object));
	case jsc_Type_UINT8:
		return JSC_AS_VARIANT_UINT8(jsc_sr_ChunkReadStream_getUint8_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object));
	case jsc_Type_INT16:
		return JSC_AS_VARIANT_INT16(jsc_sr_ChunkReadStream_getInt16_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object));
	case jsc_Type_UINT16:
		return JSC_AS_VARIANT_UINT16(jsc_sr_ChunkReadStream_getUint16_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object));
	case jsc_Type_INT32:
		return JSC_AS_VARIANT_INT32(jsc_sr_ChunkReadStream_getInt32_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object));
	case jsc_Type_UINT32:
		return JSC_AS_VARIANT_UINT32(jsc_sr_ChunkReadStream_getUint32_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object));
	case jsc_Type_FLOAT32:
		return JSC_AS_VARIANT_FLOAT32(jsc_sr_ChunkReadStream_getFloat32_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object));
	case jsc_Type_FLOAT64:
		return JSC_AS_VARIANT_FLOAT64(jsc_sr_ChunkReadStream_getFloat64_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object));
	case jsc_Type_BOOLEAN:
		return JSC_AS_VARIANT_BOOLEAN(jsc_sr_ChunkReadStream_getBoolean_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object));
	case jsc_Type_STRING:
		return JSC_AS_VARIANT_STRING(jsc_sr_ChunkReadStream_getString_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object));
	case jsc_Type_BYTES:
		return JSC_AS_VARIANT_OBJECT(jsc_sr_ChunkReadStream_getBytes_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object));
	case jsc_Type_OBJECT:
		return JSC_AS_VARIANT_OBJECT(jsc_sr_ChunkReadStream_getObject_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object));
	case jsc_Type_ARRAY:
		return JSC_AS_VARIANT_OBJECT(jsc_sr_ChunkReadStream_getArray_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object));
	default :
		((jsc_sr_ChunkReadStream_t *)(__object))->_err = jsc_Error_STREAM;
		break;
	}
	
	return JSC_AS_VARIANT_NIL(NULL);
}
static void _jsc_ChunkReadStream_seekInt8(jsc_class_t * __isa, jsc_object_t * __object) {
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,1)) {
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=1;
	}
	
}
static void _jsc_ChunkReadStream_seekUint8(jsc_class_t * __isa, jsc_object_t * __object) {
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,1)) {
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=1;
	}
	
}
static void _jsc_ChunkReadStream_seekInt16(jsc_class_t * __isa, jsc_object_t * __object) {
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,2)) {
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=2;
	}
	
}
static void _jsc_ChunkReadStream_seekUint16(jsc_class_t * __isa, jsc_object_t * __object) {
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,2)) {
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=2;
	}
	
}
static void _jsc_ChunkReadStream_seekInt32(jsc_class_t * __isa, jsc_object_t * __object) {
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,4)) {
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=4;
	}
	
}
static void _jsc_ChunkReadStream_seekUint32(jsc_class_t * __isa, jsc_object_t * __object) {
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,4)) {
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=4;
	}
	
}
static void _jsc_ChunkReadStream_seekFloat32(jsc_class_t * __isa, jsc_object_t * __object) {
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,4)) {
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=4;
	}
	
}
static void _jsc_ChunkReadStream_seekFloat64(jsc_class_t * __isa, jsc_object_t * __object) {
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,8)) {
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=8;
	}
	
}
static void _jsc_ChunkReadStream_seekString(jsc_class_t * __isa, jsc_object_t * __object) {
	jsc_uint32_t n=jsc_sr_ChunkReadStream_getUint32_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,JSC_AS_INT_UINT32(n))) {
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=JSC_AS_INT_UINT32(n);
	}
	
}
static void _jsc_ChunkReadStream_seekBoolean(jsc_class_t * __isa, jsc_object_t * __object) {
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,1)) {
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=1;
	}
	
}
static void _jsc_ChunkReadStream_seekBytes(jsc_class_t * __isa, jsc_object_t * __object) {
	jsc_uint32_t n=jsc_sr_ChunkReadStream_getUint32_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,JSC_AS_INT_UINT32(n))) {
		((jsc_sr_ChunkReadStream_t *)(__object))->_index+=JSC_AS_INT_UINT32(n);
	}
	
}
static void _jsc_ChunkReadStream_seekValue(jsc_class_t * __isa, jsc_object_t * __object) {
	if(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,1)) {
		jsc_sr_ChunkReadStream_seekValueWithType_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,jsc_sr_ChunkReadStream_getUint8_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object));
	}
	
}
static void _jsc_ChunkReadStream_seekObject(jsc_class_t * __isa, jsc_object_t * __object) {
	while(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,1)) {
		jsc_uint8_t type=jsc_sr_ChunkReadStream_getUint8_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
		if(type==jsc_Type_END) {
			break;
		}
		else {
			if(type!=jsc_Type_STRING) {
				((jsc_sr_ChunkReadStream_t *)(__object))->_err = jsc_Error_STREAM;
				break;
			}
			
			jsc_sr_ChunkReadStream_seekString_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
			jsc_sr_ChunkReadStream_seekValue_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
		}
		
	}
	
}
static void _jsc_ChunkReadStream_seekArray(jsc_class_t * __isa, jsc_object_t * __object) {
	while(jsc_sr_ChunkReadStream_valid_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,1)) {
		jsc_uint8_t type=jsc_sr_ChunkReadStream_getUint8_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
		if(type==jsc_Type_END) {
			break;
		}
		else {
			jsc_sr_ChunkReadStream_seekValueWithType_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object,type);
		}
		
	}
	
}
static void _jsc_ChunkReadStream_seekValueWithType(jsc_class_t * __isa, jsc_object_t * __object, jsc_uint8_t type) {
	switch(type) {
	case jsc_Type_NIL:
		break;
	case jsc_Type_INT8:
		jsc_sr_ChunkReadStream_seekInt8_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
		break;
	case jsc_Type_UINT8:
		jsc_sr_ChunkReadStream_seekUint8_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
		break;
	case jsc_Type_INT16:
		jsc_sr_ChunkReadStream_seekInt16_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
		break;
	case jsc_Type_UINT16:
		jsc_sr_ChunkReadStream_seekUint16_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
		break;
	case jsc_Type_INT32:
		jsc_sr_ChunkReadStream_seekInt32_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
		break;
	case jsc_Type_UINT32:
		jsc_sr_ChunkReadStream_seekUint32_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
		break;
	case jsc_Type_FLOAT32:
		jsc_sr_ChunkReadStream_seekFloat32_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
		break;
	case jsc_Type_FLOAT64:
		jsc_sr_ChunkReadStream_seekFloat64_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
		break;
	case jsc_Type_BOOLEAN:
		jsc_sr_ChunkReadStream_seekBoolean_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
		break;
	case jsc_Type_STRING:
		jsc_sr_ChunkReadStream_seekString_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
		break;
	case jsc_Type_BYTES:
		jsc_sr_ChunkReadStream_seekBytes_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
		break;
	case jsc_Type_OBJECT:
		jsc_sr_ChunkReadStream_seekObject_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
		break;
	case jsc_Type_ARRAY:
		jsc_sr_ChunkReadStream_seekArray_((jsc_class_t *)&jsc_sr_ChunkReadStream,__object);
		break;
	default :
		((jsc_sr_ChunkReadStream_t *)(__object))->_err = jsc_Error_STREAM;
		break;
	}
	
}
static jsc_int_t _jsc_ChunkReadStream_offset(jsc_class_t * __isa, jsc_object_t * __object) {
	return ((jsc_sr_ChunkReadStream_t *)(__object))->_index;
}
static void _jsc_ChunkReadStream_setOffset(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t off) {
	((jsc_sr_ChunkReadStream_t *)(__object))->_index = off;
}
static void _jsc_Buffer___init(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t capacity) {
	((jsc_sr_Buffer_t *)(__object))->_capacity = capacity;
	jsc_setStrong(&(((jsc_sr_Buffer_t *)(__object))->_buffer),(jsc_object_t *) jsc_ArrayBuffer_new(capacity));
	((jsc_sr_Buffer_t *)(__object))->_length = 0;
	jsc_setStrong(&(((jsc_sr_Buffer_t *)(__object))->_view),(jsc_object_t *) jsc_DataView_new(((jsc_sr_Buffer_t *)(__object))->_buffer,0,jsc_ArrayBuffer_byteLength(((jsc_sr_Buffer_t *)(__object))->_buffer)));
}
static void _jsc_Buffer_capacity(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t v) {
	if(v>jsc_ArrayBuffer_byteLength(((jsc_sr_Buffer_t *)(__object))->_buffer)) {
		jsc_float64_t n=jsc_Math_max(JSC_AS_FLOAT64_INT(v),JSC_AS_FLOAT64_INT(jsc_ArrayBuffer_byteLength(((jsc_sr_Buffer_t *)(__object))->_buffer)+((jsc_sr_Buffer_t *)(__object))->_capacity));
		jsc_object_t * dst=(jsc_object_t *) jsc_ArrayBuffer_new(JSC_AS_INT_FLOAT64(n));
		jsc_object_t * view=(jsc_object_t *) jsc_DataView_new(dst,0,jsc_ArrayBuffer_byteLength(dst));
		jsc_ArrayBuffer_copy_((jsc_class_t *)&jsc_ArrayBuffer,((jsc_sr_Buffer_t *)(__object))->_buffer,view,0,jsc_ArrayBuffer_byteLength(((jsc_sr_Buffer_t *)(__object))->_buffer));
		jsc_setStrong(&(((jsc_sr_Buffer_t *)(__object))->_buffer),dst);
		jsc_setStrong(&(((jsc_sr_Buffer_t *)(__object))->_view),view);
	}
	
}
static jsc_int_t _jsc_Buffer_length(jsc_class_t * __isa, jsc_object_t * __object) {
	return ((jsc_sr_Buffer_t *)(__object))->_length;
}
static void _jsc_Buffer_setLength(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t v) {
	((jsc_sr_Buffer_t *)(__object))->_length = v;
	jsc_sr_Buffer_capacity_((jsc_class_t *)&jsc_sr_Buffer,__object,v);
}
static jsc_object_t * _jsc_Buffer_toDataView(jsc_class_t * __isa, jsc_object_t * __object) {
	return (jsc_object_t *) jsc_DataView_new(((jsc_sr_Buffer_t *)(__object))->_buffer,0,((jsc_sr_Buffer_t *)(__object))->_length);
}
static void _jsc_ChunkWriteStream___init(jsc_class_t * __isa, jsc_object_t * __object) {
	jsc_sr_Buffer___init_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,20480);
	((jsc_sr_ChunkWriteStream_t *)(__object))->_err = jsc_Error_NONE;
}
static jsc_uint8_t _jsc_ChunkWriteStream_err(jsc_class_t * __isa, jsc_object_t * __object) {
	return ((jsc_sr_ChunkWriteStream_t *)(__object))->_err;
}
static void _jsc_ChunkWriteStream_setInt8(jsc_class_t * __isa, jsc_object_t * __object, jsc_int8_t v) {
	jsc_sr_Buffer_capacity_((jsc_class_t *)&jsc_sr_Buffer,__object,((jsc_sr_Buffer_t *)(__object))->_length+1);
	jsc_DataView_setInt8_((jsc_class_t *)&jsc_DataView,((jsc_sr_Buffer_t *)(__object))->_view,((jsc_sr_Buffer_t *)(__object))->_length,v);
	((jsc_sr_Buffer_t *)(__object))->_length+=1;
}
static void _jsc_ChunkWriteStream_setUint8(jsc_class_t * __isa, jsc_object_t * __object, jsc_uint8_t v) {
	jsc_sr_Buffer_capacity_((jsc_class_t *)&jsc_sr_Buffer,__object,((jsc_sr_Buffer_t *)(__object))->_length+1);
	jsc_DataView_setUint8_((jsc_class_t *)&jsc_DataView,((jsc_sr_Buffer_t *)(__object))->_view,((jsc_sr_Buffer_t *)(__object))->_length,v);
	((jsc_sr_Buffer_t *)(__object))->_length+=1;
}
static void _jsc_ChunkWriteStream_setInt16(jsc_class_t * __isa, jsc_object_t * __object, jsc_int16_t v) {
	jsc_sr_Buffer_capacity_((jsc_class_t *)&jsc_sr_Buffer,__object,((jsc_sr_Buffer_t *)(__object))->_length+2);
	jsc_DataView_setInt16_((jsc_class_t *)&jsc_DataView,((jsc_sr_Buffer_t *)(__object))->_view,((jsc_sr_Buffer_t *)(__object))->_length,v,1);
	((jsc_sr_Buffer_t *)(__object))->_length+=2;
}
static void _jsc_ChunkWriteStream_setUint16(jsc_class_t * __isa, jsc_object_t * __object, jsc_uint16_t v) {
	jsc_sr_Buffer_capacity_((jsc_class_t *)&jsc_sr_Buffer,__object,((jsc_sr_Buffer_t *)(__object))->_length+2);
	jsc_DataView_setUint16_((jsc_class_t *)&jsc_DataView,((jsc_sr_Buffer_t *)(__object))->_view,((jsc_sr_Buffer_t *)(__object))->_length,v,1);
	((jsc_sr_Buffer_t *)(__object))->_length+=2;
}
static void _jsc_ChunkWriteStream_setInt32(jsc_class_t * __isa, jsc_object_t * __object, jsc_int32_t v) {
	jsc_sr_Buffer_capacity_((jsc_class_t *)&jsc_sr_Buffer,__object,((jsc_sr_Buffer_t *)(__object))->_length+4);
	jsc_DataView_setInt32_((jsc_class_t *)&jsc_DataView,((jsc_sr_Buffer_t *)(__object))->_view,((jsc_sr_Buffer_t *)(__object))->_length,v,1);
	((jsc_sr_Buffer_t *)(__object))->_length+=4;
}
static void _jsc_ChunkWriteStream_setUint32(jsc_class_t * __isa, jsc_object_t * __object, jsc_uint32_t v) {
	jsc_sr_Buffer_capacity_((jsc_class_t *)&jsc_sr_Buffer,__object,((jsc_sr_Buffer_t *)(__object))->_length+4);
	jsc_DataView_setUint32_((jsc_class_t *)&jsc_DataView,((jsc_sr_Buffer_t *)(__object))->_view,((jsc_sr_Buffer_t *)(__object))->_length,v,1);
	((jsc_sr_Buffer_t *)(__object))->_length+=4;
}
static void _jsc_ChunkWriteStream_setFloat32(jsc_class_t * __isa, jsc_object_t * __object, jsc_float32_t v) {
	jsc_sr_Buffer_capacity_((jsc_class_t *)&jsc_sr_Buffer,__object,((jsc_sr_Buffer_t *)(__object))->_length+4);
	jsc_DataView_setFloat32_((jsc_class_t *)&jsc_DataView,((jsc_sr_Buffer_t *)(__object))->_view,((jsc_sr_Buffer_t *)(__object))->_length,v,1);
	((jsc_sr_Buffer_t *)(__object))->_length+=4;
}
static void _jsc_ChunkWriteStream_setFloat64(jsc_class_t * __isa, jsc_object_t * __object, jsc_float32_t v) {
	jsc_sr_Buffer_capacity_((jsc_class_t *)&jsc_sr_Buffer,__object,((jsc_sr_Buffer_t *)(__object))->_length+8);
	jsc_DataView_setFloat64_((jsc_class_t *)&jsc_DataView,((jsc_sr_Buffer_t *)(__object))->_view,((jsc_sr_Buffer_t *)(__object))->_length,JSC_AS_FLOAT64_FLOAT32(v),1);
	((jsc_sr_Buffer_t *)(__object))->_length+=8;
}
static void _jsc_ChunkWriteStream_setString(jsc_class_t * __isa, jsc_object_t * __object, jsc_string_t v) {
	jsc_object_t * b=jsc_crypto_encodeString(v,jsc_crypto_UTF8);
	jsc_sr_ChunkWriteStream_setUint32_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,JSC_AS_UINT32_INT(jsc_ArrayBuffer_byteLength(b)));
	jsc_sr_Buffer_capacity_((jsc_class_t *)&jsc_sr_Buffer,__object,((jsc_sr_Buffer_t *)(__object))->_length+jsc_ArrayBuffer_byteLength(b)+1);
	jsc_DataView_setData_((jsc_class_t *)&jsc_DataView,((jsc_sr_Buffer_t *)(__object))->_view,((jsc_sr_Buffer_t *)(__object))->_length,(jsc_object_t *) jsc_DataView_new(b,0,jsc_ArrayBuffer_byteLength(b)));
	((jsc_sr_Buffer_t *)(__object))->_length+=jsc_ArrayBuffer_byteLength(b);
	jsc_sr_ChunkWriteStream_setUint8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,JSC_AS_UINT8_INT(0));
}
static void _jsc_ChunkWriteStream_setBoolean(jsc_class_t * __isa, jsc_object_t * __object, jsc_boolean_t v) {
	jsc_sr_ChunkWriteStream_setUint8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,JSC_AS_UINT8_INT(v ? 1 : 0));
}
static void _jsc_ChunkWriteStream_setBytes(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * b) {
	jsc_sr_ChunkWriteStream_setUint32_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,JSC_AS_UINT32_INT(jsc_DataView_byteLength(b)));
	jsc_sr_Buffer_capacity_((jsc_class_t *)&jsc_sr_Buffer,__object,((jsc_sr_Buffer_t *)(__object))->_length+jsc_DataView_byteLength(b));
	jsc_DataView_setData_((jsc_class_t *)&jsc_DataView,((jsc_sr_Buffer_t *)(__object))->_view,((jsc_sr_Buffer_t *)(__object))->_length,b);
	((jsc_sr_Buffer_t *)(__object))->_length+=jsc_DataView_byteLength(b);
}
static void _jsc_ChunkWriteStream_setValue(jsc_class_t * __isa, jsc_object_t * __object, jsc_variant_t v) {
	if(jsc_Typeof_isInt8(v)) {
		jsc_sr_ChunkWriteStream_setUint8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,jsc_Type_INT8);
		jsc_sr_ChunkWriteStream_setInt8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,JSC_AS_INT8_VARIANT(v));
	}
	else if(jsc_Typeof_isUint8(v)) {
		jsc_sr_ChunkWriteStream_setUint8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,jsc_Type_UINT8);
		jsc_sr_ChunkWriteStream_setUint8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,JSC_AS_UINT8_VARIANT(v));
	}
	else if(jsc_Typeof_isInt16(v)) {
		jsc_sr_ChunkWriteStream_setUint8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,jsc_Type_INT16);
		jsc_sr_ChunkWriteStream_setInt16_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,JSC_AS_INT16_VARIANT(v));
	}
	else if(jsc_Typeof_isUint16(v)) {
		jsc_sr_ChunkWriteStream_setUint8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,jsc_Type_UINT16);
		jsc_sr_ChunkWriteStream_setUint16_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,JSC_AS_UINT16_VARIANT(v));
	}
	else if(jsc_Typeof_isInt32(v)) {
		jsc_sr_ChunkWriteStream_setUint8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,jsc_Type_INT32);
		jsc_sr_ChunkWriteStream_setInt32_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,JSC_AS_INT32_VARIANT(v));
	}
	else if(jsc_Typeof_isUint32(v)) {
		jsc_sr_ChunkWriteStream_setUint8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,jsc_Type_UINT32);
		jsc_sr_ChunkWriteStream_setUint32_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,JSC_AS_UINT32_VARIANT(v));
	}
	else if(jsc_Typeof_isInt64(v)||jsc_Typeof_isUint16(v)) {
		jsc_sr_ChunkWriteStream_setUint8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,jsc_Type_STRING);
		jsc_sr_ChunkWriteStream_setString_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,JSC_AS_STRING_VARIANT(v));
	}
	else if(jsc_Typeof_isFloat32(v)) {
		jsc_sr_ChunkWriteStream_setUint8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,jsc_Type_FLOAT32);
		jsc_sr_ChunkWriteStream_setFloat32_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,JSC_AS_FLOAT32_VARIANT(v));
	}
	else if(jsc_Typeof_isFloat64(v)) {
		jsc_sr_ChunkWriteStream_setUint8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,jsc_Type_FLOAT64);
		jsc_sr_ChunkWriteStream_setFloat64_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,JSC_AS_FLOAT32_VARIANT(v));
	}
	else if(jsc_Typeof_isBoolean(v)) {
		jsc_sr_ChunkWriteStream_setUint8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,jsc_Type_BOOLEAN);
		jsc_sr_ChunkWriteStream_setBoolean_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,JSC_AS_BOOLEAN_VARIANT(v));
	}
	else if(jsc_Typeof_isUnichar(v)) {
		jsc_sr_ChunkWriteStream_setUint8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,jsc_Type_UINT16);
		jsc_sr_ChunkWriteStream_setUint16_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,JSC_AS_UINT16_VARIANT(v));
	}
	else if(jsc_Typeof_isString(v)) {
		jsc_sr_ChunkWriteStream_setUint8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,jsc_Type_STRING);
		jsc_sr_ChunkWriteStream_setString_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,JSC_AS_STRING_VARIANT(v));
	}
	else if(jsc_object_isKind(JSC_AS_OBJECT_VARIANT(v),(jsc_class_t *) &jsc_Array)) {
		jsc_sr_ChunkWriteStream_setUint8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,jsc_Type_ARRAY);
		jsc_sr_ChunkWriteStream_setArray_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,JSC_AS_OBJECT_VARIANT(v));
	}
	else if(jsc_object_isKind(JSC_AS_OBJECT_VARIANT(v),(jsc_class_t *) &jsc_Map)) {
		jsc_sr_ChunkWriteStream_setUint8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,jsc_Type_OBJECT);
		jsc_sr_ChunkWriteStream_setObject_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,JSC_AS_OBJECT_VARIANT(v));
	}
	else if(jsc_object_isKind(JSC_AS_OBJECT_VARIANT(v),(jsc_class_t *) &jsc_DataView)) {
		jsc_sr_ChunkWriteStream_setUint8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,jsc_Type_BYTES);
		jsc_sr_ChunkWriteStream_setBytes_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,JSC_AS_OBJECT_VARIANT(v));
	}
	else {
		jsc_sr_ChunkWriteStream_setUint8_((jsc_class_t *)&jsc_sr_ChunkWriteStream,__object,jsc_Type_NIL);
	}
	
}
static void _jsc_ChunkWriteStream_setObject(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * v) {
}
static void _jsc_ChunkWriteStream_setArray(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * v) {
}

/* function implemented */
