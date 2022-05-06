#include "jsc.h"
#include "net.h"

/* var implemented */
jsc_int_t jsc_net_AF_INET = 0;
jsc_int_t jsc_net_AF_INET6 = 0;
jsc_int_t jsc_net_AF_UNIX = 0;
jsc_int_t jsc_net_EV_READ = 0;
jsc_int_t jsc_net_EV_WRITE = 0;
jsc_int_t jsc_net_SOCK_STREAM = 0;
jsc_int_t jsc_net_SOCK_DGRAM = 0;
jsc_int_t jsc_net_SOCK_RAW = 0;

/* class implemented */
static void _jsc_Socket_alloc(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_Socket_dealloc(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_int_t _jsc_Socket_bind(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr);
static jsc_int_t _jsc_Socket_connect(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr);
static jsc_int_t _jsc_Socket_listen(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t block);
static jsc_object_t * _jsc_Socket_accept(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr);
static jsc_int_t _jsc_Socket_nonblock(jsc_class_t * __isa, jsc_object_t * __object, jsc_boolean_t v);
static jsc_int_t _jsc_Socket_keepalive(jsc_class_t * __isa, jsc_object_t * __object, jsc_boolean_t enabled, jsc_int_t idle, jsc_int_t interval, jsc_int_t count);
static jsc_int_t _jsc_Socket_broadcast(jsc_class_t * __isa, jsc_object_t * __object, jsc_boolean_t v);
static jsc_int_t _jsc_Socket_bufsize(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t recvbuf, jsc_int_t sendbuf);
static jsc_int_t _jsc_Socket_select(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t types, jsc_int_t tv);
static jsc_int_t _jsc_Socket_send(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * data);
static jsc_int_t _jsc_Socket_recv(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * data);
static jsc_int_t _jsc_Socket_sendto(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr, jsc_object_t * data);
static jsc_int_t _jsc_Socket_recvfrom(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr, jsc_object_t * data);
static jsc_int_t _jsc_Socket_fd(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_boolean_t _jsc_Socket_valid(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_object_t * _jsc_Socket_addr(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_Socket_close(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_Socket_alloc(jsc_class_t * __isa, jsc_object_t * __object) {}
static void _jsc_Socket_dealloc(jsc_class_t * __isa, jsc_object_t * __object) {
}
jsc_net_Socket_class_t jsc_net_Socket = {{(jsc_class_t *)&jsc_Object,sizeof(jsc_net_Socket_t),"net_Socket",_jsc_Socket_alloc,_jsc_Socket_dealloc,NULL,NULL,NULL,NULL,NULL,NULL},_jsc_Socket_bind,_jsc_Socket_connect,_jsc_Socket_listen,_jsc_Socket_accept,_jsc_Socket_nonblock,_jsc_Socket_keepalive,_jsc_Socket_broadcast,_jsc_Socket_bufsize,_jsc_Socket_select,_jsc_Socket_send,_jsc_Socket_recv,_jsc_Socket_sendto,_jsc_Socket_recvfrom,_jsc_Socket_fd,_jsc_Socket_valid,_jsc_Socket_addr,_jsc_Socket_close};
jsc_int_t jsc_net_Socket_bind_(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_net_Socket)) {
        jsc_net_Socket_class_t * s = (jsc_net_Socket_class_t *) __isa;
        if(s->bind) {
            return (*s->bind)(__isa,__object,addr);
        } else {
            return jsc_net_Socket_bind_(__isa->isa,__object,addr);
        }
    }

    return 0;
}
jsc_int_t jsc_net_Socket_bind(jsc_object_t * __object, jsc_object_t * addr) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_net_Socket_bind_(__object->isa,__object,addr);
}

jsc_int_t jsc_net_Socket_connect_(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_net_Socket)) {
        jsc_net_Socket_class_t * s = (jsc_net_Socket_class_t *) __isa;
        if(s->connect) {
            return (*s->connect)(__isa,__object,addr);
        } else {
            return jsc_net_Socket_connect_(__isa->isa,__object,addr);
        }
    }

    return 0;
}
jsc_int_t jsc_net_Socket_connect(jsc_object_t * __object, jsc_object_t * addr) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_net_Socket_connect_(__object->isa,__object,addr);
}

jsc_int_t jsc_net_Socket_listen_(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t block) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_net_Socket)) {
        jsc_net_Socket_class_t * s = (jsc_net_Socket_class_t *) __isa;
        if(s->listen) {
            return (*s->listen)(__isa,__object,block);
        } else {
            return jsc_net_Socket_listen_(__isa->isa,__object,block);
        }
    }

    return 0;
}
jsc_int_t jsc_net_Socket_listen(jsc_object_t * __object, jsc_int_t block) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_net_Socket_listen_(__object->isa,__object,block);
}

jsc_object_t * jsc_net_Socket_accept_(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr) {
	if(__isa == NULL || __object == NULL) {
        return NULL;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_net_Socket)) {
        jsc_net_Socket_class_t * s = (jsc_net_Socket_class_t *) __isa;
        if(s->accept) {
            return (*s->accept)(__isa,__object,addr);
        } else {
            return jsc_net_Socket_accept_(__isa->isa,__object,addr);
        }
    }

    return NULL;
}
jsc_object_t * jsc_net_Socket_accept(jsc_object_t * __object, jsc_object_t * addr) {
	if(__object == NULL) {
        return NULL;
    }
    return jsc_net_Socket_accept_(__object->isa,__object,addr);
}

jsc_int_t jsc_net_Socket_nonblock_(jsc_class_t * __isa, jsc_object_t * __object, jsc_boolean_t v) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_net_Socket)) {
        jsc_net_Socket_class_t * s = (jsc_net_Socket_class_t *) __isa;
        if(s->nonblock) {
            return (*s->nonblock)(__isa,__object,v);
        } else {
            return jsc_net_Socket_nonblock_(__isa->isa,__object,v);
        }
    }

    return 0;
}
jsc_int_t jsc_net_Socket_nonblock(jsc_object_t * __object, jsc_boolean_t v) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_net_Socket_nonblock_(__object->isa,__object,v);
}

jsc_int_t jsc_net_Socket_keepalive_(jsc_class_t * __isa, jsc_object_t * __object, jsc_boolean_t enabled, jsc_int_t idle, jsc_int_t interval, jsc_int_t count) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_net_Socket)) {
        jsc_net_Socket_class_t * s = (jsc_net_Socket_class_t *) __isa;
        if(s->keepalive) {
            return (*s->keepalive)(__isa,__object,enabled,idle,interval,count);
        } else {
            return jsc_net_Socket_keepalive_(__isa->isa,__object,enabled,idle,interval,count);
        }
    }

    return 0;
}
jsc_int_t jsc_net_Socket_keepalive(jsc_object_t * __object, jsc_boolean_t enabled, jsc_int_t idle, jsc_int_t interval, jsc_int_t count) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_net_Socket_keepalive_(__object->isa,__object,enabled,idle,interval,count);
}

jsc_int_t jsc_net_Socket_broadcast_(jsc_class_t * __isa, jsc_object_t * __object, jsc_boolean_t v) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_net_Socket)) {
        jsc_net_Socket_class_t * s = (jsc_net_Socket_class_t *) __isa;
        if(s->broadcast) {
            return (*s->broadcast)(__isa,__object,v);
        } else {
            return jsc_net_Socket_broadcast_(__isa->isa,__object,v);
        }
    }

    return 0;
}
jsc_int_t jsc_net_Socket_broadcast(jsc_object_t * __object, jsc_boolean_t v) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_net_Socket_broadcast_(__object->isa,__object,v);
}

jsc_int_t jsc_net_Socket_bufsize_(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t recvbuf, jsc_int_t sendbuf) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_net_Socket)) {
        jsc_net_Socket_class_t * s = (jsc_net_Socket_class_t *) __isa;
        if(s->bufsize) {
            return (*s->bufsize)(__isa,__object,recvbuf,sendbuf);
        } else {
            return jsc_net_Socket_bufsize_(__isa->isa,__object,recvbuf,sendbuf);
        }
    }

    return 0;
}
jsc_int_t jsc_net_Socket_bufsize(jsc_object_t * __object, jsc_int_t recvbuf, jsc_int_t sendbuf) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_net_Socket_bufsize_(__object->isa,__object,recvbuf,sendbuf);
}

jsc_int_t jsc_net_Socket_select_(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t types, jsc_int_t tv) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_net_Socket)) {
        jsc_net_Socket_class_t * s = (jsc_net_Socket_class_t *) __isa;
        if(s->select) {
            return (*s->select)(__isa,__object,types,tv);
        } else {
            return jsc_net_Socket_select_(__isa->isa,__object,types,tv);
        }
    }

    return 0;
}
jsc_int_t jsc_net_Socket_select(jsc_object_t * __object, jsc_int_t types, jsc_int_t tv) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_net_Socket_select_(__object->isa,__object,types,tv);
}

jsc_int_t jsc_net_Socket_send_(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * data) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_net_Socket)) {
        jsc_net_Socket_class_t * s = (jsc_net_Socket_class_t *) __isa;
        if(s->send) {
            return (*s->send)(__isa,__object,data);
        } else {
            return jsc_net_Socket_send_(__isa->isa,__object,data);
        }
    }

    return 0;
}
jsc_int_t jsc_net_Socket_send(jsc_object_t * __object, jsc_object_t * data) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_net_Socket_send_(__object->isa,__object,data);
}

jsc_int_t jsc_net_Socket_recv_(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * data) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_net_Socket)) {
        jsc_net_Socket_class_t * s = (jsc_net_Socket_class_t *) __isa;
        if(s->recv) {
            return (*s->recv)(__isa,__object,data);
        } else {
            return jsc_net_Socket_recv_(__isa->isa,__object,data);
        }
    }

    return 0;
}
jsc_int_t jsc_net_Socket_recv(jsc_object_t * __object, jsc_object_t * data) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_net_Socket_recv_(__object->isa,__object,data);
}

jsc_int_t jsc_net_Socket_sendto_(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr, jsc_object_t * data) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_net_Socket)) {
        jsc_net_Socket_class_t * s = (jsc_net_Socket_class_t *) __isa;
        if(s->sendto) {
            return (*s->sendto)(__isa,__object,addr,data);
        } else {
            return jsc_net_Socket_sendto_(__isa->isa,__object,addr,data);
        }
    }

    return 0;
}
jsc_int_t jsc_net_Socket_sendto(jsc_object_t * __object, jsc_object_t * addr, jsc_object_t * data) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_net_Socket_sendto_(__object->isa,__object,addr,data);
}

jsc_int_t jsc_net_Socket_recvfrom_(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr, jsc_object_t * data) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_net_Socket)) {
        jsc_net_Socket_class_t * s = (jsc_net_Socket_class_t *) __isa;
        if(s->recvfrom) {
            return (*s->recvfrom)(__isa,__object,addr,data);
        } else {
            return jsc_net_Socket_recvfrom_(__isa->isa,__object,addr,data);
        }
    }

    return 0;
}
jsc_int_t jsc_net_Socket_recvfrom(jsc_object_t * __object, jsc_object_t * addr, jsc_object_t * data) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_net_Socket_recvfrom_(__object->isa,__object,addr,data);
}

jsc_int_t jsc_net_Socket_fd_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_net_Socket)) {
        jsc_net_Socket_class_t * s = (jsc_net_Socket_class_t *) __isa;
        if(s->fd) {
            return (*s->fd)(__isa,__object);
        } else {
            return jsc_net_Socket_fd_(__isa->isa,__object);
        }
    }

    return 0;
}
jsc_int_t jsc_net_Socket_fd(jsc_object_t * __object) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_net_Socket_fd_(__object->isa,__object);
}

jsc_boolean_t jsc_net_Socket_valid_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_net_Socket)) {
        jsc_net_Socket_class_t * s = (jsc_net_Socket_class_t *) __isa;
        if(s->valid) {
            return (*s->valid)(__isa,__object);
        } else {
            return jsc_net_Socket_valid_(__isa->isa,__object);
        }
    }

    return 0;
}
jsc_boolean_t jsc_net_Socket_valid(jsc_object_t * __object) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_net_Socket_valid_(__object->isa,__object);
}

jsc_object_t * jsc_net_Socket_addr_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return NULL;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_net_Socket)) {
        jsc_net_Socket_class_t * s = (jsc_net_Socket_class_t *) __isa;
        if(s->addr) {
            return (*s->addr)(__isa,__object);
        } else {
            return jsc_net_Socket_addr_(__isa->isa,__object);
        }
    }

    return NULL;
}
jsc_object_t * jsc_net_Socket_addr(jsc_object_t * __object) {
	if(__object == NULL) {
        return NULL;
    }
    return jsc_net_Socket_addr_(__object->isa,__object);
}

void jsc_net_Socket_close_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_net_Socket)) {
        jsc_net_Socket_class_t * s = (jsc_net_Socket_class_t *) __isa;
        if(s->close) {
            (*s->close)(__isa,__object);
        } else {
            jsc_net_Socket_close_(__isa->isa,__object);
        }
    }

    
}
void jsc_net_Socket_close(jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_net_Socket_close_(__object->isa,__object);
}

