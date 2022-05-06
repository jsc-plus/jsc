//
//  jsc_String.h
//  jsc
//
//  Created by 张海龙 on 2022/1/17.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#ifndef jsc_String_h
#define jsc_String_h


#ifdef __cplusplus
extern "C" {
#endif

    struct jsc_String_t;
    struct jsc_Array_t;
    struct jsc_buffer_t;

    typedef jsc_int_t (*jsc_String_length_t)(jsc_class_t * isa, jsc_object_t * object);
    typedef jsc_unichar_t (*jsc_String___index_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index);
    typedef jsc_string_t (*jsc_String_CString_t)(jsc_class_t * isa, jsc_object_t * object);
    typedef jsc_unichar_t (*jsc_String_charAt_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index);
    typedef jsc_int_t (*jsc_String_charCodeAt_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index);
    typedef jsc_int_t (*jsc_String_codePointAt_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index);
    typedef struct jsc_String_t * (*jsc_String_concat_t)(jsc_class_t * isa, jsc_object_t * object,jsc_string_t s);
    typedef jsc_int_t (*jsc_String_indexOf_t)(jsc_class_t * isa, jsc_object_t * object,jsc_string_t s);
    typedef struct jsc_String_t * (*jsc_String_repeat_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t n);
    typedef struct jsc_String_t * (*jsc_String_replace_t)(jsc_class_t * isa, jsc_object_t * object,jsc_string_t substr,jsc_string_t newSubstr);
    typedef struct jsc_String_t * (*jsc_String_slice_t)(jsc_class_t * isa, jsc_object_t * object,jsc_int_t start,jsc_int_t end);
    typedef struct jsc_Array_t * (*jsc_String_split_t)(jsc_class_t * isa, jsc_object_t * object,jsc_string_t separator,jsc_int_t limit);
   
    typedef struct jsc_String_class_t {
        jsc_class_t base;
        jsc_String_length_t length;
        jsc_String___index_t __index;
        jsc_String_CString_t CString;
        jsc_String_charAt_t charAt;
        jsc_String_charCodeAt_t charCodeAt;
        jsc_String_codePointAt_t codePointAt;
        jsc_String_concat_t concat;
        jsc_String_indexOf_t indexOf;
        jsc_String_repeat_t repeat;
        jsc_String_replace_t replace;
        jsc_String_slice_t slice;
        jsc_String_split_t split;
    } jsc_String_class_t;

    extern jsc_String_class_t jsc_String;
    
    typedef struct jsc_String_t {
        jsc_object_t base;
        jsc_string_t _CString;
        jsc_unichar_t * _UString;
        jsc_int_t _length;
        jsc_boolean_t _CStringNotFree;
    } jsc_String_t;

    jsc_int_t jsc_String_length_(jsc_class_t * isa, jsc_object_t * object);
    jsc_unichar_t jsc_String___index_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index);
    jsc_string_t jsc_String_CString_(jsc_class_t * isa, jsc_object_t * object);
    jsc_unichar_t jsc_String_charAt_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index);
    jsc_int_t jsc_String_charCodeAt_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index);
    jsc_int_t jsc_String_codePointAt_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t index);
    struct jsc_String_t * jsc_String_concat_(jsc_class_t * isa, jsc_object_t * object,jsc_string_t s);
    jsc_int_t jsc_String_indexOf_(jsc_class_t * isa, jsc_object_t * object,jsc_string_t s);
    struct jsc_String_t * jsc_String_repeat_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t n);
    struct jsc_String_t * jsc_String_replace_(jsc_class_t * isa, jsc_object_t * object,jsc_string_t substr,jsc_string_t newSubstr);
    struct jsc_String_t * jsc_String_slice_(jsc_class_t * isa, jsc_object_t * object,jsc_int_t start,jsc_int_t end);
    struct jsc_Array_t * jsc_String_split_(jsc_class_t * isa, jsc_object_t * object,jsc_string_t separator,jsc_int_t limit);

    jsc_int_t jsc_String_length(jsc_object_t * object);
    jsc_unichar_t jsc_String___index(jsc_object_t * object,jsc_int_t index);
    jsc_string_t jsc_String_CString(jsc_object_t * object);
    jsc_unichar_t jsc_String_charAt(jsc_object_t * object,jsc_int_t index);
    jsc_int_t jsc_String_charCodeAt(jsc_object_t * object,jsc_int_t index);
    jsc_int_t jsc_String_codePointAt(jsc_object_t * object,jsc_int_t index);
    struct jsc_String_t * jsc_String_concat(jsc_object_t * object,jsc_string_t s);
    jsc_int_t jsc_String_indexOf(jsc_object_t * object,jsc_string_t s);
    struct jsc_String_t * jsc_String_repeat(jsc_object_t * object,jsc_int_t n);
    struct jsc_String_t * jsc_String_replace(jsc_object_t * object,jsc_string_t substr,jsc_string_t newSubstr);
    struct jsc_String_t * jsc_String_slice(jsc_object_t * object,jsc_int_t start,jsc_int_t end);
    struct jsc_Array_t * jsc_String_split(jsc_object_t * object,jsc_string_t separator,jsc_int_t limit);

    struct jsc_String_t * jsc_String_allocCString(jsc_string_t s);
    struct jsc_String_t * jsc_String_allocConstCString(jsc_string_t s);
    struct jsc_String_t * jsc_String_allocUTF8String(jsc_string_t s,jsc_int_t length);
    struct jsc_String_t * jsc_String_allocUString(jsc_unichar_t * s, jsc_int_t length);
    struct jsc_String_t * jsc_String_allocFormat(jsc_string_t format,...);
    struct jsc_String_t * jsc_String_newCString(jsc_string_t s);
    struct jsc_String_t * jsc_String_newConstCString(jsc_string_t s);
    struct jsc_String_t * jsc_String_newUTF8String(jsc_string_t s,jsc_int_t length);
    struct jsc_String_t * jsc_String_newUString(jsc_unichar_t * s, jsc_int_t length);
    struct jsc_String_t * jsc_String_newFormat(jsc_string_t format,...);

    size_t jsc_String_iconv(jsc_string_t toCharset,jsc_string_t fromCharset, jsc_byte_t * inBytes,size_t inLen,struct jsc_buffer_t * dst);
    
    jsc_long_t jsc_string_compare(jsc_string_t a,jsc_string_t b);
    
    struct jsc_String_t * jsc_string_concat(jsc_string_t a,jsc_string_t b);

    

#ifdef __cplusplus
}
#endif

#endif /* jsc_String_h */
