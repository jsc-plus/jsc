#include "jsc.h"
#include "fs.h"

/* var implemented */
jsc_int_t jsc_fs_O_CREAT = 0;
jsc_int_t jsc_fs_O_APPEND = 0;
jsc_int_t jsc_fs_O_RDONLY = 0;
jsc_int_t jsc_fs_O_WRONLY = 0;
jsc_int_t jsc_fs_O_RDWR = 0;
jsc_int_t jsc_fs_SEEK_SET = 0;
jsc_int_t jsc_fs_SEEK_CUR = 0;
jsc_int_t jsc_fs_SEEK_END = 0;

/* class implemented */
static void _jsc_Stat_alloc(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_Stat_dealloc(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_ulong_t _jsc_Stat_size(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_boolean_t _jsc_Stat_isDir(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_ulong_t _jsc_Stat_mtime(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_Stat_alloc(jsc_class_t * __isa, jsc_object_t * __object) {}
static void _jsc_Stat_dealloc(jsc_class_t * __isa, jsc_object_t * __object) {
}
jsc_fs_Stat_class_t jsc_fs_Stat = {{(jsc_class_t *)&jsc_Object,sizeof(jsc_fs_Stat_t),"fs_Stat",_jsc_Stat_alloc,_jsc_Stat_dealloc,NULL,NULL,NULL,NULL,NULL,NULL},_jsc_Stat_size,_jsc_Stat_isDir,_jsc_Stat_mtime};
jsc_ulong_t jsc_fs_Stat_size_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_fs_Stat)) {
        jsc_fs_Stat_class_t * s = (jsc_fs_Stat_class_t *) __isa;
        if(s->size) {
            return (*s->size)(__isa,__object);
        } else {
            return jsc_fs_Stat_size_(__isa->isa,__object);
        }
    }

    return 0;
}
jsc_ulong_t jsc_fs_Stat_size(jsc_object_t * __object) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_fs_Stat_size_(__object->isa,__object);
}

jsc_boolean_t jsc_fs_Stat_isDir_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_fs_Stat)) {
        jsc_fs_Stat_class_t * s = (jsc_fs_Stat_class_t *) __isa;
        if(s->isDir) {
            return (*s->isDir)(__isa,__object);
        } else {
            return jsc_fs_Stat_isDir_(__isa->isa,__object);
        }
    }

    return 0;
}
jsc_boolean_t jsc_fs_Stat_isDir(jsc_object_t * __object) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_fs_Stat_isDir_(__object->isa,__object);
}

jsc_ulong_t jsc_fs_Stat_mtime_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_fs_Stat)) {
        jsc_fs_Stat_class_t * s = (jsc_fs_Stat_class_t *) __isa;
        if(s->mtime) {
            return (*s->mtime)(__isa,__object);
        } else {
            return jsc_fs_Stat_mtime_(__isa->isa,__object);
        }
    }

    return 0;
}
jsc_ulong_t jsc_fs_Stat_mtime(jsc_object_t * __object) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_fs_Stat_mtime_(__object->isa,__object);
}

static void _jsc_File_alloc(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_File_dealloc(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_int_t _jsc_File_fd(jsc_class_t * __isa, jsc_object_t * __object);
static void _jsc_File_close(jsc_class_t * __isa, jsc_object_t * __object);
static jsc_long_t _jsc_File_read(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * data);
static jsc_long_t _jsc_File_seek(jsc_class_t * __isa, jsc_object_t * __object, jsc_long_t off, jsc_int_t mode);
static jsc_long_t _jsc_File_write(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * data);
static void _jsc_File_alloc(jsc_class_t * __isa, jsc_object_t * __object) {}
static void _jsc_File_dealloc(jsc_class_t * __isa, jsc_object_t * __object) {
}
jsc_fs_File_class_t jsc_fs_File = {{(jsc_class_t *)&jsc_Object,sizeof(jsc_fs_File_t),"fs_File",_jsc_File_alloc,_jsc_File_dealloc,NULL,NULL,NULL,NULL,NULL,NULL},_jsc_File_fd,_jsc_File_close,_jsc_File_read,_jsc_File_seek,_jsc_File_write};
jsc_int_t jsc_fs_File_fd_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_fs_File)) {
        jsc_fs_File_class_t * s = (jsc_fs_File_class_t *) __isa;
        if(s->fd) {
            return (*s->fd)(__isa,__object);
        } else {
            return jsc_fs_File_fd_(__isa->isa,__object);
        }
    }

    return 0;
}
jsc_int_t jsc_fs_File_fd(jsc_object_t * __object) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_fs_File_fd_(__object->isa,__object);
}

void jsc_fs_File_close_(jsc_class_t * __isa, jsc_object_t * __object) {
	if(__isa == NULL || __object == NULL) {
        return ;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_fs_File)) {
        jsc_fs_File_class_t * s = (jsc_fs_File_class_t *) __isa;
        if(s->close) {
            (*s->close)(__isa,__object);
        } else {
            jsc_fs_File_close_(__isa->isa,__object);
        }
    }

    
}
void jsc_fs_File_close(jsc_object_t * __object) {
	if(__object == NULL) {
        return ;
    }
    jsc_fs_File_close_(__object->isa,__object);
}

jsc_long_t jsc_fs_File_read_(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * data) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_fs_File)) {
        jsc_fs_File_class_t * s = (jsc_fs_File_class_t *) __isa;
        if(s->read) {
            return (*s->read)(__isa,__object,data);
        } else {
            return jsc_fs_File_read_(__isa->isa,__object,data);
        }
    }

    return 0;
}
jsc_long_t jsc_fs_File_read(jsc_object_t * __object, jsc_object_t * data) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_fs_File_read_(__object->isa,__object,data);
}

jsc_long_t jsc_fs_File_seek_(jsc_class_t * __isa, jsc_object_t * __object, jsc_long_t off, jsc_int_t mode) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_fs_File)) {
        jsc_fs_File_class_t * s = (jsc_fs_File_class_t *) __isa;
        if(s->seek) {
            return (*s->seek)(__isa,__object,off,mode);
        } else {
            return jsc_fs_File_seek_(__isa->isa,__object,off,mode);
        }
    }

    return 0;
}
jsc_long_t jsc_fs_File_seek(jsc_object_t * __object, jsc_long_t off, jsc_int_t mode) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_fs_File_seek_(__object->isa,__object,off,mode);
}

jsc_long_t jsc_fs_File_write_(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * data) {
	if(__isa == NULL || __object == NULL) {
        return 0;
    }

    if(jsc_class_isKind(__isa, (jsc_class_t *) &jsc_fs_File)) {
        jsc_fs_File_class_t * s = (jsc_fs_File_class_t *) __isa;
        if(s->write) {
            return (*s->write)(__isa,__object,data);
        } else {
            return jsc_fs_File_write_(__isa->isa,__object,data);
        }
    }

    return 0;
}
jsc_long_t jsc_fs_File_write(jsc_object_t * __object, jsc_object_t * data) {
	if(__object == NULL) {
        return 0;
    }
    return jsc_fs_File_write_(__object->isa,__object,data);
}

