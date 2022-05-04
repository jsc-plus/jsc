//
//  main.m
//  cli
//
//  Created by 张海龙 on 2022/1/12.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#include "jsc_type.h"
#include "jsc_class.h"
#include "jsc_variant.h"
#include "jsc_buffer.h"
#include "jsc_String.h"
#include "jsc_Number.h"
#include "jsc_Array.h"
#include "jsc_Map.h"
#include "jsc_Set.h"
#include "jsc_Iterator.h"
#include "jsc_ArrayBuffer.h"
#include "jsc_DataView.h"
#include <pthread.h>

static void * test1(void * data) {
    
    jsc_autorelease_pool_begin();
    
    
    {
        // map
        jsc_autorelease_pool_begin();
        
        jsc_object_t * m = jsc_object_new((jsc_class_t *) &jsc_Map, 0);
        
        jsc_Map_set(m, jsc_variant_CString("k1"), jsc_variant_CString("v1"));
        jsc_Map_set(m, jsc_variant_CString("k2"), jsc_variant_CString("v2"));
        jsc_Map_set(m, jsc_variant_CString("k3"), jsc_variant_CString("v3"));
        
        jsc_object_t * i = (jsc_object_t *) jsc_Map_iterator(m);
        
        const struct jsc_IteratorEntity_t * e;
        
        while(i && (e = jsc_Iterator_next(i))) {
            
            jsc_log("key: %s value: %s",e->key.stringValue,e->value.stringValue);
            
        }
        
        jsc_autorelease_pool_end();
    }
    
    {
        // set
        jsc_autorelease_pool_begin();
        
        jsc_object_t * m = jsc_object_new((jsc_class_t *) &jsc_Set, 0);
        
        jsc_Set_add(m, jsc_variant_CString("v1"));
        jsc_Set_add(m, jsc_variant_CString("v2"));
        jsc_Set_add(m, jsc_variant_CString("v3"));
        
        jsc_object_t * i = (jsc_object_t *) jsc_Set_iterator(m);
        
        const struct jsc_IteratorEntity_t * e;
        
        while(i && (e = jsc_Iterator_next(i))) {
            
            jsc_log("value: %s",e->value.stringValue);
            
        }
        
        jsc_autorelease_pool_end();
    }
    
    {
        // array
        jsc_autorelease_pool_begin();
        
        jsc_object_t * m = jsc_object_new((jsc_class_t *) &jsc_Array, 0);
        
        jsc_Array_push(m, jsc_variant_CString("v1"));
        jsc_Array_push(m, jsc_variant_CString("v2"));
        jsc_Array_push(m, jsc_variant_CString("v3"));
        
        jsc_object_t * i = (jsc_object_t *) jsc_Array_iterator(m);
        
        const struct jsc_IteratorEntity_t * e;
        
        while(i && (e = jsc_Iterator_next(i))) {
            
            jsc_log("value: %s",e->value.stringValue);
            
        }
        
        jsc_autorelease_pool_end();
    }
    
    {
        // arraybuffer
        jsc_autorelease_pool_begin();
        
        jsc_ArrayBuffer_t * buffer = jsc_ArrayBuffer_new(2048);
        jsc_DataView_t * view = jsc_DataView_new(buffer, 0, 0);
        
        jsc_DataView_setUint32((jsc_object_t *) view, 0, 0x01020304, 1);
        jsc_DataView_setUint32((jsc_object_t *) view, 4, 0x01020304, 0);
        
        jsc_log("%s",jsc_String_CString((jsc_object_t *) jsc_object_toString((jsc_object_t *) buffer)));
        
        jsc_autorelease_pool_end();
    }
    
    
    
    jsc_object_t * a = jsc_object_new(&jsc_Object, 0);
    jsc_object_t * b = jsc_object_new(&jsc_Object, 0);
    jsc_object_t * c = jsc_object_new(&jsc_Object, 0);
    
    jsc_object_t * A = NULL, * B = NULL , * C = NULL;
    
    jsc_setWeak(&A, a);
    jsc_setWeak(&B, b);
    jsc_setWeak(&C, c);
    
    jsc_autorelease_pool_end();
    
    jsc_log("A: 0x%x",(long) A);
    jsc_log("B: 0x%x",(long) B);
    jsc_log("C: 0x%x",(long) C);
    
    return NULL;
}

#define N 1

int main(int argc, const char * argv[]) {
    
    jsc_initialize();
    
    pthread_t p[N];
    
    for(int i=0;i<N;i++) {
        pthread_create(&p[i], NULL, test1, NULL);
    }
    
    for(int i=0;i<N;i++) {
        pthread_join(p[i], NULL);
    }
    
    return 0;
}
