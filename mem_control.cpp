#include "mem_control.h"


DECLARE_uint64(mem_size);

uint64_t MemControl::get_cur_mem(){
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

int MemControl::run(){
    char *data;
    uint64_t temp=FLAGS_mem_size*1024;
    uint64_t cur_mem=get_cur_mem();
    if(temp<=cur_mem){
        LOG(ERROR)<<"memory get two small: "<<temp<<"KB vs "<<cur_mem<<"KB";
        return -1;
    }
    uint64_t len=(temp-cur_mem)*1024;
    data=new char[len];
    memset(data,0,len);
    while(1){
        sleep(1000);
    }
    return 0;
}

