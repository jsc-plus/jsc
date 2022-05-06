#include "jsc_type.h"
#include "jsc_class.h"
#include "jsc_variant.h"
#include "jsc_buffer.h"
#include "jsc_ArrayBuffer.h"
#include "jsc_DataView.h"
#include "jsc_fs.h"
#include "jsc_fs.inc"

/* var implemented */
jsc_int_t jsc_fs_O_CREAT = O_CREAT;
jsc_int_t jsc_fs_O_APPEND = O_APPEND;
jsc_int_t jsc_fs_O_RDONLY = O_RDONLY;
jsc_int_t jsc_fs_O_WRONLY = O_WRONLY;
jsc_int_t jsc_fs_O_RDWR = O_RDWR;
jsc_int_t jsc_fs_SEEK_SET = SEEK_SET;
jsc_int_t jsc_fs_SEEK_CUR = SEEK_CUR;
jsc_int_t jsc_fs_SEEK_END = SEEK_END;

/* class implemented */
static jsc_ulong_t _jsc_Stat_size(jsc_class_t * __isa, jsc_object_t * __object) {
    jsc_fs_Stat_t * s = (jsc_fs_Stat_t *) __object;
	return s->_size;
}

static jsc_boolean_t _jsc_Stat_isDir(jsc_class_t * __isa, jsc_object_t * __object) {
    jsc_fs_Stat_t * s = (jsc_fs_Stat_t *) __object;
    return s->_isDir;
}

static jsc_ulong_t _jsc_Stat_mtime(jsc_class_t * __isa, jsc_object_t * __object) {
    jsc_fs_Stat_t * s = (jsc_fs_Stat_t *) __object;
    return s->_mtime;
}

static jsc_int_t _jsc_File_fd(jsc_class_t * __isa, jsc_object_t * __object) {
    jsc_fs_File_t * s = (jsc_fs_File_t *) __object;
	return s->_fd;
}

static void _jsc_File_close(jsc_class_t * __isa, jsc_object_t * __object) {
    jsc_fs_File_t * s = (jsc_fs_File_t *) __object;
    if(s->_fd != -1) {
        close(s->_fd);
        s->_fd = -1;
    }
}

static jsc_long_t _jsc_File_read(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * data) {
    jsc_fs_File_t * s = (jsc_fs_File_t *) __object;
    
    if(s->_fd == -1 || data == NULL || !jsc_class_isKind(data->isa, (jsc_class_t *) &jsc_DataView)) {
        return -1;
    }
    
    jsc_DataView_t * dv = (jsc_DataView_t *) data;
    
    if(!dv->_buffer || dv->_byteLength <=0) {
        return -1;
    }
    
    jsc_long_t rs = read(s->_fd,dv->_buffer->_data + dv->_byteOffset,dv->_byteLength);
    
    if(rs == -1) {
        if(errno == EAGAIN) {
            rs = 0;
        }
    }
    
	return rs;
}

static jsc_long_t _jsc_File_seek(jsc_class_t * __isa, jsc_object_t * __object, jsc_long_t off,jsc_int_t mode) {
    
    jsc_fs_File_t * s = (jsc_fs_File_t *) __object;
    
    if(s->_fd == -1) {
        return -1;
    }
    
    return lseek(s->_fd, off, mode);
}

static jsc_long_t _jsc_File_write(jsc_class_t * __isa, jsc_object_t * __object, jsc_object_t * data) {
    
    jsc_fs_File_t * s = (jsc_fs_File_t *) __object;
    
    if(s->_fd == -1 || data == NULL || !jsc_class_isKind(data->isa, (jsc_class_t *) &jsc_DataView)) {
        return -1;
    }
    
    jsc_DataView_t * dv = (jsc_DataView_t *) data;
    
    if(!dv->_buffer || dv->_byteLength <=0) {
        return 0;
    }
    
    jsc_long_t rs = write(s->_fd,dv->_buffer->_data + dv->_byteOffset,dv->_byteLength);
    
    if(rs == -1) {
        if(errno == EAGAIN) {
            rs = 0;
        }
    }
    
    return rs;
}


/* function implemented */
jsc_object_t * jsc_fs_stat(jsc_string_t path) {
    if(path == NULL) {
        return NULL;
    }
    struct stat st;
    
    if(-1 == stat(path, &st)) {
        return NULL;
    }
    
    jsc_fs_Stat_t * s = (jsc_fs_Stat_t *) jsc_object_new((jsc_class_t *) &jsc_fs_Stat, 0);
    
    s->_isDir = S_ISDIR(st.st_mode);
    s->_size = st.st_size;
   
#if defined(__APPLE__)
    s->_mtime = st.st_mtimespec.tv_sec * 1000 + st.st_mtimespec.tv_nsec / 1000;
#else
    s->_mtime = st.st_mtime * 1000;
#endif
    
	return (jsc_object_t *) s;
}

jsc_object_t * jsc_fs_open(jsc_string_t path, jsc_int_t flag, jsc_int_t perm) {
    
    if(path == NULL) {
        return NULL;
    }
    
    jsc_int_t fd = open(path, flag,perm);
    
    if(fd == -1) {
        return NULL;
    }
    
    jsc_fs_File_t * s = (jsc_fs_File_t *) jsc_object_new((jsc_class_t *) &jsc_fs_File, 0);
    
    s->_fd = fd;
    
    return (jsc_object_t *) s;
}


static void _jsc_File_dealloc(jsc_class_t * __isa, jsc_object_t * __object) {
    jsc_fs_File_t * s = (jsc_fs_File_t *) __object;
    if(s->_fd != -1) {
        close(s->_fd);
        s->_fd = -1;
    }
}
