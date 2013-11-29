#ifndef PERFORM_HELPER
#define PERFORM_HELPER


#include "gflags/gflags.h"
#include "glog/logging.h"

#include <stdio.h>

class PerformHelper{
public:
    char m_line[65535];
    
    double get_cpu_ave();

    double get_cpu();

    uint64_t get_mem();

    static PerformHelper *GetInstance();
private:
    PerformHelper();
};



#endif
