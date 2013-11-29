#include "perform_show.h"

PerformShow::PerformShow(){
    m_helper=PerformHelper::GetInstance();
}
void *PerformShow::thread_run(void *args){
    PerformShow *inst=(PerformShow*)args;
    inst->show();
}


int PerformShow::show(){
    double dval;
    uint64_t uval;
    while(1){
        dval=m_helper->get_cpu_ave();
        LOG(INFO)<<"cpu: "<<dval<<" %";
        uval=m_helper->get_mem();
        LOG(INFO)<<"mem: "<<uval<<" KB";
    }
}

int PerformShow::start(){
    pthread_t pt;
    pthread_create(&pt,NULL,thread_run,this);
}

