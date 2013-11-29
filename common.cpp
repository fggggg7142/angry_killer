#include "common.h"



int ResourceControl::init(){
    return 0;
}

int ResourceControl::run(){
    while(1){
        sleep(1000);
    }
    return 0;
}

ResourceControl::ResourceControl(){
    m_helper=PerformHelper::GetInstance();
}


int64_t tv_to_microseconds(const timeval & tp)
{
    return (((int64_t) tp.tv_sec) * 1000000 + (int64_t) tp.tv_usec);
}


int64_t get_cur_microseconds_time(void)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tv_to_microseconds(tp);
}
