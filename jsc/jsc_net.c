#include "net.inc"

/* class implemented */
static jsc_int_t _jsc_Socket_bind(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr) {
	return 0;
}
static jsc_int_t _jsc_Socket_connect(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr) {
	return 0;
}
static jsc_int_t _jsc_Socket_listen(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t block) {
	return 0;
}
static jsc_object_t * _jsc_Socket_accept(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr) {
	return NULL;
}
static jsc_int_t _jsc_Socket_nonblock(jsc_class_t * __isa, jsc_object_t * __object, jsc_boolean_t v) {
	return 0;
}
static jsc_int_t _jsc_Socket_keepalive(jsc_class_t * __isa, jsc_object_t * __object, jsc_boolean_t enabled, jsc_int_t idle, jsc_int_t interval, jsc_int_t count) {
	return 0;
}
static jsc_int_t _jsc_Socket_broadcast(jsc_class_t * __isa, jsc_object_t * __object, jsc_boolean_t v) {
	return 0;
}
static jsc_int_t _jsc_Socket_bufsize(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t recvbuf, jsc_int_t sendbuf) {
	return 0;
}
static jsc_int_t _jsc_Socket_select(jsc_class_t * __isa, jsc_object_t * __object, jsc_int_t types, jsc_int_t tv) {
	return 0;
}
static jsc_int_t _jsc_Socket_send(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * data) {
	return 0;
}
static jsc_int_t _jsc_Socket_recv(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * data) {
	return 0;
}
static jsc_int_t _jsc_Socket_sendto(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr, jsc_object_t * data) {
	return 0;
}
static jsc_int_t _jsc_Socket_recvfrom(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * addr, jsc_object_t * data) {
	return 0;
}
static jsc_int_t _jsc_Socket_fd(jsc_class_t * __isa, jsc_object_t * __object) {
	return 0;
}
static jsc_boolean_t _jsc_Socket_valid(jsc_class_t * __isa, jsc_object_t * __object) {
	return 0;
}
static jsc_object_t * _jsc_Socket_addr(jsc_class_t * __isa, jsc_object_t * __object) {
	return NULL;
}
static void _jsc_Socket_close(jsc_class_t * __isa, jsc_object_t * __object) {
}

/* function implemented */
jsc_object_t * jsc_net_createAddr(jsc_string_t s, jsc_int_t port) {
	return NULL;
}
jsc_int_t jsc_net_getAddrFamily(jsc_object_t * s) {
	return 0;
}
jsc_int_t jsc_net_getAddrPort(jsc_object_t * s) {
	return 0;
}
jsc_string_t jsc_net_getAddrString(jsc_object_t * s) {
	return NULL;
}
jsc_object_t * jsc_net_resolve(jsc_string_t s, jsc_int_t port) {
	return NULL;
}
jsc_object_t * jsc_net_createSocket(jsc_int_t family, jsc_int_t type, jsc_int_t protocol) {
	return NULL;
}
