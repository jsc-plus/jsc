#ifndef jsc_net_h
#define jsc_net_h

#ifdef __cplusplus
extern "C" {
#endif

	extern jsc_int_t jsc_net_AF_INET;
	extern jsc_int_t jsc_net_AF_INET6;
	extern jsc_int_t jsc_net_AF_UNIX;
	extern jsc_int_t jsc_net_EV_READ;
	extern jsc_int_t jsc_net_EV_WRITE;
	extern jsc_int_t jsc_net_SOCK_STREAM;
	extern jsc_int_t jsc_net_SOCK_DGRAM;
	extern jsc_int_t jsc_net_SOCK_RAW;
	jsc_object_t * jsc_net_createAddr(jsc_string_t s, jsc_int_t port);
	jsc_int_t jsc_net_getAddrFamily(jsc_object_t * s);
	jsc_int_t jsc_net_getAddrPort(jsc_object_t * s);
	jsc_string_t jsc_net_getAddrString(jsc_object_t * s);
	jsc_object_t * jsc_net_resolve(jsc_string_t s, jsc_int_t port);
	jsc_object_t * jsc_net_createSocket(jsc_int_t family, jsc_int_t type, jsc_int_t protocol);
	typedef jsc_int_t (*jsc_net_Socket_bind_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * addr);
	typedef jsc_int_t (*jsc_net_Socket_connect_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * addr);
	typedef jsc_int_t (*jsc_net_Socket_listen_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_int_t block);
	typedef jsc_object_t * (*jsc_net_Socket_accept_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * addr);
	typedef jsc_int_t (*jsc_net_Socket_nonblock_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_boolean_t v);
	typedef jsc_int_t (*jsc_net_Socket_keepalive_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_boolean_t enabled, jsc_int_t idle, jsc_int_t interval, jsc_int_t count);
	typedef jsc_int_t (*jsc_net_Socket_broadcast_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_boolean_t v);
	typedef jsc_int_t (*jsc_net_Socket_bufsize_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_int_t recvbuf, jsc_int_t sendbuf);
	typedef jsc_int_t (*jsc_net_Socket_select_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_int_t types, jsc_int_t tv);
	typedef jsc_int_t (*jsc_net_Socket_send_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * data);
	typedef jsc_int_t (*jsc_net_Socket_recv_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * data);
	typedef jsc_int_t (*jsc_net_Socket_sendto_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * addr, jsc_object_t * data);
	typedef jsc_int_t (*jsc_net_Socket_recvfrom_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * addr, jsc_object_t * data);
	typedef jsc_int_t (*jsc_net_Socket_fd_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_boolean_t (*jsc_net_Socket_valid_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_object_t * (*jsc_net_Socket_addr_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef void (*jsc_net_Socket_close_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef struct jsc_net_Socket_class_t {
		jsc_class_t base;
		jsc_net_Socket_bind_t bind;
		jsc_net_Socket_connect_t connect;
		jsc_net_Socket_listen_t listen;
		jsc_net_Socket_accept_t accept;
		jsc_net_Socket_nonblock_t nonblock;
		jsc_net_Socket_keepalive_t keepalive;
		jsc_net_Socket_broadcast_t broadcast;
		jsc_net_Socket_bufsize_t bufsize;
		jsc_net_Socket_select_t select;
		jsc_net_Socket_send_t send;
		jsc_net_Socket_recv_t recv;
		jsc_net_Socket_sendto_t sendto;
		jsc_net_Socket_recvfrom_t recvfrom;
		jsc_net_Socket_fd_t fd;
		jsc_net_Socket_valid_t valid;
		jsc_net_Socket_addr_t addr;
		jsc_net_Socket_close_t close;
	} jsc_net_Socket_class_t;
	extern jsc_net_Socket_class_t jsc_net_Socket;

	typedef struct net_Socket_t {
		jsc_object_t base;
		jsc_int_t _fd;
	} jsc_net_Socket_t;

	jsc_int_t jsc_net_Socket_bind_(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * addr);
	jsc_int_t jsc_net_Socket_connect_(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * addr);
	jsc_int_t jsc_net_Socket_listen_(jsc_class_t * __isa,jsc_object_t * __object, jsc_int_t block);
	jsc_object_t * jsc_net_Socket_accept_(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * addr);
	jsc_int_t jsc_net_Socket_nonblock_(jsc_class_t * __isa,jsc_object_t * __object, jsc_boolean_t v);
	jsc_int_t jsc_net_Socket_keepalive_(jsc_class_t * __isa,jsc_object_t * __object, jsc_boolean_t enabled, jsc_int_t idle, jsc_int_t interval, jsc_int_t count);
	jsc_int_t jsc_net_Socket_broadcast_(jsc_class_t * __isa,jsc_object_t * __object, jsc_boolean_t v);
	jsc_int_t jsc_net_Socket_bufsize_(jsc_class_t * __isa,jsc_object_t * __object, jsc_int_t recvbuf, jsc_int_t sendbuf);
	jsc_int_t jsc_net_Socket_select_(jsc_class_t * __isa,jsc_object_t * __object, jsc_int_t types, jsc_int_t tv);
	jsc_int_t jsc_net_Socket_send_(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * data);
	jsc_int_t jsc_net_Socket_recv_(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * data);
	jsc_int_t jsc_net_Socket_sendto_(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * addr, jsc_object_t * data);
	jsc_int_t jsc_net_Socket_recvfrom_(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * addr, jsc_object_t * data);
	jsc_int_t jsc_net_Socket_fd_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_boolean_t jsc_net_Socket_valid_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_object_t * jsc_net_Socket_addr_(jsc_class_t * __isa,jsc_object_t * __object);
	void jsc_net_Socket_close_(jsc_class_t * __isa,jsc_object_t * __object);

	jsc_int_t jsc_net_Socket_bind(jsc_object_t * __object, jsc_object_t * addr);
	jsc_int_t jsc_net_Socket_connect(jsc_object_t * __object, jsc_object_t * addr);
	jsc_int_t jsc_net_Socket_listen(jsc_object_t * __object, jsc_int_t block);
	jsc_object_t * jsc_net_Socket_accept(jsc_object_t * __object, jsc_object_t * addr);
	jsc_int_t jsc_net_Socket_nonblock(jsc_object_t * __object, jsc_boolean_t v);
	jsc_int_t jsc_net_Socket_keepalive(jsc_object_t * __object, jsc_boolean_t enabled, jsc_int_t idle, jsc_int_t interval, jsc_int_t count);
	jsc_int_t jsc_net_Socket_broadcast(jsc_object_t * __object, jsc_boolean_t v);
	jsc_int_t jsc_net_Socket_bufsize(jsc_object_t * __object, jsc_int_t recvbuf, jsc_int_t sendbuf);
	jsc_int_t jsc_net_Socket_select(jsc_object_t * __object, jsc_int_t types, jsc_int_t tv);
	jsc_int_t jsc_net_Socket_send(jsc_object_t * __object, jsc_object_t * data);
	jsc_int_t jsc_net_Socket_recv(jsc_object_t * __object, jsc_object_t * data);
	jsc_int_t jsc_net_Socket_sendto(jsc_object_t * __object, jsc_object_t * addr, jsc_object_t * data);
	jsc_int_t jsc_net_Socket_recvfrom(jsc_object_t * __object, jsc_object_t * addr, jsc_object_t * data);
	jsc_int_t jsc_net_Socket_fd(jsc_object_t * __object);
	jsc_boolean_t jsc_net_Socket_valid(jsc_object_t * __object);
	jsc_object_t * jsc_net_Socket_addr(jsc_object_t * __object);
	void jsc_net_Socket_close(jsc_object_t * __object);

#ifdef __cplusplus
}
#endif

#endif

