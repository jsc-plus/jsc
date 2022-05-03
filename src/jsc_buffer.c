//
//  jsc_Buffer.c
//  jsc
//
//  Created by 张海龙 on 2022/1/18.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#include "jsc_type.h"
#include "jsc_buffer.h"


void jsc_buffer_init(jsc_buffer_t * buffer) {
    memset(buffer,0,sizeof(jsc_buffer_t));
    buffer->data = buffer->_buf;
    buffer->size = sizeof(buffer->_buf);
}

void jsc_buffer_destory(jsc_buffer_t * buffer) {
    if(buffer->data != buffer->_buf) {
        JSC_FREE(buffer->data);
    }
    memset(buffer,0,sizeof(jsc_buffer_t));
}

void jsc_buffer_capacity(jsc_buffer_t * buffer, size_t length) {
    if(buffer->size < length) {
        if(buffer->data == buffer->_buf) {
            buffer->data = (jsc_byte_t *) JSC_MALLOC(length);
            if(buffer->length > 0) {
                memcpy(buffer->data, buffer->_buf, buffer->length);
            }
        } else {
            buffer->data = JSC_REALLOC(buffer->data, length);
        }
        buffer->size = length;
    }
}

void jsc_buffer_append(jsc_buffer_t * buffer, const void * data, size_t size) {
    jsc_buffer_capacity(buffer,buffer->length + size);
    memcpy(buffer->data + buffer->length, data, size);
    buffer->length += size;
}

jsc_string_t jsc_buffer_formatv(jsc_buffer_t * buffer, jsc_string_t format, va_list ap, size_t size) {
    jsc_buffer_capacity(buffer,buffer->length + size + 1);
    size_t n = vsnprintf(buffer->data + buffer->length, buffer->size - buffer->length, format,ap);
    jsc_string_t v = (jsc_string_t) buffer->data + buffer->length;
    buffer->length += n;
    return v;
}

jsc_string_t jsc_buffer_format(jsc_buffer_t * buffer, jsc_string_t format, ... ) {
    va_list ap;
    va_start(ap, format);
    size_t n = vsnprintf(NULL, 0, format, ap);
    va_end(ap);
    va_start(ap, format);
    jsc_string_t v = jsc_buffer_formatv(buffer,format,ap,n);
    va_end(ap);
    return v;
}

void jsc_buffer_drain(jsc_buffer_t * buffer,size_t length) {
    ssize_t n = (ssize_t) buffer->length - (ssize_t) length;
    if(n > 0) {
        memcpy(buffer->data, buffer->data + length, n);
        buffer->length = n;
    } else {
        buffer->length = 0;
    }
}

void jsc_buffer_setlength(jsc_buffer_t * buffer,size_t length) {
    jsc_buffer_capacity(buffer, length);
    buffer->length = length;
}

jsc_range_t jsc_buffer_add(jsc_buffer_t * buffer,const jsc_byte_t * data,size_t size) {
    jsc_range_t b = { buffer->length , 0};
    if(data != NULL && size > 0) {
        b.length = size;
        jsc_buffer_append(buffer, data, b.length);
    }
    return b;
}

jsc_range_t jsc_buffer_add_string(jsc_buffer_t * buffer,jsc_string_t v) {
    jsc_range_t b = { buffer->length , 0};
    if(v != NULL) {
        b.length = strlen(v) + 1;
        jsc_buffer_append(buffer, v, b.length);
    }
    return b;
}

jsc_range_t jsc_buffer_add_formatv(jsc_buffer_t * buffer, jsc_string_t format, va_list ap, size_t size) {
    jsc_range_t b = { buffer->length , 0};
    jsc_buffer_formatv(buffer, format, ap, size);
    jsc_buffer_add(buffer, "\0", 1);
    b.length = buffer->length - b.location;
    return b;
}

jsc_range_t jsc_buffer_add_format(jsc_buffer_t * buffer,jsc_string_t format, ...) {
    va_list ap;
    va_start(ap, format);
    size_t n = vsnprintf(NULL, 0, format, ap);
    va_end(ap);
    va_start(ap, format);
    jsc_range_t v = jsc_buffer_add_formatv(buffer,format,ap,n);
    va_end(ap);
    return v;
}

jsc_ptr_t jsc_buffer_ptr(jsc_buffer_t * buffer,jsc_range_t v) {
    return buffer->data + v.location;
}

jsc_string_t jsc_buffer_string(jsc_buffer_t * buffer,jsc_range_t v) {
    return (jsc_string_t)(buffer->data + v.location);
}


