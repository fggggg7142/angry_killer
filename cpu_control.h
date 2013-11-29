#ifndef CPU_HELPER
#define CPU_HELPER

#include "gflags/gflags.h"
#include "common.h"
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>


class CpuControl:public ResourceControl{
public:
    
    CpuControl();
    
    virtual int run();

    static int64_t m_time;

private:

    pthread_t m_pids[1000];
    int m_len;
    int64_t m_cur_sleep,m_max,m_min;
    double m_cur,m_ori;

    static void *run_fr(void *args);

};




#endif
