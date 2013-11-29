#include "cpu_control.h"





DECLARE_int32(sleep_eve);
DECLARE_int32(thread_num);
DECLARE_int32(wen_time);
DECLARE_double(cpu_use);

int64_t CpuControl::m_time=0;

CpuControl::CpuControl():m_len(0),m_ori(-1){
    m_min=0;
    m_max=FLAGS_sleep_eve;
    m_cur_sleep=(m_min+m_max)/2;
}

void* CpuControl::run_fr(void *args){
    double flag=2.5;
    while(1){
        for(int i=0;i<1000;++i){
            flag=sin(1)+sin(2)+sin(3);
        }
        usleep(m_time);
    }
    return NULL;
}

int CpuControl::run(){
    if(FLAGS_cpu_use>100) return -1;
    double m_cur=m_helper->get_cpu_ave();
    for(int i=0;i<FLAGS_thread_num;++i){
        pthread_create(m_pids+m_len++,NULL,CpuControl::run_fr,NULL);
    }
    double cha,shicha;
    int change;
    int wentai=0;
    while(1){
        if(wentai>=FLAGS_wen_time){
            m_helper->get_cpu_ave();
            continue;
        }
        change=0;
        m_ori=m_cur;
        m_cur=m_helper->get_cpu_ave();
        shicha=m_cur-FLAGS_cpu_use;
        if(shicha>0){
            m_time+=m_cur_sleep;
            change=1;
        }else if(shicha<0){
            if(CpuControl::m_time==0){
                pthread_create(m_pids+m_len++,NULL,CpuControl::run_fr,NULL);
                VLOG(5)<<"create a thread, thread num is "<<m_len;
            }else{
                if(m_time>=m_cur_sleep){
                    m_time-=m_cur_sleep;
                    change=1;
                }else{
                    m_time=0;
                }
                
            }
            
        }
        if(change==1){
            cha=m_cur-m_ori;
            if(cha<0){
                cha=-cha;
            }
            if(cha>10){
                m_max=m_cur_sleep;
                m_cur_sleep=(m_max+m_min)/2;
                m_min-=m_cur_sleep;
                if(m_min<0){
                    m_min=0;
                }
                wentai=0;
            }else if(shicha>15||shicha<-15){
                if(cha<3){
                    m_min=m_cur_sleep;
                    m_max+=m_cur_sleep;
                    m_cur_sleep=(m_max+m_min)/2;
                    wentai=0;
                }
            }else{
                ++wentai;
            }
            if(m_cur_sleep==0){
                if(shicha>15){
                    m_time+=1;
                }else if(shicha<-15){
                    m_time-=1;
                }
            }
            VLOG(5)<<"buchang="<<m_cur_sleep<<" m_time="<<m_time;
        }
    }
    return 0;
}


