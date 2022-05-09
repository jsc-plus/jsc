#include "test.inc"

/* class implemented */
static void _jsc_A_test(jsc_class_t * __isa, jsc_object_t * __object) {
	jsc_log("A test");
}
static void _jsc_B_test(jsc_class_t * __isa, jsc_object_t * __object) {
	jsc_A_test_((jsc_class_t *)&jsc_A,__object);
	jsc_log("B test");
}

/* function implemented */
jsc_object_t * jsc_test_entrypoint(jsc_object_t * /* jsc_test_closures_declare_2_11_2_t */ callContext, jsc_uint64_t id, jsc_object_t * data) {
	return (jsc_object_t *) jsc_ArrayBuffer_new(0);
}
void jsc_test_init(jsc_string_t dir) {
	jsc_setStrong(&(jsc__dir),JSC_AS_OBJECT_STRING(dir));
}
void jsc_test_exit() {
}
void jsc_test_lowMemory() {
}
static void jsc_closures_4(jsc_object_t * __closures) {
}
void jsc_test_main() {
	jsc_object_t * a=jsc_object_new((jsc_class_t*)&jsc_A,0);
	jsc_object_t * b=jsc_object_new((jsc_class_t*)&jsc_B,0);
	jsc_int_t i=0;
	jsc_log("a.test %s %d %s %d >>",JSC_AS_STRING_OBJECT(a),JSC_AS_INT_OBJECT(a),JSC_AS_STRING_OBJECT(JSC_STRING_ADD(JSC_AS_STRING_INT(2+3-4/2*4%2),"px")),(++i));
	jsc_A_test_((jsc_class_t *)&jsc_A,a);
	jsc_log("b.test %s %d >>",JSC_AS_STRING_OBJECT(b),(++i));
	jsc_B_test_((jsc_class_t *)&jsc_B,b);
	jsc_object_t * done=(jsc_object_t *) jsc_Closures_new((void *) jsc_closures_4,0x0ff);
	(*(jsc_closures_declare_0_2_t)((jsc_Closures_t *)done)->imp)(done);
}
