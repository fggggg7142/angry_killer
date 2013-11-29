#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>


#include "control_manager.h"
#include "perform_show.h"


DECLARE_string(operation);
DECLARE_bool(show_perform);


void print_help(){
    printf(""
        "\n\n"
        "./angry_killer --operation=$1 --$conf=$num\n\n"
        "./angry_killer --operation=cpu --cpu_use=$num (20<$num<98)\n"
        "./angry_killer --operation=mem --mem_size=$num ($num is MB)\n"
        "./angry_killer --operation=disk_write --eve_size=$num\n"
        "./angry_killer --operation=net --server_address=$place(bj or sz) --net_in=$num (set input net $num MB/s)\n"
        "./angry_killer --operation=net --server_address=$place(bj or sz) --net_out=$num (set output net $num MB/s)\n"
        "./angry_killer --operation=fd --fd_num=$num\n"
        "./angry_killer --operation=processor --user_pid=$pid --dead_time=$time\n\n\n"
    "");
}

void set_hook_conf(int argc,char **argv){
    key_t key = ftok("angry_killer", (int)'a');  
    int shmid = shmget(key, MID_LEN, IPC_CREAT | 0600);  
    char* buf = (char*)shmat(shmid, NULL, 0);
    int len=0,cur_len;
    for(int i=1;i<argc;++i){
        cur_len=strlen(argv[i]);
        memcpy(buf+len,argv[i],cur_len);
        len+=cur_len;
        buf[len++]='\n';
    }
    buf[len]='\0';
}

DECLARE_string(so_path);
DECLARE_string(cmd);

int main(int argc,char **argv){
    FLAGS_logtostderr=true;
    FLAGS_log_dir="./log";
    ::google::ParseCommandLineFlags(&argc, &argv, false);
    ::google::InitGoogleLogging(argv[0]);
    int ret;
    ControlManager manager;
    ResourceControl *rc;

    if(FLAGS_operation=="change"){
        set_hook_conf(argc,argv);
        char cmd[MID_LEN];
	std::string so_path="./libakhook.so";
        sprintf(cmd,"./akhook -u %s %s",so_path.c_str(),FLAGS_cmd.c_str());
        system(cmd);
        return 0;
    }
    ret=manager.get_control(FLAGS_operation,rc);

    if(ret!=0){
        print_help();
        return -1;
    }

    if(FLAGS_show_perform){
        PerformShow pshow;
        pshow.start();
    }

    //output current's pid
    pid_t cur_p=getpid();
    printf("%d\n",cur_p);
    fflush(stdout);
    ret=rc->run();

    /*while(1){
        sleep(1000);
    }*/
    delete rc;
    return ret;
}
