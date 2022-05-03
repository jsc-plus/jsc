//
//  jsc_log_libc.c
//  jsc
//
//  Created by 张海龙 on 2022/1/12.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#include "jsc_type.h"

void jsc_logv(jsc_string_t format,va_list va, size_t length) {
    
    time_t now = time(NULL);
    
    char data[4096];
    
    struct tm * p = localtime(&now);
    
    size_t n = snprintf(data,sizeof(data), "[JSC] [%04d-%02d-%02d %02d:%02d:%02d] ",1900 + p->tm_year,p->tm_mon + 1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
    
    n += vsnprintf(data + n, sizeof(data) - n ,format, va);
    
    printf("%s\n",data);
    
}

