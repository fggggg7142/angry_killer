#include "fd_control.h"


DECLARE_int32(fd_num);
DECLARE_string(data_path);
DECLARE_string(fd_path);
DECLARE_string(exec_path);

FdControl::FdControl():m_cur_num(0){}

int FdControl::init(){
    char read_dir[XIAO_LEN];
    sprintf(read_dir,"%s/%s",FLAGS_data_path.c_str(),FLAGS_fd_path.c_str());
    if(DiskWriteControl::dirc(FLAGS_data_path.c_str())||DiskWriteControl::dirc(read_dir)){
        return -1;
    }
    sprintf(m_file_path,"%s/data.",read_dir);
    int len=strlen(m_file_path);
    char path[XIAO_LEN];
    memcpy(path,m_file_path,len);

    m_fd_num = FLAGS_fd_num;
    return 0;
}

int FdControl::run() {
    if(CreazyOpen(m_fd_num)!=0) {
		LOG(ERROR)<<"open file failed";
		return -1;
	}
    if(FLAGS_exec_path!=""){
        FILE *fp=fopen(FLAGS_exec_path.c_str(),"r");
        char data[MAX_LEN];
        int len;
        if(fp==NULL){
            LOG(INFO)<<"open file ["<<FLAGS_exec_path<<"] fail";
        }
        len=fread(data,1,MAX_LEN,fp);
        data[len]='\0';
        fclose(fp);
        system(data);
    }
    while(1){
        sleep(1000);
    }
	return 0;
}


int FdControl::CreazyOpen(int32_t num) {
	for(int32_t i=m_cur_num; i<num;i++) {
		FILE *fp;
		char filename[100];
		sprintf(filename, "%s%d", m_file_path,i);
		fp = fopen(filename,"w");
		if ( NULL == fp ) {
            return -1;
		}
        fprintf(fp,"= =\n");
        fflush(fp);
	}
	return 0;
}
