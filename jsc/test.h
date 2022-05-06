#ifndef jsc_test_h
#define jsc_test_h

#ifdef __cplusplus
extern "C" {
#endif

	jsc_object_t * jsc_test_entrypoint(jsc_object_t * (*callContext)(jsc_uint64_t,jsc_object_t *), jsc_uint64_t id, jsc_object_t * data);
	void jsc_test_init(jsc_string_t dir);
	void jsc_test_exit(void);
	void jsc_test_lowMemory(void);
	void jsc_test_main(void);

#ifdef __cplusplus
}
#endif

#endif

