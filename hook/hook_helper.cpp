#include "hook_helper.h"

HookHelper::HookHelper():m_cur(0),m_val(-1){
    pthread_mutex_init(&m_lock,NULL);
}

int HookHelper::add(){
    if(m_val==-1) return -1;
    int ret=0;
    pthread_mutex_lock(&m_lock);
    if(m_cur==m_val){
        m_cur=-1;
        ret=-1;
    }
    ++m_cur;
    pthread_mutex_unlock(&m_lock);
    return ret;
}

