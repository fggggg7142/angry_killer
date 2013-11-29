#include <stdio.h>
#include <string.h>
#include <string>
#include <pthread.h>

void *func(void *args){
    printf("another thread in!\n");
    return NULL;
}

int main(int argc,char **argv){
    std::string op="thread";
    if(argc>1){
        op=argv[1];
    }
    if(op=="thread"){
        pthread_t pid;
        int ret=pthread_create(&pid,NULL,func,NULL);
        if(ret==0){
            pthread_join(pid,NULL);
            printf("run thread over\n");
        }else{
            printf("create thread error, ret=%d\n",ret);
        }
    }else if(op=="file"){
        FILE *fp=fopen("aktest.txt","w");
        const char *str="hello world";
        int len=fwrite(str,1,strlen(str),fp);
        printf("fwrite's ret=%d\n",len);
        fclose(fp);
    }else{
        printf("unknown operation\n");
    }
    return 0;
}
