#include <stdio.h>                                                                                          
#include <errno.h>
#include <pthread.h>
#include "bhook.h"               
#include "gflags/gflags.h"                                                                           
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <dlfcn.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdarg.h>

#include "common.h"
#include "hook_helper.h"
//connect,send,recv,write,read,malloc,popen,open,fork,pthread_create,                                                                                                            
//file:open,write,read,fwrite,fread
//
//signal:mkfifo,pipe,
//进程控制函数:execl
//文件权限控制函数:link,fstat
//=============connect ===============
DECLARE_int32(set_connect_value);

int my_connect(int sockfd, const struct sockaddr *serv_addr, int addrlen) {
	int32_t return_value = FLAGS_set_connect_value;
	if( return_value == -100 ) {
		typedef int(*REALFUNC)(int sockfd, const struct sockaddr *serv_addr, int addrlen);
		REALFUNC real_connect = (REALFUNC)get_real_func("connect");
		return real_connect(sockfd, serv_addr, addrlen);
	}
	errno=ECONNREFUSED;
	return return_value;	
}

//==============send ===================
DECLARE_int32(set_send_value);
DECLARE_int32(send_flag);
int my_send(int s, const void *msg, int len, unsigned int flags) {
	int32_t return_value = FLAGS_set_send_value;
    typedef int(*REALFUNC)(int s, const void *msg, int len, unsigned int flags);
    REALFUNC real_send = (REALFUNC)get_real_func("send");
    static HookHelper helper;
    helper.set_val(FLAGS_send_flag);
	if ( return_value == -100){
		return real_send(s, msg, len, flags);
	}
    if(helper.add()==0){
		return real_send(s, msg, len, flags);
    }
	errno=EAGAIN;
	return return_value;
}

//==============recv===================
DECLARE_int32(set_recv_value);
DECLARE_int32(recv_flag);
int my_recv(int s, void *buf, int len, unsigned int flags) {
	int32_t return_value = FLAGS_set_recv_value;
    typedef int(*REALFUNC)(int s, void *buf, int len, unsigned int flags);
    REALFUNC real_recv = (REALFUNC)get_real_func("recv");
    static HookHelper helper;
    helper.set_val(FLAGS_recv_flag);
	if ( return_value == -100 ) {
		return real_recv(s, buf, len, flags);
	}
    if(helper.add()==0){
		return real_recv(s, buf, len, flags);
    }
	errno=EAGAIN;
	return return_value;
}

//================write==============
DECLARE_int32(set_write_value);
DECLARE_int32(write_flag);
ssize_t my_write(int fd, const void *buf, size_t count) {
	int32_t return_value = FLAGS_set_recv_value;
    typedef ssize_t(*REALFUNC)(int fd, const void *buf, size_t count);
    REALFUNC real_write = (REALFUNC)get_real_func("write");
    static HookHelper helper;
    helper.set_val(FLAGS_write_flag);
	if ( return_value == -100)	{
		return real_write(fd, buf, count);
	}
    if(helper.add()==0){
		return real_write(fd, buf, count);
    }
	errno = EAGAIN;
	return return_value;
}

//===============read===========
DECLARE_int32(set_read_value);
DECLARE_int32(read_flag);
ssize_t my_read(int fd, void *buf, size_t count) {
	int32_t return_value = FLAGS_set_read_value;
    typedef ssize_t(*REALFUNC)(int fd, void *buf, size_t count);
    REALFUNC real_read = (REALFUNC)get_real_func("read");
    static HookHelper helper;
    helper.set_val(FLAGS_read_flag);
	if ( return_value == -100) { 
		return real_read(fd, buf, count);
	}
    if(helper.add()==0){
		return real_read(fd, buf, count);
    }
	errno = EAGAIN;
	return return_value;
}

//=============malloc============
DECLARE_string(set_malloc_value);
DECLARE_int32(malloc_flag);
void* my_malloc(size_t size) {
	std::string return_value = FLAGS_set_malloc_value;
	static HookHelper helper;
    helper.set_val(FLAGS_malloc_flag);
    typedef void*(*REALFUNC)(size_t size);
    REALFUNC real_malloc = (REALFUNC)get_real_func("malloc");
	if ( return_value == "NULL" ) {
        return real_malloc(size);
	}
    if(helper.add()==0){
        return real_malloc(size);
    }
	return NULL;
}

//=============popen===========
DECLARE_string(set_popen_value);
DECLARE_int32(popen_flag);
FILE *my_popen(const char *command, const char *type) {
	std::string return_value = FLAGS_set_popen_value;
    typedef FILE*(*REALFUNC)(const char *command, const char *type);
    REALFUNC real_popen = (REALFUNC)get_real_func("popen");
    
    static HookHelper helper;
    helper.set_val(FLAGS_popen_flag);

	if ( return_value == "NULL" ) {
		return real_popen(command, type);
	}
    if(helper.add()==0){
        return real_popen(command, type);
    }
	errno = EINVAL;
	return NULL;
}

//=============open===========
DECLARE_int32(set_open_value);
DECLARE_int32(open_flag);
int my_open(const char* pathname, int flags, mode_t mode) {
	int32_t return_value = FLAGS_set_open_value;
    typedef int(*REALFUNC)(const char *pathname, int flags, mode_t mode);
    REALFUNC real_open = (REALFUNC)get_real_func("open");
    static HookHelper helper;
    helper.set_val(FLAGS_open_flag);
	if ( return_value == -100 ) {
		return real_open(pathname ,flags, mode);
	}
    if(helper.add()==0){
		return real_open(pathname ,flags, mode);
    }
	errno = EACCES;
	return return_value;
}
//=============fork===========
DECLARE_int32(set_fork_value);
DECLARE_int32(fork_flag);
pid_t my_fork() {
	int32_t return_value = FLAGS_set_fork_value;
    typedef pid_t(*REALFUNC)();
    REALFUNC real_fork = (REALFUNC)get_real_func("fork");
    static HookHelper helper;
    helper.set_val(FLAGS_fork_flag);
	if ( return_value == -100 ) {
		return real_fork();
	}
    
    if(helper.add()==0){
		return real_fork();
    }
	errno = EAGAIN;
	return return_value;
}

//=============fread===========
DECLARE_int32(set_fread_value);
DECLARE_int32(fread_flag);
size_t my_fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	int32_t return_value = FLAGS_set_fread_value;
    typedef size_t(*REALFUNC)(void *ptr, size_t size, size_t nmemb, FILE *stream);
    REALFUNC real_fread = (REALFUNC)get_real_func("fread");
    static HookHelper helper;
    helper.set_val(FLAGS_fread_flag);
	if ( return_value == -100 ) {
		return real_fread(ptr, size, nmemb, stream);
	}
    if(helper.add()==0){
		return real_fread(ptr, size, nmemb, stream);
    }
	errno = EAGAIN;
	return return_value;
}

//=============fwrite===========
DECLARE_int32(set_fwrite_value);
DECLARE_int32(fwrite_flag);
size_t my_fwrite(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	int32_t return_value = FLAGS_set_fwrite_value;
    typedef size_t(*REALFUNC)(void *ptr, size_t size, size_t nmemb, FILE *stream);
    REALFUNC real_fwrite = (REALFUNC)get_real_func("fwrite");
    static HookHelper helper;
    helper.set_val(FLAGS_fwrite_flag);
	if ( return_value == -100 ) {
		return real_fwrite(ptr, size, nmemb, stream);
	}
    if(helper.add()==0){
		return real_fwrite(ptr, size, nmemb, stream);
    }
	errno = EAGAIN;
	return return_value;
}

//=============pthread_create===========
DECLARE_int32(set_pthread_create_value);
DECLARE_int32(pthread_create_flag);
int my_pthread_create(pthread_t *thread, const pthread_attr_t *attr, void*(*start_routine)(void *), void *arg) {
	int32_t return_value = FLAGS_set_pthread_create_value;
    typedef int(*REALFUNC)(pthread_t *thread, const pthread_attr_t *attr, void*(*start_routine)(void *), void *arg);
    REALFUNC real_pthread_create = (REALFUNC)get_real_func("pthread_create");
    static HookHelper helper;
    helper.set_val(FLAGS_pthread_create_flag);
	if ( return_value == -100 ) {
		return real_pthread_create(thread, attr, start_routine, arg);
	}
    if(helper.add()==0){
		return real_pthread_create(thread, attr, start_routine, arg);
    }
	//errno = EAGAIN;
	return return_value;
}

//============= mkfifo ===========
DECLARE_int32(set_mkfifo_value);
DECLARE_int32(mkfifo_flag);
int my_mkfifo(const char* pathname, mode_t mode) {
	int32_t return_value = FLAGS_set_mkfifo_value;
    typedef int(*REALFUNC)(const char* pathname, mode_t mode);
    REALFUNC real_mkfifo = (REALFUNC)get_real_func("mkfifo");
    static HookHelper helper;
    helper.set_val(FLAGS_mkfifo_flag);
	if ( return_value == -100 ) {
		return real_mkfifo(pathname, mode);
	}
    if(helper.add()==0){
		return real_mkfifo(pathname, mode);
    }
	errno = EACCES;
	return return_value;
}
//============= pipe ===========
DECLARE_int32(set_pipe_value);
DECLARE_int32(pipe_flag);
int my_pipe(int fileds[2]) {
	int32_t return_value = FLAGS_set_pipe_value;
    typedef int(*REALFUNC)(int fileds[2]);
    REALFUNC real_pipe = (REALFUNC)get_real_func("pipe");
    static HookHelper helper;
    helper.set_val(FLAGS_pipe_flag);

	if ( return_value == -100 ) {
		return real_pipe(fileds);
	}
    if(helper.add()==0){
		return real_pipe(fileds);
    }
	errno = EFAULT;
	return return_value;
}

//============= execl ===========
DECLARE_int32(set_execl_value);
DECLARE_int32(execl_flag);
int my_execl(const char* path, const char* arg, ...) {
	int32_t return_value = FLAGS_set_execl_value;
    typedef int(*REALFUNC)(const char* path, const char* arg, ...);
    REALFUNC real_execl = (REALFUNC)get_real_func("execl");
    va_list p;
    va_start(p, arg);
    static HookHelper helper;
    helper.set_val(FLAGS_execl_flag);
	if ( return_value == -100 ) {
		return real_execl(path, arg);
	}
    if(helper.add()==0){
		return real_execl(path, arg);
    }
	errno = EACCES;
	return return_value;
}
//============= link ===========
DECLARE_int32(set_link_value);
DECLARE_int32(link_flag);
int my_link(const char* oldpath, const char* newpath) {
	int32_t return_value = FLAGS_set_link_value;
    typedef int(*REALFUNC)(const char* oldpath, const char* newpath);
    REALFUNC real_link = (REALFUNC)get_real_func("link");
    static HookHelper helper;
    helper.set_val(FLAGS_link_flag);
	if ( return_value == -100 ) {
		return real_link(oldpath, newpath);
	}
    if(helper.add()==0){
		return real_link(oldpath, newpath);
    }
	errno = EEXIST;
	return return_value;
}
//============= fstat ===========
DECLARE_int32(set_fstat_value);
DECLARE_int32(fstat_flag);
int my_fstat(int fields, struct stat *buf) {
	int32_t return_value = FLAGS_set_fstat_value;
    typedef int(*REALFUNC)(int fields, struct stat *buf);
    REALFUNC real_fstat = (REALFUNC)get_real_func("fstat");
    static HookHelper helper;
    helper.set_val(FLAGS_fstat_flag);
	if ( return_value == -100 ) {
		return real_fstat(fields, buf);
	}
    if(helper.add()==0){
		return real_fstat(fields, buf);
    }
	errno = ENOENT;
	return return_value;
}
//============= dlopen ===========
DECLARE_string(set_dlopen_value);
DECLARE_int32(dlopen_flag);
void* my_dlopen(const char* pathname, int mode) {
	std::string return_value = FLAGS_set_dlopen_value;
    typedef void*(*REALFUNC)(const char* pathname, int mode);
    REALFUNC real_dlopen = (REALFUNC)get_real_func("dlopen");
    static HookHelper helper;
    helper.set_val(FLAGS_dlopen_flag);
	if ( return_value == "NULL" ) {
		return real_dlopen(pathname, mode);
	}
    if(helper.add()==0){
		return real_dlopen(pathname, mode);
    }
	//errno = ENOENT;
	return NULL;
}

//============= dlsym ===========
DECLARE_string(set_dlsym_value);
DECLARE_int32(dlsym_flag);
void* my_dlsym(void *pHandle, char *symbol) {
	std::string return_value = FLAGS_set_dlsym_value;
    typedef void*(*REALFUNC)(void *pHandle, char *symbol);
    REALFUNC real_dlsym = (REALFUNC)get_real_func("dlsym");
    static HookHelper helper;
    helper.set_val(FLAGS_dlsym_flag);
	if ( return_value == "NULL" ) {
		return real_dlsym(pHandle, symbol);
	}
    if(helper.add()==0){
		return real_dlsym(pHandle, symbol);
    }
	//errno = ENOENT;
	return NULL;
}

//=========== 
int ak_printf(const char *format, ...)                                                                      
{                                                                                                           
    typedef int (*REALFUNC)(const char *format, ...);                                                       
    REALFUNC real_printf = (REALFUNC)get_real_func("printf");                                               
                                                                                                            
    real_printf("this is my printf function!\n");                                                           
    return 0;                                                                                               
}

//int ak_pthread_create(pthread_t *thread,
//    const pthread_attr_t *attr,
//    void *(*start_routine)(void*),
//    void *arg){
//	
//    printf("jiazhuang buxing\n");
//    return EAGAIN;
//}
void __attribute__ ((constructor)) my_printf_init(void)                                                     
{                                                                                                           
    //attach_func("printf", (void *)ak_printf);                                                               
    key_t key = ftok("angry_killer", (int)'a');
    int shmid = shmget(key, MID_LEN, 0600);
    char* buf = (char*)shmat(shmid, NULL, 0);
    //printf("%s\n",buf);
    //printf("%d\n",shmctl(shmid, IPC_RMID, NULL));
    shmctl(shmid, IPC_RMID, NULL);
    std::string str=buf;
    ::google::ReadFlagsFromString(str,"angry_killer",true);
    //attach_func("pthread_create", (void *)ak_pthread_create);                                                               
    attach_func("connect", (void *)my_connect);
    attach_func("send", (void *)my_send);
    attach_func("recv", (void *)my_recv);
    attach_func("write", (void *)my_write);
    attach_func("read", (void *)my_read);
    attach_func("malloc", (void *)my_malloc);
    attach_func("popen", (void *)my_popen);
    attach_func("open", (void *)my_open);
    attach_func("fork", (void *)my_fork);
    attach_func("fread", (void *)my_fread);
    attach_func("fwrite", (void *)my_fwrite);
    attach_func("pthread_create", (void *)my_pthread_create);
    attach_func("mkfifo",(void *)my_mkfifo);
    attach_func("pipe",(void *)my_pipe);
//    attach_func("execl",(void *)my_execl);
    attach_func("link",(void *)my_link);
    attach_func("fstat", (void *)my_fstat);
    attach_func("dlopen", (void *)my_dlopen);
    attach_func("dlsym", (void *)my_dlsym);
}

