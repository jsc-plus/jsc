#ifndef jsc_fs_h
#define jsc_fs_h

#ifdef __cplusplus
extern "C" {
#endif

	extern jsc_int_t jsc_fs_O_CREAT;
	extern jsc_int_t jsc_fs_O_APPEND;
	extern jsc_int_t jsc_fs_O_RDONLY;
	extern jsc_int_t jsc_fs_O_WRONLY;
	extern jsc_int_t jsc_fs_O_RDWR;
	extern jsc_int_t jsc_fs_SEEK_SET;
	extern jsc_int_t jsc_fs_SEEK_CUR;
	extern jsc_int_t jsc_fs_SEEK_END;
	jsc_object_t * jsc_fs_stat(jsc_string_t path);
	jsc_object_t * jsc_fs_open(jsc_string_t path, jsc_int_t flag, jsc_int_t perm);
	typedef jsc_ulong_t (*jsc_fs_Stat_size_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_boolean_t (*jsc_fs_Stat_isDir_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_ulong_t (*jsc_fs_Stat_mtime_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef struct jsc_fs_Stat_class_t {
		jsc_class_t base;
		jsc_fs_Stat_size_t size;
		jsc_fs_Stat_isDir_t isDir;
		jsc_fs_Stat_mtime_t mtime;
	} jsc_fs_Stat_class_t;
	extern jsc_fs_Stat_class_t jsc_fs_Stat;

	typedef struct fs_Stat_t {
		jsc_object_t base;
		jsc_ulong_t _size;
		jsc_boolean_t _isDir;
		jsc_ulong_t _mtime;
	} jsc_fs_Stat_t;

	jsc_ulong_t jsc_fs_Stat_size_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_boolean_t jsc_fs_Stat_isDir_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_ulong_t jsc_fs_Stat_mtime_(jsc_class_t * __isa,jsc_object_t * __object);

	jsc_ulong_t jsc_fs_Stat_size(jsc_object_t * __object);
	jsc_boolean_t jsc_fs_Stat_isDir(jsc_object_t * __object);
	jsc_ulong_t jsc_fs_Stat_mtime(jsc_object_t * __object);
	typedef jsc_int_t (*jsc_fs_File_fd_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef void (*jsc_fs_File_close_t)(jsc_class_t * __isa,jsc_object_t * __object);
	typedef jsc_long_t (*jsc_fs_File_read_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * data);
	typedef jsc_long_t (*jsc_fs_File_seek_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_long_t off, jsc_int_t mode);
	typedef jsc_long_t (*jsc_fs_File_write_t)(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * data);
	typedef struct jsc_fs_File_class_t {
		jsc_class_t base;
		jsc_fs_File_fd_t fd;
		jsc_fs_File_close_t close;
		jsc_fs_File_read_t read;
		jsc_fs_File_seek_t seek;
		jsc_fs_File_write_t write;
	} jsc_fs_File_class_t;
	extern jsc_fs_File_class_t jsc_fs_File;

	typedef struct fs_File_t {
		jsc_object_t base;
		jsc_int_t _fd;
	} jsc_fs_File_t;

	jsc_int_t jsc_fs_File_fd_(jsc_class_t * __isa,jsc_object_t * __object);
	void jsc_fs_File_close_(jsc_class_t * __isa,jsc_object_t * __object);
	jsc_long_t jsc_fs_File_read_(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * data);
	jsc_long_t jsc_fs_File_seek_(jsc_class_t * __isa,jsc_object_t * __object, jsc_long_t off, jsc_int_t mode);
	jsc_long_t jsc_fs_File_write_(jsc_class_t * __isa,jsc_object_t * __object, jsc_object_t * data);

	jsc_int_t jsc_fs_File_fd(jsc_object_t * __object);
	void jsc_fs_File_close(jsc_object_t * __object);
	jsc_long_t jsc_fs_File_read(jsc_object_t * __object, jsc_object_t * data);
	jsc_long_t jsc_fs_File_seek(jsc_object_t * __object, jsc_long_t off, jsc_int_t mode);
	jsc_long_t jsc_fs_File_write(jsc_object_t * __object, jsc_object_t * data);

#ifdef __cplusplus
}
#endif

#endif

