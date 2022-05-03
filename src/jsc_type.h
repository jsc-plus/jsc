//
//  jsc_type.h
//  jsc
//
//  Created by 张海龙 on 2022/1/12.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#ifndef jsc_type_h
#define jsc_type_h


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/time.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <zlib.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <dirent.h>
#include <signal.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <assert.h>

#define JSC_ASSERT assert
#define JSC_MALLOC malloc
#define JSC_REALLOC realloc
#define JSC_FREE free

#ifdef AF_LINK
#include <net/if_dl.h>
#endif

#if defined(__APPLE__)

#include <TargetConditionals.h>

#endif

#ifndef MAX
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
    
    /**
     * i
     */
    typedef int jsc_int_t;
    
    /**
     * I
     */
    typedef unsigned int jsc_uint_t;
    
    /**
     * l
     */
    typedef long jsc_long_t;
    
    /**
     * L
     */
    typedef unsigned long jsc_ulong_t;
    
    /**
     * i32
     */
    typedef int jsc_int32_t;
    /**
     * I32
     */
    typedef unsigned int jsc_uint32_t;
    
    /**
     * i16
     */
    typedef short jsc_int16_t;
    /**
     * I16
     */
    typedef unsigned short jsc_uint16_t;
    /**
     * i64
     */
    typedef long long jsc_int64_t;
    /**
     * I64
     */
    typedef unsigned long long jsc_uint64_t;
    /**
     * f32
     */
    typedef float jsc_float32_t;
    /**
     * f64
     */
    typedef double jsc_float64_t;
    
    /**
     * f
     */
    typedef float jsc_float_t;
    /**
     * d
     */
    typedef double jsc_double_t;
    /**
     * z
     */
    typedef char jsc_boolean_t;
    /**
     * s
     */
    typedef const char * jsc_string_t;
    
    /**
     * b
     */
    typedef char jsc_byte_t;
    /**
     * B
     */
    typedef unsigned char jsc_ubyte_t;
    
    /**
     * v
     */
    typedef void jsc_void_t;
    
    /**
     * p
     */
    typedef void * jsc_ptr_t;

    /**
     * U
     */
    typedef unsigned short jsc_unichar_t;

    void jsc_logv(jsc_string_t format,va_list va,size_t n);
    
    void jsc_log(jsc_string_t format, ...);
    
    
#ifdef __cplusplus
}
#endif

#endif /* jsc_type_h */
