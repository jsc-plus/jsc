#include "jsc.h"
#include "test.h"
typedef void (*jsc_A_A_t)(jsc_class_t * __isa,jsc_object_t * __object);
typedef struct jsc_A_class_t {
	jsc_class_t base;
	jsc_A_A_t A;
} jsc_A_class_t;

typedef struct A_t {
	jsc_object_t base;
} jsc_A_t;

void jsc_A_A_(jsc_class_t * __isa,jsc_object_t * __object);

void jsc_A_A(jsc_object_t * __object);
typedef void (*jsc_B_B_t)(jsc_class_t * __isa,jsc_object_t * __object);
typedef struct jsc_B_class_t {
	jsc_A_class_t base;
	jsc_B_B_t B;
} jsc_B_class_t;

typedef struct B_t {
	jsc_A_t base;
} jsc_B_t;

void jsc_B_B_(jsc_class_t * __isa,jsc_object_t * __object);

void jsc_B_B(jsc_object_t * __object);

/* function implemented */
void jsc_test_main() {
}

/* class implemented */
static void _jsc_A_alloc(struct jsc_class_t * __isa, struct jsc_object_t * __object);
static void _jsc_A_dealloc(struct jsc_class_t * __isa, struct jsc_object_t * __object);
static void _jsc_A_A(struct jsc_class_t * __isa, struct jsc_object_t * __object);
static void _jsc_A_alloc(struct jsc_class_t * __isa, struct jsc_object_t * __object) {}
static void _jsc_A_dealloc(struct jsc_class_t * __isa, struct jsc_object_t * __object) {
}
static jsc_A_class_t jsc_A = {{(jsc_class_t *)&jsc_Object,sizeof(jsc_A_t),"A",_jsc_A_alloc,_jsc_A_dealloc,NULL,NULL,NULL,NULL,NULL,NULL},_jsc_A_A};
static void _jsc_A_A(struct jsc_class_t * __isa, struct jsc_object_t * __object) {
	jsc_log("A test");
}
static void jsc_A_A_(struct jsc_class_t * __isa, struct jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_A)) {
        jsc_A_class_t * s = (jsc_A_class_t *) __isa;
        if(s->A) {
            (*s->A)(__isa,__object);
        } else {
            jsc_A_A_(isa->isa,object);
        }
    }

    
}
static void jsc_A_A(struct jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_A_A_(__object->isa,__object);
}

static void _jsc_B_alloc(struct jsc_class_t * __isa, struct jsc_object_t * __object);
static void _jsc_B_dealloc(struct jsc_class_t * __isa, struct jsc_object_t * __object);
static void _jsc_B_B(struct jsc_class_t * __isa, struct jsc_object_t * __object);
static void _jsc_B_alloc(struct jsc_class_t * __isa, struct jsc_object_t * __object) {}
static void _jsc_B_dealloc(struct jsc_class_t * __isa, struct jsc_object_t * __object) {
}
static jsc_B_class_t jsc_B = {{{(jsc_class_t *)&jsc_A,sizeof(jsc_B_t),"B",_jsc_B_alloc,_jsc_B_dealloc,NULL,NULL,NULL,NULL,NULL,NULL},NULL},_jsc_B_B};
static void _jsc_B_B(struct jsc_class_t * __isa, struct jsc_object_t * __object) {
	jsc_A_test_((jsc_class_t *)&jsc_A,__object);
	jsc_log("B test");
}
static void jsc_B_B_(struct jsc_class_t * __isa, struct jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_B)) {
        jsc_B_class_t * s = (jsc_B_class_t *) __isa;
        if(s->B) {
            (*s->B)(__isa,__object);
        } else {
            jsc_B_B_(isa->isa,object);
        }
    }

    
}
static void jsc_B_B(struct jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_B_B_(__object->isa,__object);
}

