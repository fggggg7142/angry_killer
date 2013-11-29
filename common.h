#ifndef COMMON
#define COMMON

#include "perform_helper.h"

#include <math.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>


#define XIAO_LEN 255
#define MID_LEN 65535
#define MAX_LEN (1024*1024)

int64_t tv_to_microseconds(const timeval & tp);


int64_t get_cur_microseconds_time(void);

class ResourceControl{
public:
    ResourceControl();
    virtual int init();
    virtual int run();

    PerformHelper *m_helper;
};



#endif

