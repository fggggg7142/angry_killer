#include <stdio.h>
#include <string.h>
#include <string>
#include <pthread.h>


int main(int argc,char **argv){
    FILE *fp = fopen("test.txt","w");
    const char *str = "hello world";
    size_t len = fwrite(str, 1, strlen(str), fp);
    printf("fwrite's ret = %d\n", len);
    fclose(fp);
    return 0;
}
