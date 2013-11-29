#include "disk_write.h"


DECLARE_string(data_path);

DECLARE_string(write_path);
DECLARE_int32(eve_size);

pthread_mutex_t m_mutex=PTHREAD_MUTEX_INITIALIZER;


int DiskWriteControl::init(){
    char read_dir[XIAO_LEN];
    sprintf(read_dir,"%s/%s",FLAGS_data_path.c_str(),FLAGS_write_path.c_str());
    if(dirc(FLAGS_data_path.c_str())||dirc(read_dir)){
        return -1;
    }
    sprintf(m_file_path,"%s/data.",read_dir);
    return 0;
}

int DiskWriteControl::run(){
    int64_t begin,end,cha;
    FILE *fp;
    char buf[MAX_LEN];
    while(1){
        begin=get_cur_microseconds_time();
        fp=fopen(m_file_path,"w");
        for(int i=0;i<FLAGS_eve_size;++i){
            fwrite(buf,MAX_LEN,1,fp);
        }
        fflush(fp);
        fclose(fp);
        end=get_cur_microseconds_time();
        cha=1000000-(end-begin);
        if(cha>0){
            usleep(cha);
        }
    }
}


int DiskWriteControl::dirc(const char *src){
    if(access(src,W_OK)!=0){
        if(mkdir(src,0755)!=0){
            return -1;
        }
        return 0;
    }
    return 0;
}


