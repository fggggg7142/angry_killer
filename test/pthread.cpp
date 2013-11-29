#include <stdio.h>
#include <string.h>
#include <pthread.h>

void *func(void *args){
    printf("hello world\n");
    return NULL;
}

int main(int argc,char **argv){
	pthread_t pid;
	int ret = pthread_create(&pid,NULL,func,NULL);
	if(ret == 0){
	    pthread_join(pid,NULL);
	    printf("run thread over\n");
	}else{
	    printf("create thread error, ret=%d\n",ret);
	}
    	return 0;
}
