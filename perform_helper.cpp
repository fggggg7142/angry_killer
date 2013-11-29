#include "perform_helper.h"


DECLARE_int32(cpu_fre);
DECLARE_int32(cnum);



PerformHelper::PerformHelper(){
    
}

PerformHelper* PerformHelper::GetInstance(){
    static PerformHelper *inst=NULL;
    if(inst==NULL){
        inst=new PerformHelper();
    }
    return inst;
}

double PerformHelper::get_cpu_ave(){
    double res=0;
    for(int i=0;i<FLAGS_cnum;++i){
        res+=get_cpu();
    }
    res/=FLAGS_cnum;
    return res;
}

double PerformHelper::get_cpu(){
    double user[2];
    double nice[2];
    double sys[2];
    double idle[2];
    double total[2];
    FILE *fp;
    
    for(int i=0;i<2;++i){
        fp=fopen("/proc/stat","r");
        fgets(m_line,65535,fp);
        sscanf(m_line+3,"%lf%lf%lf%lf", user+i,nice+i,sys+i,idle+i);
        fclose(fp);
        total[i]=user[i]+nice[i]+sys[i]+idle[i];
        usleep(FLAGS_cpu_fre*1000);
    }
    //double res=(sys[1]+user[1]-sys[0]-user[0])*100/(total[1]-total[0]);
    double res=100-((idle[1]-idle[0])*100/(total[1]-total[0]));
    return res>0?res:0;
}

uint64_t PerformHelper::get_mem(){
    uint64_t free,res;
    FILE *fp=fopen("/proc/meminfo","r");
    fgets(m_line,65535,fp);
    char *ps=strchr(m_line,':')+1;
    sscanf(ps,"%llu",&res);
    
    fgets(m_line,65535,fp);
    ps=strchr(m_line,':')+1;
    sscanf(ps,"%llu",&free);
    res-=free;
    return res;
}

