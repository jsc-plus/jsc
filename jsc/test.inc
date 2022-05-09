#include "jsc.h"
#include "test.h"
static jsc_object_t * jsc__dir = NULL ;
typedef void (*jsc_closures_declare_0_2_t)(jsc_object_t * __closures);
static void jsc_closures_4(jsc_object_t * __closures);
typedef void (*jsc_A_test_t)(jsc_class_t * __isa,jsc_object_t * __object);
typedef struct jsc_A_class_t {
	jsc_class_t base;
	jsc_A_test_t test;
} jsc_A_class_t;

typedef struct A_t {
	jsc_object_t base;
} jsc_A_t;

static void jsc_A_test_(jsc_class_t * __isa,jsc_object_t * __object);

static void jsc_A_test(jsc_object_t * __object);
typedef void (*jsc_B_test_t)(jsc_class_t * __isa,jsc_object_t * __object);
typedef struct jsc_B_class_t {
	jsc_A_class_t base;
	jsc_B_test_t test;
} jsc_B_class_t;

typedef struct B_t {
	jsc_A_t base;
} jsc_B_t;

static void jsc_B_test_(jsc_class_t * __isa,jsc_object_t * __object);

static void jsc_B_test(jsc_object_t * __object);

/* var implemented */

/* class implemented */
static void _jsc_A_alloc(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_A_dealloc(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_A_test(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_A_alloc(jsc_class_t * __isa, jsc_object_t * __object) {}
static void _jsc_A_dealloc(jsc_class_t * __isa, jsc_object_t * __object) {
}
static jsc_A_class_t jsc_A = {{(jsc_class_t *)&jsc_Object,sizeof(jsc_A_t),"A",_jsc_A_alloc,_jsc_A_dealloc,NULL,NULL,NULL,NULL,NULL,NULL},_jsc_A_test};
static void jsc_A_test_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_A)) {
        jsc_A_class_t * s = (jsc_A_class_t *) __isa;
        if(s->test) {
            (*s->test)(__isa,__object);
        } else {
            jsc_A_test_(__isa->isa,__object);
        }
    }

    
}
static void jsc_A_test(jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_A_test_(__object->isa,__object);
}

static void _jsc_B_alloc(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_B_dealloc(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_B_test(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_B_alloc(jsc_class_t * __isa, jsc_object_t * __object) {}
static void _jsc_B_dealloc(jsc_class_t * __isa, jsc_object_t * __object) {
}
static jsc_B_class_t jsc_B = {{{(jsc_class_t *)&jsc_A,sizeof(jsc_B_t),"B",_jsc_B_alloc,_jsc_B_dealloc,NULL,NULL,NULL,NULL,NULL,NULL},_jsc_B_test},_jsc_B_test};
static void jsc_B_test_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_B)) {
        jsc_B_class_t * s = (jsc_B_class_t *) __isa;
        if(s->test) {
            (*s->test)(__isa,__object);
        } else {
            jsc_B_test_(__isa->isa,__object);
        }
    }

    
}
static void jsc_B_test(jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_B_test_(__object->isa,__object);
}

