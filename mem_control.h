#ifndef MEM_HELPER
#define MEM_HELPER

#include "common.h"


class MemControl:public ResourceControl{
public:
    virtual int run();
private:
    uint64_t get_cur_mem();
};

#endif
