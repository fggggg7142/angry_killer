#include "pid_control.h"


DECLARE_int64(pid_size);

std::vector<pid_t> PidControl::m_pids;

int PidControl::run(){
    signal(SIGINT, SignalIntHandler);
    signal(SIGTERM, SignalIntHandler);
    pid_t pt;
    for(int i=0;i<FLAGS_pid_size;++i){
        pt=fork();
        if(pt==0){
            while(1){
                sleep(1000);
            }
        }else{
            m_pids.push_back(pt);
        }
    }
    while(1){
        sleep(1000);
    }
    return 0;
}

void PidControl::SignalIntHandler(int sig){
    for(std::vector<pid_t>::iterator it=m_pids.begin();it!=m_pids.end();++it){
        kill(*it,SIGKILL);
        waitpid(*it,NULL,0);
    }
    m_pids.clear();
    exit(0);
}

