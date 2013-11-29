#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <dlfcn.h>
#include <error.h>

extern int errno;
#define ECONNREFUSED 111
extern "C" {
int connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen) {
	srand(time(NULL));
	int r = rand() % 100;
	if ( r < 50) {
		errno = ECONNREFUSED;
		return -1;
	}else {
		int (*_connect)(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen) = NULL;
		_connect = (int (*)(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen)) dlsym(RTLD_NEXT, "connect");
		return _connect(sockfd, serv_addr, addrlen);
	}
}
}
