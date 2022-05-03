//
//  jsc_Set.cpp
//  jsc
//
//  Created by 张海龙 on 2022/5/3.
//  Copyright © 2022 jsc.plus. All rights reserved.
//

#include "jsc_type.h"
#include "jsc_class.h"
#include "jsc_variant.h"
#include "jsc_buffer.h"
#include "jsc_String.h"
#include "jsc_Number.h"
#include "jsc_Array.h"
#include "jsc_Set.h"
#include "jsc_Iterator.h"

#include <set>

typedef jsc_IteratorEntity_t jsc_Set_Entry;

class jsc_Set_Entry_Compare {
public:
    bool operator ()(const jsc_Set_Entry * left,const jsc_Set_Entry * right) const {
        return jsc_variant_compare(left->value, right->value) < 0;
    }
};

typedef std::set<jsc_Set_Entry *,jsc_Set_Entry_Compare> jsc_Set_EntrySet;

/* iterator */

typedef struct jsc_SetIterator_t {
    jsc_Iterator_t base;
    jsc_Set_EntrySet * s;
    jsc_Set_EntrySet::iterator i;
} jsc_SetIterator_t;


static const struct jsc_IteratorEntity_t * _jsc_SetIterator_next(jsc_class_t * isa, jsc_object_t * object);

jsc_Iterator_class_t jsc_SetIterator = { {(jsc_class_t *) &jsc_Iterator,sizeof(jsc_SetIterator_t),"SetIterator",
    NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    _jsc_SetIterator_next,
};



/* iterator */

static void _jsc_Set_alloc(struct jsc_class_t * isa, struct jsc_object_t * object);
static void _jsc_Set_dealloc(struct jsc_class_t * isa, struct jsc_object_t * object);


static jsc_int_t _jsc_Set_size(jsc_class_t * isa, jsc_object_t * object);
static void _jsc_Set_clear(jsc_class_t * isa, jsc_object_t * object);
static void _jsc_Set_del(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t value);
static jsc_boolean_t _jsc_Set_has(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t value);
static void _jsc_Set_add(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t value);
static struct jsc_Iterator_t * _jsc_Set_iterator(jsc_class_t * isa, jsc_object_t * object);


jsc_Set_class_t jsc_Set = { {&jsc_Object,sizeof(jsc_Set_t),"Set",
    _jsc_Set_alloc,_jsc_Set_dealloc,NULL,NULL,NULL,NULL,NULL,NULL},
    _jsc_Set_size,
    _jsc_Set_clear,
    _jsc_Set_del,
    _jsc_Set_has,
    _jsc_Set_add,
    _jsc_Set_iterator,
};

jsc_int_t jsc_Set_size_(jsc_class_t * isa, jsc_object_t * object) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_Set.base)) {
        jsc_Set_class_t * s = (jsc_Set_class_t *) isa;
        if(s->size) {
            return (*s->size)(isa,object);
        } else {
            return jsc_Set_size_(isa->isa,object);
        }
    }

    return 0;
}

void jsc_Set_clear_(jsc_class_t * isa, jsc_object_t * object) {
    
    if(isa == NULL || object == NULL) {
        return ;
    }
    
    if(jsc_class_isKind(isa, &jsc_Set.base)) {
        jsc_Set_class_t * s = (jsc_Set_class_t *) isa;
        if(s->clear) {
            (*s->clear)(isa,object);
        } else {
            jsc_Set_clear_(isa->isa,object);
        }
    }

    return ;
}

void jsc_Set_del_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t value) {
    if(isa == NULL || object == NULL) {
        return ;
    }
    
    if(jsc_class_isKind(isa, &jsc_Set.base)) {
        jsc_Set_class_t * s = (jsc_Set_class_t *) isa;
        if(s->del) {
            (*s->del)(isa,object,value);
        } else {
            jsc_Set_del_(isa->isa,object,value);
        }
    }

    return ;
}

jsc_boolean_t jsc_Set_has_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t value) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_Set.base)) {
        jsc_Set_class_t * s = (jsc_Set_class_t *) isa;
        if(s->has) {
            return (*s->has)(isa,object,value);
        } else {
            return jsc_Set_has_(isa->isa,object,value);
        }
    }

    return 0;
}

void jsc_Set_add_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t value) {
    
    if(isa == NULL || object == NULL) {
        return ;
    }
    
    if(jsc_class_isKind(isa, &jsc_Set.base)) {
        jsc_Set_class_t * s = (jsc_Set_class_t *) isa;
        if(s->add) {
            (*s->add)(isa,object,value);
        } else {
            jsc_Set_add_(isa->isa,object,value);
        }
    }

    return ;
}

struct jsc_Iterator_t * jsc_Set_iterator_(jsc_class_t * isa, jsc_object_t * object) {
    
    if(isa == NULL || object == NULL) {
        return NULL;
    }
    
    if(jsc_class_isKind(isa, &jsc_Set.base)) {
        jsc_Set_class_t * s = (jsc_Set_class_t *) isa;
        if(s->iterator) {
            return (*s->iterator)(isa,object);
        } else {
            return jsc_Set_iterator_(isa->isa,object);
        }
    }

    return NULL;
    
}

jsc_int_t jsc_Set_size(jsc_object_t * object) {
    if(object == NULL) {
        return 0;
    }
    return jsc_Set_size_(object->isa, object);
}

void jsc_Set_clear(jsc_object_t * object) {
    if(object == NULL) {
        return;
    }
    jsc_Set_clear_(object->isa, object);
}

void jsc_Set_del(jsc_object_t * object,struct jsc_variant_t value) {
    if(object == NULL) {
        return;
    }
    jsc_Set_del_(object->isa, object,value);
}

jsc_boolean_t jsc_Set_has(jsc_object_t * object,struct jsc_variant_t value) {
    if(object == NULL) {
        return 0;
    }
    return jsc_Set_has_(object->isa, object,value);
}

void jsc_Set_add(jsc_object_t * object,struct jsc_variant_t value) {
    if(object == NULL) {
        return;
    }
    jsc_Set_add_(object->isa, object,value);
}

struct jsc_Iterator_t * jsc_Set_iterator(jsc_object_t * object) {
    if(object == NULL) {
        return NULL;
    }
    return jsc_Set_iterator_(object->isa, object);
}


/* implemented */

static void _jsc_Set_alloc(struct jsc_class_t * isa, struct jsc_object_t * object) {
}

static void _jsc_Set_dealloc(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_Set_t * v = (jsc_Set_t *) object;
    jsc_Set_EntrySet * s = (jsc_Set_EntrySet *) v->_internal;
    if(s) {
        jsc_Set_EntrySet::iterator i = s->begin();
        while(i != s->end()) {
            jsc_Set_Entry * e = * i;
            jsc_variant_setStrong(&e->key, jsc_Nil);
            jsc_variant_setStrong(&e->value, jsc_Nil);
            delete e;
            i ++;
        }
        delete s;
    }
}


static jsc_int_t _jsc_Set_size(jsc_class_t * isa, jsc_object_t * object) {
    jsc_Set_t * v = (jsc_Set_t *) object;
    jsc_Set_EntrySet * s = (jsc_Set_EntrySet *) v->_internal;
    if(s) {
        return (jsc_int_t) s->size();
    }
    return 0;
}

static void _jsc_Set_clear(jsc_class_t * isa, jsc_object_t * object) {
    jsc_Set_t * v = (jsc_Set_t *) object;
    jsc_Set_EntrySet * s = (jsc_Set_EntrySet *) v->_internal;
    if(s) {
        delete s;
        v->_internal = NULL;
    }
}

static void _jsc_Set_del(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t value) {
    jsc_Set_t * v = (jsc_Set_t *) object;
    jsc_Set_EntrySet * s = (jsc_Set_EntrySet *) v->_internal;
    if(s) {
        jsc_Set_Entry e = {jsc_Nil,value};
        jsc_Set_EntrySet::iterator i = s->find(&e);
        if(i != s->end()) {
            s->erase(i);
        }
    }
}

static jsc_boolean_t _jsc_Set_has(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t value) {
    jsc_Set_t * v = (jsc_Set_t *) object;
    jsc_Set_EntrySet * s = (jsc_Set_EntrySet *) v->_internal;
    if(s) {
        jsc_Set_Entry e = {jsc_Nil,value};
        jsc_Set_EntrySet::iterator i = s->find(&e);
        if(i != s->end()) {
            return 1;
        }
    }
    return 0;
}

static void _jsc_Set_add(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t value) {
    jsc_Set_t * v = (jsc_Set_t *) object;
    jsc_Set_EntrySet * s = (jsc_Set_EntrySet *) v->_internal;
    if(s) {
        jsc_Set_Entry e = {jsc_Nil,value};
        jsc_Set_EntrySet::iterator i = s->find(&e);
        if(i != s->end()) {
            jsc_variant_setStrong(&(*i)->value,value);
            return;
        } else {
            jsc_Set_Entry * p = new jsc_Set_Entry({jsc_Nil,jsc_Nil});
            jsc_variant_setStrong(&p->value, value);
            s->insert(p);
        }
    } else {
        s = new jsc_Set_EntrySet();
        v->_internal = s;
        jsc_Set_Entry * p = new jsc_Set_Entry({jsc_Nil,jsc_Nil});
        jsc_variant_setStrong(&p->value, value);
        s->insert(p);
    }
}

static struct jsc_Iterator_t * _jsc_Set_iterator(jsc_class_t * isa, jsc_object_t * object) {
    jsc_Set_t * v = (jsc_Set_t *) object;
    jsc_Set_EntrySet * s = (jsc_Set_EntrySet *) v->_internal;
    if(s) {
        jsc_SetIterator_t * i = (jsc_SetIterator_t *) jsc_object_new((jsc_class_t *) & jsc_SetIterator, 0);
        i->s = s;
        i->i = s->begin();
        return (jsc_Iterator_t *) i;
    }
    return NULL;
}

/* iterator implemented */

static const struct jsc_IteratorEntity_t * _jsc_SetIterator_next(jsc_class_t * isa, jsc_object_t * object) {
    jsc_SetIterator_t * v = (jsc_SetIterator_t *) object;
    if(v->i != v->s->end()) {
        const struct jsc_IteratorEntity_t * entity = *v->i;
        v->i ++;
        return entity;
    }
    return NULL;
}

