//
//  jsc_buffer.h
//  jsc
//
//  Created by 张海龙 on 2022/1/18.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#ifndef jsc_buffer_h
#define jsc_buffer_h

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct jsc_buffer_t {
        jsc_byte_t _buf[2048];
        jsc_byte_t * data;
        size_t length;
        size_t size;
    } jsc_buffer_t;

    void jsc_buffer_init(jsc_buffer_t * buffer);

    void jsc_buffer_destory(jsc_buffer_t * buffer);

    void jsc_buffer_capacity(jsc_buffer_t * buffer, size_t length);

    void jsc_buffer_append(jsc_buffer_t * buffer, const void * data, size_t size);

    jsc_string_t jsc_buffer_formatv(jsc_buffer_t * buffer, jsc_string_t format, va_list ap, size_t size);

    jsc_string_t jsc_buffer_format(jsc_buffer_t * buffer, jsc_string_t format, ... );

    void jsc_buffer_drain(jsc_buffer_t * buffer,size_t length);

    void jsc_buffer_setlength(jsc_buffer_t * buffer,size_t length);

    typedef struct _jsc_range_t {
        size_t location;
        size_t length;
    } jsc_range_t;

    jsc_range_t jsc_buffer_add(jsc_buffer_t * buffer,const jsc_byte_t * data,size_t size);

    jsc_range_t jsc_buffer_add_formatv(jsc_buffer_t * buffer, jsc_string_t format, va_list ap, size_t size);

    jsc_range_t jsc_buffer_add_format(jsc_buffer_t * buffer,jsc_string_t format, ...);

    jsc_ptr_t jsc_buffer_ptr(jsc_buffer_t * buffer,jsc_range_t v);

    jsc_string_t jsc_buffer_string(jsc_buffer_t * buffer,jsc_range_t v);

#ifdef __cplusplus
}
#endif


#endif /* jsc_Buffer_h */
