#ifndef HOOK_HELPER
#define HOOK_HELPER

#include <pthread.h>

class HookHelper{

public:
    pthread_mutex_t m_lock;
    HookHelper();
    int add();
    inline void set_val(int val){
        m_val=val;
    }

private:
    int m_cur;
    int m_val;
};

#endif

