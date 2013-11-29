#include "port_control.h"



DECLARE_int32(begin);
DECLARE_int32(end);
DECLARE_int32(port);

int PortControl::run(){
    int len=FLAGS_end-FLAGS_begin+1;
    if(len<1){
        LOG(ERROR)<<"input error";
        return -1;
    }
    int ret;
    for(int i=0;i<len;++i){
        FLAGS_port=i+FLAGS_begin;
        m_servers=new NetServer();
        ret=m_servers->init();
        if(ret==0){
            LOG(INFO)<<"port "<<FLAGS_port<<" success";
        }else{
            LOG(WARNING)<<"port "<<FLAGS_port<<" fail";
        }
    }
    while(1){
        sleep(1000);
    }
    return 0;
}
