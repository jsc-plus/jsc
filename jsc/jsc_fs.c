#include "fs.inc"

/* class implemented */
static jsc_ulong_t _jsc_Stat_size(jsc_class_t * __isa, jsc_object_t * __object) {
	return 0;
}
static jsc_boolean_t _jsc_Stat_isDir(jsc_class_t * __isa, jsc_object_t * __object) {
	return 0;
}
static jsc_ulong_t _jsc_Stat_mtime(jsc_class_t * __isa, jsc_object_t * __object) {
	return 0;
}
static jsc_int_t _jsc_File_fd(jsc_class_t * __isa, jsc_object_t * __object) {
	return 0;
}
static void _jsc_File_close(jsc_class_t * __isa, jsc_object_t * __object) {
}
static jsc_long_t _jsc_File_read(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * data) {
	return 0;
}
static jsc_long_t _jsc_File_seek(jsc_class_t * __isa, jsc_object_t * __object, jsc_long_t off, jsc_int_t mode) {
	return 0;
}
static jsc_long_t _jsc_File_write(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * data) {
	return 0;
}

/* function implemented */
jsc_object_t * jsc_fs_stat(jsc_string_t path) {
	return NULL;
}
jsc_object_t * jsc_fs_open(jsc_string_t path, jsc_int_t flag, jsc_int_t perm) {
	return NULL;
}
