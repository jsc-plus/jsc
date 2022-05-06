#include "jsc_type.h"
#include "jsc_class.h"
#include "jsc_variant.h"
#include "jsc_buffer.h"
#include "jsc_ArrayBuffer.h"
#include "jsc_DataView.h"
#include "jsc_String.h"
#include "jsc_net.h"
#include "jsc_net.inc"
#include <sys/socket.h>
#include <sys/un.h>
#include <ifaddrs.h>

/* var implemented */
jsc_int_t jsc_net_AF_INET = AF_INET;
jsc_int_t jsc_net_AF_INET6 = AF_INET6;
jsc_int_t jsc_net_AF_UNIX = AF_UNIX;
jsc_int_t jsc_net_EV_READ = 1 << 1;
jsc_int_t jsc_net_EV_WRITE = 1 << 2;
jsc_int_t jsc_net_SOCK_STREAM = SOCK_STREAM;
jsc_int_t jsc_net_SOCK_DGRAM = SOCK_DGRAM;
jsc_int_t jsc_net_SOCK_RAW = SOCK_RAW;

static jsc_object_t * jsc_net_createSocket_fd(jsc_int_t fd,jsc_int_t family, jsc_int_t type, jsc_int_t protocol);


/* class implemented */
static jsc_int_t _jsc_Socket_bind(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr) {
    
    jsc_net_Socket_t * s = (jsc_net_Socket_t *) __object;
    
    if(s->_fd == -1) {
        return -1;
    }
    
    if(addr == NULL || !jsc_class_isKind(addr->isa, (jsc_class_t *) &jsc_ArrayBuffer)) {
        return -1;
    }
    
    jsc_ArrayBuffer_t * v = (jsc_ArrayBuffer_t *) addr;
    
    struct sockaddr * a = (struct sockaddr *) v->_data;
    
    if(a->sa_family == AF_INET) {
        return bind(s->_fd, a, sizeof(struct sockaddr_in));
    } else if(a->sa_family == AF_INET6) {
        return bind(s->_fd, a, sizeof(struct sockaddr_in6));
    } else if(a->sa_family == AF_UNIX) {
        return bind(s->_fd, a, sizeof(struct sockaddr_un));
    }
    
    return -1;
}

static jsc_int_t _jsc_Socket_connect(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr) {
    
    jsc_net_Socket_t * s = (jsc_net_Socket_t *) __object;
    
    if(s->_fd == -1) {
        return -1;
    }
    
    if(addr == NULL || !jsc_class_isKind(addr->isa, (jsc_class_t *) &jsc_ArrayBuffer)) {
        return -1;
    }
    
    jsc_ArrayBuffer_t * v = (jsc_ArrayBuffer_t *) addr;
    
    struct sockaddr * a = (struct sockaddr *) v->_data;

    jsc_int_t r = -1;
    
    if(a->sa_family == AF_INET) {
        r = connect(s->_fd, a, sizeof(struct sockaddr_in));
        if(r == -1 && errno == EINPROGRESS) {
            r = -2;
        }
    } else if(a->sa_family == AF_INET6) {
        r = connect(s->_fd, a, sizeof(struct sockaddr_in6));
        if(r == -1 && errno == EINPROGRESS) {
            r = -2;
        }
    } else if(a->sa_family == AF_UNIX) {
        r = connect(s->_fd, a, sizeof(struct sockaddr_un));
        if(r == -1 && errno == EINPROGRESS) {
            r = -2;
        }
    }
    
    return r;
}

static jsc_int_t _jsc_Socket_listen(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t block) {
    
    jsc_net_Socket_t * s = (jsc_net_Socket_t *) __object;
    
    if(s->_fd == -1) {
        return -1;
    }
    
    return listen(s->_fd, block);
}

static jsc_object_t * _jsc_Socket_accept(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr) {
    
    jsc_net_Socket_t * s = (jsc_net_Socket_t *) __object;
    
    if(s->_fd == -1) {
        return NULL;
    }
    
    if(addr == NULL || !jsc_class_isKind(addr->isa, (jsc_class_t *) &jsc_ArrayBuffer)) {
        return NULL;
    }
    
    jsc_ArrayBuffer_t * v = (jsc_ArrayBuffer_t *) addr;
    
    socklen_t len = v->_byteLength;
    struct sockaddr * a = (struct sockaddr *) v->_data;
    
    jsc_int_t r = accept(s->_fd, a, &len);
    
    if(r > 0) {
        return jsc_net_createSocket_fd(r, 0, 0, 0);
    }
    
	return NULL;
}

static jsc_int_t _jsc_Socket_nonblock(jsc_class_t * __isa, jsc_object_t * __object, jsc_boolean_t v) {
    
    jsc_net_Socket_t * ss = (jsc_net_Socket_t *) __object;
    
    if(ss->_fd == -1) {
        return -1;
    }
    
    if(v) {
        
        int s = fcntl(ss->_fd,F_GETFL,0);
        
        if(s == -1) {
            return -1;
        }
        
        s = s | O_NONBLOCK;
        
        if(fcntl(ss->_fd,F_SETFL,s) == -1) {
            return -1;
        }
        
    } else {
        
        int s = fcntl(ss->_fd,F_GETFL,0);
        
        if(s == -1) {
            return -1;
        }
    
        s = s & (~O_NONBLOCK);
        
        if(fcntl(ss->_fd,F_SETFL,s) == -1) {
            return -1;
        }
        
    }
    
	return 0;
}
static jsc_int_t _jsc_Socket_keepalive(jsc_class_t * __isa, jsc_object_t * __object, jsc_boolean_t enabled, jsc_int_t idle, jsc_int_t interval, jsc_int_t count) {
    
    jsc_net_Socket_t * ss = (jsc_net_Socket_t *) __object;
    
    if(ss->_fd == -1) {
        return -1;
    }
    
    if(-1 == setsockopt(ss->_fd, SOL_SOCKET, SO_KEEPALIVE, (void *)&enabled , sizeof(enabled ))) {
        return -1;
    }

#if defined(__APPLE__)
    if(-1 == setsockopt(ss->_fd, SOL_SOCKET, TCP_KEEPALIVE, (void *)&idle , sizeof(idle ))) {
        return -1;
    }
#else
    if(-1 == setsockopt(ss->_fd, SOL_SOCKET, TCP_KEEPIDLE, (void *)&idle , sizeof(idle ))) {
        return -1;
    }
#endif

    if(-1 == setsockopt(ss->_fd, SOL_SOCKET, TCP_KEEPINTVL, (void *)&interval , sizeof(interval ))) {
        return -1;
    }
    
    if(-1 == setsockopt(ss->_fd, SOL_SOCKET, TCP_KEEPCNT, (void *)&interval , sizeof(interval ))) {
        return -1;
    }
    
	return 0;
}
static jsc_int_t _jsc_Socket_broadcast(jsc_class_t * __isa, jsc_object_t * __object, jsc_boolean_t v) {
    
    jsc_net_Socket_t * ss = (jsc_net_Socket_t *) __object;
    
    if(ss->_fd == -1) {
        return -1;
    }
    
    int opt = v ? 1 : 0;
    
    return setsockopt(ss->_fd, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));
}
static jsc_int_t _jsc_Socket_bufsize(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t recvbuf, jsc_int_t sendbuf) {
    
    jsc_net_Socket_t * ss = (jsc_net_Socket_t *) __object;
    
    if(ss->_fd == -1) {
        return -1;
    }
    
    int r = setsockopt(ss->_fd,SOL_SOCKET, SO_RCVBUF, &recvbuf, sizeof(jsc_int_t));
    
    if(r == -1) {
        return -1;
    }
    
    r = setsockopt(ss->_fd,SOL_SOCKET, SO_SNDBUF, &recvbuf, sizeof(jsc_int_t));
    
    return r;
    
}

static jsc_int_t _jsc_Socket_select(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t types, jsc_int_t tv) {
    
    jsc_net_Socket_t * ss = (jsc_net_Socket_t *) __object;
    
    if(ss->_fd == -1 || types == 0) {
        return -1;
    }

    fd_set rd, * prd = NULL;
    fd_set wd, * pwd = NULL;
    
    FD_ZERO(&rd);
    FD_ZERO(&wd);
    
    if((types & jsc_net_EV_READ) != 0) {
        FD_SET(ss->_fd,&rd);
        prd = &rd;
    }
    
    if((types & jsc_net_EV_WRITE) != 0) {
        FD_SET(ss->_fd,&wd);
        pwd = &wd;
    }
    
    if(prd == NULL && pwd == NULL) {
        return -1;
    }
    
    struct timeval t = { tv / 1000, (tv % 1000) * 1000 };
    
    jsc_int_t r = select(ss->_fd + 1, prd, pwd, NULL, &t);
    
    if(r > 0) {
        jsc_int_t ev = 1;
        if(FD_ISSET(ss->_fd,&rd)) {
            ev = ev | jsc_net_EV_READ;
        }
        if(FD_ISSET(ss->_fd,&wd)) {
            ev = ev | jsc_net_EV_WRITE;
        }
        return ev;
    }
    
    return r;
}

static jsc_int_t _jsc_Socket_send(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * data) {
    
    jsc_net_Socket_t * ss = (jsc_net_Socket_t *) __object;
    
    if(ss->_fd == -1) {
        return -1;
    }
    
    if(data == NULL || !jsc_class_isKind(data->isa, (jsc_class_t *) &jsc_DataView)) {
        return 0;
    }
    
    jsc_DataView_t * v = (jsc_DataView_t *) data;
   
    if(!v->_buffer) {
        return 0;
    }
    
    jsc_int_t r = (jsc_int_t) send(ss->_fd, v->_buffer->_data + v->_byteOffset, v->_byteLength, 0);
    
    if(r == -1 && errno == EAGAIN) {
        r = 0;
    }
    
    return r;
}

static jsc_int_t _jsc_Socket_recv(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * data) {
    
    jsc_net_Socket_t * ss = (jsc_net_Socket_t *) __object;
    
    if(ss->_fd == -1) {
        return -1;
    }
    
    if(data == NULL || !jsc_class_isKind(data->isa, (jsc_class_t *) &jsc_DataView)) {
        return 0;
    }
    
    jsc_DataView_t * v = (jsc_DataView_t *) data;
   
    if(!v->_buffer) {
        return 0;
    }
    
    jsc_int_t r = (jsc_int_t) recv(ss->_fd, v->_buffer->_data + v->_byteOffset, v->_byteLength, 0);
    
    if(r == -1 && errno == EAGAIN) {
        r = 0;
    }
    
    return r;
    
}

static jsc_int_t _jsc_Socket_sendto(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr, jsc_object_t * data) {
    
    jsc_net_Socket_t * ss = (jsc_net_Socket_t *) __object;
    
    if(ss->_fd == -1) {
        return -1;
    }
    
    if(addr == NULL || !jsc_class_isKind(addr->isa, (jsc_class_t *) &jsc_ArrayBuffer)) {
        return -1;
    }
    
    if(data == NULL || !jsc_class_isKind(data->isa, (jsc_class_t *) &jsc_DataView)) {
        return 0;
    }
    
    jsc_DataView_t * v = (jsc_DataView_t *) data;
   
    if(!v->_buffer) {
        return 0;
    }
    
    jsc_ArrayBuffer_t * a = (jsc_ArrayBuffer_t *) addr;
    
    struct sockaddr * sa = (struct sockaddr *) a->_data;
    
    jsc_int_t r = (jsc_int_t) sendto(ss->_fd, v->_buffer->_data + v->_byteOffset, v->_byteLength, 0,sa,sa->sa_len);
    
    if(r == -1 && errno == EAGAIN) {
        r = 0;
    }
    
    return r;

}

static jsc_int_t _jsc_Socket_recvfrom(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr, jsc_object_t * data) {
    
    jsc_net_Socket_t * ss = (jsc_net_Socket_t *) __object;
    
    if(ss->_fd == -1) {
        return -1;
    }
    
    if(addr == NULL || !jsc_class_isKind(addr->isa, (jsc_class_t *) &jsc_ArrayBuffer)) {
        return -1;
    }
    
    if(data == NULL || !jsc_class_isKind(data->isa, (jsc_class_t *) &jsc_DataView)) {
        return 0;
    }
    
    jsc_DataView_t * v = (jsc_DataView_t *) data;
   
    if(!v->_buffer) {
        return 0;
    }
    
    jsc_ArrayBuffer_t * a = (jsc_ArrayBuffer_t *) addr;
    
    socklen_t n = v->_byteLength;
    
    jsc_int_t r = (jsc_int_t) recvfrom(ss->_fd, v->_buffer->_data + v->_byteOffset, v->_byteLength, 0, (struct sockaddr *) a->_data,&n);
    
    if(r == -1 && errno == EAGAIN) {
        r = 0;
    }
    
    return r;
}

static jsc_int_t _jsc_Socket_fd(jsc_class_t * __isa, jsc_object_t * __object) {
    jsc_net_Socket_t * ss = (jsc_net_Socket_t *) __object;
    return ss->_fd;
}

#if defined(__APPLE__)
#define tcp_info tcp_connection_info
#define TCP_INFO TCP_CONNECTION_INFO
#endif

#ifndef TCP_ESTABLISHED

#if defined(__RASPBERRYPI__)
#define TCP_ESTABLISHED 1
#elif defined(__ANDROID_API__)
#define TCP_ESTABLISHED 1
#else
#define TCP_ESTABLISHED 4
#endif

#endif

static jsc_boolean_t _jsc_Socket_valid(jsc_class_t * __isa, jsc_object_t * __object) {
    
    jsc_net_Socket_t * ss = (jsc_net_Socket_t *) __object;
    
    if(ss->_fd == -1) {
        return -1;
    }
    
    struct tcp_info info;
    socklen_t len = sizeof(info);
    
    if(getsockopt(ss->_fd, IPPROTO_TCP, TCP_INFO, &info, &len) == -1) {
        return 0;
    }

    return info.tcpi_state == TCP_ESTABLISHED;
}

static jsc_object_t * _jsc_Socket_addr(jsc_class_t * __isa, jsc_object_t * __object) {
    
    jsc_net_Socket_t * ss = (jsc_net_Socket_t *) __object;
    
    if(ss->_fd == -1) {
        return NULL;
    }
    
    jsc_ArrayBuffer_t * addr = (jsc_ArrayBuffer_t *) jsc_net_createAddr(NULL, 0);
    
    socklen_t n = addr->_byteLength;
    
    int r = getsockname(ss->_fd, (struct sockaddr *) addr->_data, &n);
    
    if(r == -1) {
        return NULL;
    }
    
    return (jsc_object_t *) addr;
}

static void _jsc_Socket_close(jsc_class_t * __isa, jsc_object_t * __object) {
    
    jsc_net_Socket_t * ss = (jsc_net_Socket_t *) __object;
    
    if(ss->_fd != -1) {
        close(ss->_fd);
        ss->_fd = -1;
    }
    
}

static void _jsc_Socket_dealloc(jsc_class_t * __isa, jsc_object_t * __object) {
    
    jsc_net_Socket_t * ss = (jsc_net_Socket_t *) __object;
    
    if(ss->_fd != -1) {
        close(ss->_fd);
        ss->_fd = -1;
    }
    
}

/* function implemented */
jsc_object_t * jsc_net_createAddr(jsc_string_t s, jsc_int_t port) {
    jsc_int_t n = sizeof(struct sockaddr_in);
    n = MAX(n,sizeof(struct sockaddr_in6));
    n = MAX(n,sizeof(struct sockaddr_un));
    jsc_ArrayBuffer_t * v = jsc_ArrayBuffer_new(n);
    
    if(s) {
        if(strncmp(s, "unix:", 5) == 0) {
            struct sockaddr_un * a = (struct sockaddr_un *) v->_data;
            a->sun_family = AF_UNIX;
            a->sun_len = sizeof(struct sockaddr_un);
            strncpy(a->sun_path, s,sizeof(a->sun_path)-1);
        } else if(inet_aton(s, &((struct sockaddr_in * )v->_data)->sin_addr)) {
            struct sockaddr_in * a = (struct sockaddr_in *) v->_data;
            a->sin_len = sizeof(struct sockaddr_in);
            a->sin_family = AF_INET;
            a->sin_port = htons(port);
        } else if(inet_pton(AF_INET6,s, v->_data)) {
            struct sockaddr_in6 * a = (struct sockaddr_in6 *) v->_data;
            a->sin6_len = sizeof(struct sockaddr_in6);
            a->sin6_family = AF_INET6;
            a->sin6_port = htons(port);
        } else {
            memset(v->_data,0,v->_byteLength);
        }
    }
    
	return (jsc_object_t *) s;
}


jsc_int_t jsc_net_getAddrFamily(jsc_object_t * s) {
    
    if(s == NULL || !jsc_class_isKind(s->isa, (jsc_class_t *) &jsc_ArrayBuffer)) {
        return 0;
    }
    
    jsc_ArrayBuffer_t * v = (jsc_ArrayBuffer_t *) s;
    
    struct sockaddr * a = (struct sockaddr *) v->_data;
    
	return a->sa_family;
}

jsc_int_t jsc_net_getAddrPort(jsc_object_t * s) {
	
    
    if(s == NULL || !jsc_class_isKind(s->isa, (jsc_class_t *) &jsc_ArrayBuffer)) {
        return 0;
    }
    
    jsc_ArrayBuffer_t * v = (jsc_ArrayBuffer_t *) s;
    
    struct sockaddr * a = (struct sockaddr *) v->_data;
    
    if(a->sa_family == AF_INET) {
        return ntohs(((struct sockaddr_in *) v->_data)->sin_port);
    }
    
    if(a->sa_family == AF_INET6) {
        return ntohs(((struct sockaddr_in6 *) v->_data)->sin6_port);
    }
    
    return 0;
}

jsc_string_t jsc_net_getAddrString(jsc_object_t * s) {
    
    if(s == NULL || !jsc_class_isKind(s->isa, (jsc_class_t *) &jsc_ArrayBuffer)) {
        return NULL;
    }
    
    jsc_ArrayBuffer_t * v = (jsc_ArrayBuffer_t *) s;
    
    struct sockaddr * a = (struct sockaddr *) v->_data;
    
    if(a->sa_family == AF_INET || a->sa_family == AF_INET6) {
        
        char data[128] = "";
        
        jsc_string_t r = inet_ntop(a->sa_family, a,data,(socklen_t) sizeof(data));
        
        if(r) {
            return jsc_String_CString((jsc_object_t *) jsc_String_newCString(r));
        }
        
        return NULL;
    } else if(a->sa_family == AF_UNIX) {
        return ((struct sockaddr_un *) a)->sun_path;
    }
    
	return NULL;
}

jsc_object_t * jsc_net_resolve(jsc_string_t s, jsc_int_t port) {
	
    if(!s ) {
        return NULL;
    }
    
    jsc_ArrayBuffer_t * result = (jsc_ArrayBuffer_t *) jsc_net_createAddr(s,port);
    
    if(jsc_net_getAddrFamily((jsc_object_t *) result)) {
        return (jsc_object_t *) result;
    }
    
    jsc_boolean_t b = 0;
    
    struct addrinfo *res = NULL, *cur;
    int ret;
    struct sockaddr *addr = NULL;
    struct addrinfo hint;
    
    memset(&hint, 0, sizeof(struct addrinfo));
    
    hint.ai_flags = AI_ADDRCONFIG;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = IPPROTO_TCP;
    
    char p[64];
    
    snprintf(p, sizeof(p), "%d",port);
    
    ret = getaddrinfo(s, p,&hint ,&res);
    
    if (ret != -1 && res) {
        
        for (cur = res; cur != NULL; cur = cur->ai_next) {
            addr = (struct sockaddr *)cur->ai_addr;
            if(addr->sa_family == AF_INET) {
                break;
            }
        }
        
        if(cur == NULL) {
            for (cur = res; cur != NULL; cur = cur->ai_next) {
                addr = (struct sockaddr *)cur->ai_addr;
                if(addr->sa_family == AF_INET6) {
                    break;
                }
            }
        }
        
        if(cur != NULL && addr != NULL) {
            
            if(addr->sa_family == AF_INET) {
                ((struct sockaddr_in *) addr)->sin_port = htons(port);
                memcpy(result->_data,addr,sizeof(struct sockaddr_in));
                b = 1;
            } else if(addr->sa_family == AF_INET6) {
                ((struct sockaddr_in6 *) addr)->sin6_port = htons(port);
                memcpy(result->_data,addr,sizeof(struct sockaddr_in6));
                b = 1;
            }
            
        }

        if(res) {
            freeaddrinfo(res);
        }
        
    }

    if(!b && addr) {
        struct hostent * en = gethostbyname(s);
        if(en) {
            if(en->h_addrtype == AF_INET) {
                ((struct sockaddr_in *) addr)->sin_port = htons(port);
                memcpy(result->_data,en->h_addr,sizeof(struct sockaddr_in));
                b = 1;
            } else if(addr->sa_family == AF_INET6) {
                ((struct sockaddr_in6 *) addr)->sin6_port = htons(port);
                memcpy(result->_data,en->h_addr,sizeof(struct sockaddr_in6));
                b = 1;
            }
        }
    }
    
    if(jsc_net_getAddrFamily((jsc_object_t *) result)) {
        return (jsc_object_t *) result;
    }
    
    return NULL;
}

static jsc_object_t * jsc_net_createSocket_fd(jsc_int_t fd,jsc_int_t family, jsc_int_t type, jsc_int_t protocol) {
    
    if(fd == -1) {
        fd = socket(family, type, protocol);
    }

    if(fd == -1) {
        return NULL;
    }
    
#ifdef SO_NOSIGPIPE
    {
        int opt = 1;
        setsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, &opt, sizeof(opt));
    }
#endif
    
#ifdef SO_REUSEADDR
    {
        int opt = 1;
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    }
#endif

    jsc_net_Socket_t * s = (jsc_net_Socket_t *) jsc_object_new((jsc_class_t *) &jsc_net_Socket, 0);
    
    s->_fd = fd;
    
    return (jsc_object_t *) s;
}

jsc_object_t * jsc_net_createSocket(jsc_int_t family, jsc_int_t type, jsc_int_t protocol) {
    return jsc_net_createSocket_fd(-1,family,type,protocol);
}

