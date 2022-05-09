//
//  jsc_DataView.h
//  jsc
//
//  Created by 张海龙 on 2022/5/4.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#ifndef jsc_DataView_h
#define jsc_DataView_h


#ifdef __cplusplus
extern "C" {
#endif

    struct jsc_DataView_t;
    struct jsc_ArrayBuffer_t;

    typedef jsc_object_t * (*jsc_DataView_buffer_t)(jsc_class_t * isa, jsc_object_t * object);
    typedef jsc_int_t (*jsc_DataView_byteOffset_t)(jsc_class_t * isa, jsc_object_t * object);
    typedef jsc_int_t (*jsc_DataView_byteLength_t)(jsc_class_t * isa, jsc_object_t * object);
    typedef jsc_int8_t (*jsc_DataView_getInt8_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset);
    typedef jsc_uint8_t (*jsc_DataView_getUint8_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset);
    typedef jsc_int16_t (*jsc_DataView_getInt16_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    typedef jsc_uint16_t (*jsc_DataView_getUint16_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    typedef jsc_int32_t (*jsc_DataView_getInt32_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    typedef jsc_uint32_t (*jsc_DataView_getUint32_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    typedef jsc_int64_t (*jsc_DataView_getInt64_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    typedef jsc_uint64_t (*jsc_DataView_getUint64_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    typedef jsc_float32_t (*jsc_DataView_getFloat32_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    typedef jsc_float64_t (*jsc_DataView_getFloat64_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);

    typedef jsc_string_t (*jsc_DataView_getString_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset);
    typedef jsc_object_t * (*jsc_DataView_getData_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int_t length);
    
    typedef void (*jsc_DataView_setInt8_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int8_t value);
    typedef void (*jsc_DataView_setUint8_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint8_t value);
    typedef void (*jsc_DataView_setInt16_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int16_t value,jsc_boolean_t littleEndian);
    typedef void (*jsc_DataView_setUint16_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint16_t value,jsc_boolean_t littleEndian);
    typedef void (*jsc_DataView_setInt32_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int32_t value,jsc_boolean_t littleEndian);
    typedef void (*jsc_DataView_setUint32_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint32_t value,jsc_boolean_t littleEndian);
    typedef void (*jsc_DataView_setInt64_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int64_t value,jsc_boolean_t littleEndian);
    typedef void (*jsc_DataView_setUint64_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint64_t value,jsc_boolean_t littleEndian);
    typedef void (*jsc_DataView_setFloat32_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_float32_t value,jsc_boolean_t littleEndian);
    typedef void (*jsc_DataView_setFloat64_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_float64_t value,jsc_boolean_t littleEndian);

    typedef jsc_int_t (*jsc_DataView_setString_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_string_t value);
    typedef jsc_int_t (*jsc_DataView_setData_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_object_t * data);
   
    typedef struct jsc_DataView_class_t {
        jsc_class_t base;
        jsc_DataView_buffer_t buffer;
        jsc_DataView_byteOffset_t byteOffset;
        jsc_DataView_byteLength_t byteLength;
        jsc_DataView_getInt8_t getInt8;
        jsc_DataView_getUint8_t getUint8;
        jsc_DataView_getInt16_t getInt16;
        jsc_DataView_getUint16_t getUint16;
        jsc_DataView_getInt32_t getInt32;
        jsc_DataView_getUint32_t getUint32;
        jsc_DataView_getInt64_t getInt64;
        jsc_DataView_getUint64_t getUint64;
        jsc_DataView_getFloat32_t getFloat32;
        jsc_DataView_getFloat64_t getFloat64;
        
        jsc_DataView_getString_t getString;
        jsc_DataView_getData_t getData;
        
        jsc_DataView_setInt8_t setInt8;
        jsc_DataView_setUint8_t setUint8;
        jsc_DataView_setInt16_t setInt16;
        jsc_DataView_setUint16_t setUint16;
        jsc_DataView_setInt32_t setInt32;
        jsc_DataView_setUint32_t setUint32;
        jsc_DataView_setInt64_t setInt64;
        jsc_DataView_setUint64_t setUint64;
        jsc_DataView_setFloat32_t setFloat32;
        jsc_DataView_setFloat64_t setFloat64;
        
        jsc_DataView_setString_t setString;
        jsc_DataView_setData_t setData;
        
    } jsc_DataView_class_t;

    extern jsc_DataView_class_t jsc_DataView;

    typedef struct jsc_DataView_t {
        jsc_object_t base;
        jsc_ArrayBuffer_t * _buffer;
        jsc_int_t _byteOffset;
        jsc_int_t _byteLength;
    } jsc_DataView_t;

    jsc_object_t * jsc_DataView_buffer_(jsc_class_t * isa, jsc_object_t * object);
    jsc_int_t jsc_DataView_byteOffset_(jsc_class_t * isa, jsc_object_t * object);
    jsc_int_t jsc_DataView_byteLength_(jsc_class_t * isa, jsc_object_t * object);
    jsc_int8_t jsc_DataView_getInt8_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset);
    jsc_uint8_t jsc_DataView_getUint8_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset);
    jsc_int16_t jsc_DataView_getInt16_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    jsc_uint16_t jsc_DataView_getUint16_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    jsc_int32_t jsc_DataView_getInt32_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    jsc_uint32_t jsc_DataView_getUint32_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    jsc_int64_t jsc_DataView_getInt64_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    jsc_uint64_t jsc_DataView_getUint64_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    jsc_float32_t jsc_DataView_getFloat32_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    jsc_float64_t jsc_DataView_getFloat64_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    jsc_string_t jsc_DataView_getString_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset);
    jsc_object_t * jsc_DataView_getData_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int_t length);


    jsc_object_t * jsc_DataView_buffer(jsc_object_t * object);
    jsc_int_t jsc_DataView_byteOffset(jsc_object_t * object);
    jsc_int_t jsc_DataView_byteLength(jsc_object_t * object);
    jsc_int8_t jsc_DataView_getInt8(jsc_object_t * object,jsc_int_t offset);
    jsc_uint8_t jsc_DataView_getUint8(jsc_object_t * object,jsc_int_t offset);
    jsc_int16_t jsc_DataView_getInt16(jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    jsc_uint16_t jsc_DataView_getUint16(jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    jsc_int32_t jsc_DataView_getInt32(jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    jsc_uint32_t jsc_DataView_getUint32(jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    jsc_int64_t jsc_DataView_getInt64(jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    jsc_uint64_t jsc_DataView_getUint64(jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    jsc_float32_t jsc_DataView_getFloat32(jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    jsc_float64_t jsc_DataView_getFloat64(jsc_object_t * object,jsc_int_t offset,jsc_boolean_t littleEndian);
    jsc_string_t jsc_DataView_getString(jsc_object_t * object,jsc_int_t offset);
    jsc_object_t * jsc_DataView_getData(jsc_object_t * object,jsc_int_t offset,jsc_int_t length);
    

    void jsc_DataView_setInt8_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int8_t value);
    void jsc_DataView_setUint8_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint8_t value);
    void jsc_DataView_setInt16_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int16_t value,jsc_boolean_t littleEndian);
    void jsc_DataView_setUint16_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint16_t value,jsc_boolean_t littleEndian);
    void jsc_DataView_setInt32_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int32_t value,jsc_boolean_t littleEndian);
    void jsc_DataView_setUint32_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint32_t value,jsc_boolean_t littleEndian);
    void jsc_DataView_setInt64_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_int64_t value,jsc_boolean_t littleEndian);
    void jsc_DataView_setUint64_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_uint64_t value,jsc_boolean_t littleEndian);
    void jsc_DataView_setFloat32_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_float32_t value,jsc_boolean_t littleEndian);
    void jsc_DataView_setFloat64_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_float64_t value,jsc_boolean_t littleEndian);
    jsc_int_t jsc_DataView_setString_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_string_t value);
    jsc_int_t jsc_DataView_setData_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t offset,jsc_object_t * data);

    void jsc_DataView_setInt8(jsc_object_t * object,jsc_int_t offset,jsc_int8_t value);
    void jsc_DataView_setUint8(jsc_object_t * object,jsc_int_t offset,jsc_uint8_t value);
    void jsc_DataView_setInt16(jsc_object_t * object,jsc_int_t offset,jsc_int16_t value,jsc_boolean_t littleEndian);
    void jsc_DataView_setUint16(jsc_object_t * object,jsc_int_t offset,jsc_uint16_t value,jsc_boolean_t littleEndian);
    void jsc_DataView_setInt32(jsc_object_t * object,jsc_int_t offset,jsc_int32_t value,jsc_boolean_t littleEndian);
    void jsc_DataView_setUint32(jsc_object_t * object,jsc_int_t offset,jsc_uint32_t value,jsc_boolean_t littleEndian);
    void jsc_DataView_setInt64(jsc_object_t * object,jsc_int_t offset,jsc_int64_t value,jsc_boolean_t littleEndian);
    void jsc_DataView_setUint64(jsc_object_t * object,jsc_int_t offset,jsc_uint64_t value,jsc_boolean_t littleEndian);
    void jsc_DataView_setFloat32(jsc_object_t * object,jsc_int_t offset,jsc_float32_t value,jsc_boolean_t littleEndian);
    void jsc_DataView_setFloat64(jsc_object_t * object,jsc_int_t offset,jsc_float64_t value,jsc_boolean_t littleEndian);
    jsc_int_t jsc_DataView_setString(jsc_object_t * object,jsc_int_t offset,jsc_string_t value);
    jsc_int_t jsc_DataView_setData(jsc_object_t * object,jsc_int_t offset,jsc_object_t * data);


    struct jsc_DataView_t * jsc_DataView_alloc(jsc_object_t * buffer,jsc_int_t offset,jsc_int_t length);
    struct jsc_DataView_t * jsc_DataView_new(jsc_object_t * buffer,jsc_int_t offset,jsc_int_t length);

#ifdef __cplusplus
}
#endif

#endif /* jsc_DataView_h */
