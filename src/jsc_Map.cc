//
//  jsc_Map.cpp
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
#include "jsc_Map.h"
#include "jsc_Iterator.h"

#include <set>

typedef jsc_IteratorEntity_t jsc_Map_Entry;

class jsc_Map_Entry_Compare {
public:
    bool operator ()(const jsc_Map_Entry * left,const jsc_Map_Entry * right) const {
        return jsc_variant_compare(left->key, right->key) < 0;
    }
};

typedef std::set<jsc_Map_Entry *,jsc_Map_Entry_Compare> jsc_Map_EntrySet;

/* iterator */

typedef struct jsc_MapIterator_t {
    jsc_Iterator_t base;
    jsc_Map_EntrySet * s;
    jsc_Map_EntrySet::iterator i;
} jsc_MapIterator_t;


static const struct jsc_IteratorEntity_t * _jsc_MapIterator_next(jsc_class_t * isa, jsc_object_t * object);

jsc_Iterator_class_t jsc_MapIterator = { {(jsc_class_t *) &jsc_Iterator,sizeof(jsc_MapIterator_t),"MapIterator",
    NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    _jsc_MapIterator_next,
};



/* iterator */

static void _jsc_Map_alloc(struct jsc_class_t * isa, struct jsc_object_t * object);
static void _jsc_Map_dealloc(struct jsc_class_t * isa, struct jsc_object_t * object);


static jsc_int_t _jsc_Map_size(jsc_class_t * isa, jsc_object_t * object);
static struct jsc_variant_t _jsc_Map___index(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key);
static void _jsc_Map___newindex(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key,struct jsc_variant_t value);
static void _jsc_Map_clear(jsc_class_t * isa, jsc_object_t * object);
static void _jsc_Map_del(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key);
static struct jsc_variant_t _jsc_Map_get(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key);
static jsc_boolean_t _jsc_Map_has(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key);
static void _jsc_Map_set(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key,struct jsc_variant_t value);
static struct jsc_Iterator_t * _jsc_Map_iterator(jsc_class_t * isa, jsc_object_t * object);


jsc_Map_class_t jsc_Map = { {&jsc_Object,sizeof(jsc_Map_t),"Map",
    _jsc_Map_alloc,_jsc_Map_dealloc,NULL,NULL,NULL,NULL,NULL,NULL},
    _jsc_Map_size,
    _jsc_Map___index,
    _jsc_Map___newindex,
    _jsc_Map_clear,
    _jsc_Map_del,
    _jsc_Map_get,
    _jsc_Map_has,
    _jsc_Map_set,
    _jsc_Map_iterator,
};

jsc_int_t jsc_Map_size_(jsc_class_t * isa, jsc_object_t * object) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_Map.base)) {
        jsc_Map_class_t * s = (jsc_Map_class_t *) isa;
        if(s->size) {
            return (*s->size)(isa,object);
        } else {
            return jsc_Map_size_(isa->isa,object);
        }
    }

    return 0;
}

struct jsc_variant_t jsc_Map___index_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key) {
    
    if(isa == NULL || object == NULL) {
        return jsc_Nil;
    }
    
    if(jsc_class_isKind(isa, &jsc_Map.base)) {
        jsc_Map_class_t * s = (jsc_Map_class_t *) isa;
        if(s->__index) {
            return (*s->__index)(isa,object,key);
        } else {
            return jsc_Map___index_(isa->isa,object,key);
        }
    }

    return jsc_Nil;
}

void jsc_Map___newindex_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key,struct jsc_variant_t value) {
    
    if(isa == NULL || object == NULL) {
        return;
    }
    
    if(jsc_class_isKind(isa, &jsc_Map.base)) {
        jsc_Map_class_t * s = (jsc_Map_class_t *) isa;
        if(s->__newindex) {
            (*s->__newindex)(isa,object,key,value);
        } else {
            jsc_Map___newindex_(isa->isa,object,key,value);
        }
    }

    return;
}

void jsc_Map_clear_(jsc_class_t * isa, jsc_object_t * object) {
    
    if(isa == NULL || object == NULL) {
        return ;
    }
    
    if(jsc_class_isKind(isa, &jsc_Map.base)) {
        jsc_Map_class_t * s = (jsc_Map_class_t *) isa;
        if(s->clear) {
            (*s->clear)(isa,object);
        } else {
            jsc_Map_clear_(isa->isa,object);
        }
    }

    return ;
}

void jsc_Map_del_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key) {
    if(isa == NULL || object == NULL) {
        return ;
    }
    
    if(jsc_class_isKind(isa, &jsc_Map.base)) {
        jsc_Map_class_t * s = (jsc_Map_class_t *) isa;
        if(s->del) {
            (*s->del)(isa,object,key);
        } else {
            jsc_Map_del_(isa->isa,object,key);
        }
    }

    return ;
}

struct jsc_variant_t jsc_Map_get_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key) {
    if(isa == NULL || object == NULL) {
        return jsc_Nil;
    }
    
    if(jsc_class_isKind(isa, &jsc_Map.base)) {
        jsc_Map_class_t * s = (jsc_Map_class_t *) isa;
        if(s->get) {
            return (*s->get)(isa,object,key);
        } else {
            return jsc_Map_get_(isa->isa,object,key);
        }
    }

    return jsc_Nil;
}

jsc_boolean_t jsc_Map_has_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key) {
    
    if(isa == NULL || object == NULL) {
        return 0;
    }
    
    if(jsc_class_isKind(isa, &jsc_Map.base)) {
        jsc_Map_class_t * s = (jsc_Map_class_t *) isa;
        if(s->has) {
            return (*s->has)(isa,object,key);
        } else {
            return jsc_Map_has_(isa->isa,object,key);
        }
    }

    return 0;
}

void jsc_Map_set_(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key,struct jsc_variant_t value) {
    
    if(isa == NULL || object == NULL) {
        return ;
    }
    
    if(jsc_class_isKind(isa, &jsc_Map.base)) {
        jsc_Map_class_t * s = (jsc_Map_class_t *) isa;
        if(s->set) {
            (*s->set)(isa,object,key,value);
        } else {
            jsc_Map_set_(isa->isa,object,key,value);
        }
    }

    return ;
}

struct jsc_Iterator_t * jsc_Map_iterator_(jsc_class_t * isa, jsc_object_t * object) {
    
    if(isa == NULL || object == NULL) {
        return NULL;
    }
    
    if(jsc_class_isKind(isa, &jsc_Map.base)) {
        jsc_Map_class_t * s = (jsc_Map_class_t *) isa;
        if(s->iterator) {
            return (*s->iterator)(isa,object);
        } else {
            return jsc_Map_iterator_(isa->isa,object);
        }
    }

    return NULL;
    
}

jsc_int_t jsc_Map_size(jsc_object_t * object) {
    if(object == NULL) {
        return 0;
    }
    return jsc_Map_size_(object->isa, object);
}

struct jsc_variant_t jsc_Map___index(jsc_object_t * object,struct jsc_variant_t key) {
    if(object == NULL) {
        return jsc_Nil;
    }
    return jsc_Map___index_(object->isa, object,key);
}

void jsc_Map___newindex(jsc_object_t * object,struct jsc_variant_t key,struct jsc_variant_t value) {
    if(object == NULL) {
        return;
    }
    jsc_Map___newindex_(object->isa, object,key,value);
}

void jsc_Map_clear(jsc_object_t * object) {
    if(object == NULL) {
        return;
    }
    jsc_Map_clear_(object->isa, object);
}

void jsc_Map_del(jsc_object_t * object,struct jsc_variant_t key) {
    if(object == NULL) {
        return;
    }
    jsc_Map_del_(object->isa, object,key);
}

struct jsc_variant_t jsc_Map_get(jsc_object_t * object,struct jsc_variant_t key) {
    if(object == NULL) {
        return jsc_Nil;
    }
    return jsc_Map_get_(object->isa, object,key);
}

jsc_boolean_t jsc_Map_has(jsc_object_t * object,struct jsc_variant_t key) {
    if(object == NULL) {
        return 0;
    }
    return jsc_Map_has_(object->isa, object,key);
}

void jsc_Map_set(jsc_object_t * object,struct jsc_variant_t key,struct jsc_variant_t value) {
    if(object == NULL) {
        return;
    }
    jsc_Map_set_(object->isa, object,key,value);
}

struct jsc_Iterator_t * jsc_Map_iterator(jsc_object_t * object) {
    if(object == NULL) {
        return NULL;
    }
    return jsc_Map_iterator_(object->isa, object);
}


/* implemented */

static void _jsc_Map_alloc(struct jsc_class_t * isa, struct jsc_object_t * object) {
}

static void _jsc_Map_dealloc(struct jsc_class_t * isa, struct jsc_object_t * object) {
    jsc_Map_t * v = (jsc_Map_t *) object;
    jsc_Map_EntrySet * s = (jsc_Map_EntrySet *) v->_internal;
    if(s) {
        jsc_Map_EntrySet::iterator i = s->begin();
        while(i != s->end()) {
            jsc_Map_Entry * e = * i;
            jsc_variant_setStrong(&e->key, jsc_Nil);
            jsc_variant_setStrong(&e->value, jsc_Nil);
            delete e;
            i ++;
        }
        delete s;
    }
}


static jsc_int_t _jsc_Map_size(jsc_class_t * isa, jsc_object_t * object) {
    jsc_Map_t * v = (jsc_Map_t *) object;
    jsc_Map_EntrySet * s = (jsc_Map_EntrySet *) v->_internal;
    if(s) {
        return (jsc_int_t) s->size();
    }
    return 0;
}

static struct jsc_variant_t _jsc_Map___index(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key) {
    return _jsc_Map_get(isa,object,key);
}

static void _jsc_Map___newindex(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key,struct jsc_variant_t value) {
    _jsc_Map_set(isa,object,key,value);
}

static void _jsc_Map_clear(jsc_class_t * isa, jsc_object_t * object) {
    jsc_Map_t * v = (jsc_Map_t *) object;
    jsc_Map_EntrySet * s = (jsc_Map_EntrySet *) v->_internal;
    if(s) {
        delete s;
        v->_internal = NULL;
    }
}

static void _jsc_Map_del(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key) {
    jsc_Map_t * v = (jsc_Map_t *) object;
    jsc_Map_EntrySet * s = (jsc_Map_EntrySet *) v->_internal;
    if(s) {
        jsc_Map_Entry e = {key,jsc_Nil};
        jsc_Map_EntrySet::iterator i = s->find(&e);
        if(i != s->end()) {
            s->erase(i);
        }
    }
}

static struct jsc_variant_t _jsc_Map_get(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key) {
    jsc_Map_t * v = (jsc_Map_t *) object;
    jsc_Map_EntrySet * s = (jsc_Map_EntrySet *) v->_internal;
    if(s) {
        jsc_Map_Entry e = {key,jsc_Nil};
        jsc_Map_EntrySet::iterator i = s->find(&e);
        if(i != s->end()) {
            return (*i)->value;
        }
    }
    return jsc_Nil;
}

static jsc_boolean_t _jsc_Map_has(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key) {
    jsc_Map_t * v = (jsc_Map_t *) object;
    jsc_Map_EntrySet * s = (jsc_Map_EntrySet *) v->_internal;
    if(s) {
        jsc_Map_Entry e = {key,jsc_Nil};
        jsc_Map_EntrySet::iterator i = s->find(&e);
        if(i != s->end()) {
            return 1;
        }
    }
    return 0;
}

static void _jsc_Map_set(jsc_class_t * isa, jsc_object_t * object,struct jsc_variant_t key,struct jsc_variant_t value) {
    jsc_Map_t * v = (jsc_Map_t *) object;
    jsc_Map_EntrySet * s = (jsc_Map_EntrySet *) v->_internal;
    if(s) {
        jsc_Map_Entry e = {key,jsc_Nil};
        jsc_Map_EntrySet::iterator i = s->find(&e);
        if(i != s->end()) {
            jsc_variant_setStrong(&(*i)->value,value);
            return;
        } else {
            jsc_Map_Entry * p = new jsc_Map_Entry({jsc_Nil,jsc_Nil});
            jsc_variant_setStrong(&p->key, key);
            jsc_variant_setStrong(&p->value, value);
            s->insert(p);
        }
    } else {
        s = new jsc_Map_EntrySet();
        v->_internal = s;
        jsc_Map_Entry * p = new jsc_Map_Entry({jsc_Nil,jsc_Nil});
        jsc_variant_setStrong(&p->key, key);
        jsc_variant_setStrong(&p->value, value);
        s->insert(p);
    }
}

static struct jsc_Iterator_t * _jsc_Map_iterator(jsc_class_t * isa, jsc_object_t * object) {
    jsc_Map_t * v = (jsc_Map_t *) object;
    jsc_Map_EntrySet * s = (jsc_Map_EntrySet *) v->_internal;
    if(s) {
        jsc_MapIterator_t * i = (jsc_MapIterator_t *) jsc_object_new((jsc_class_t *) & jsc_MapIterator, 0);
        i->s = s;
        i->i = s->begin();
        return (jsc_Iterator_t *) i;
    }
    return NULL;
}

/* iterator implemented */

static const struct jsc_IteratorEntity_t * _jsc_MapIterator_next(jsc_class_t * isa, jsc_object_t * object) {
    jsc_MapIterator_t * v = (jsc_MapIterator_t *) object;
    if(v->i != v->s->end()) {
        const struct jsc_IteratorEntity_t * entity = *v->i;
        v->i ++;
        return entity;
    }
    return NULL;
}
