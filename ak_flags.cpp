#include <gflags/gflags.h>

DEFINE_string(operation,"kong","cpu or mem,fd,net,disk_write,port,processor,change; set mem,or cpu,fd,net,disk_write,port,processor and change the return value");
DEFINE_string(write_path,"write","do not change");
DEFINE_int32(eve_size,10,"every seconds in MB");
DEFINE_int32(user_pid,10000,"input the PID which you want to Apparent Death");
DEFINE_uint64(dead_time, 10000, "Apparent Death's time [ms]");
DEFINE_bool(show_perform,true,"show perform");
DEFINE_int32(cpu_fre,100,"in ms, do not change");
DEFINE_int32(cnum,6,"do not change");
DEFINE_int32(begin,0,"input net, in MB/s");
DEFINE_int32(end,0,"output net, in MB/s");
DEFINE_int32(net_in,-10,"input net, in MB/s");
DEFINE_int32(net_out,-10,"output net, in MB/s");
DEFINE_string(address,"NULL","server's real address");
DEFINE_string(server_address,"bj","server's place, bj(����) or sz(����)");
DEFINE_int32(port,12321,"the net server port");
DEFINE_int32(fd_num,1000,"input the num of fd");
DEFINE_string(fd_path,"fd","do not change");
DEFINE_string(exec_path,"","child process's conf");
DEFINE_string(data_path,"./angry_killer_data","tool's workingdir");
DEFINE_double(cpu_use,10,"set cpu use frequency");
DEFINE_int32(sleep_eve,30,"do not change");
DEFINE_int32(thread_num,5,"do not change");
DEFINE_int32(wen_time,10,"do not change");
DEFINE_uint64(mem_size,1,"memory size, in MB");
DEFINE_string(set_malloc_value, "NULL", "please set malloc's return value[string]");
DEFINE_int32(set_connect_value, -100, "please set connect's return value[int]");
DEFINE_int32(set_send_value, -100, "please set send's return value[int]");
DEFINE_int32(set_recv_value, -100, "please set recv's return value[int]");
DEFINE_int32(set_write_value, -100, "please set write's return value[int]");
DEFINE_int32(set_read_value, -100, "please set read's return value[int]");
DEFINE_string(set_popen_value, "NULL", "please set popen's return value[string]");
DEFINE_int32(set_open_value, -100, "please set open's return value[int]");
DEFINE_int32(set_fork_value, -100, "please set fork's return value[int]");
DEFINE_int32(set_fread_value, -100, "please set fread's return value[int]");
DEFINE_int32(set_fwrite_value,-100, "please set fwrite's return value[int]");
DEFINE_int32(set_pthread_create_value,-100, "please set pthread_create's return value[int]");
DEFINE_int32(set_mkfifo_value,-100, "please set mkfifo's return value[int]");
DEFINE_int32(set_pipe_value,-100, "please set pipe's return value[int]");
DEFINE_int32(set_execl_value,-100, "please set execl's return value[int]");
DEFINE_int32(set_link_value,-100, "please set link's return value[int]");
DEFINE_int32(set_fstat_value,-100, "please set fstat's return value[int]");
DEFINE_string(set_dlopen_value, "NULL", "please set dlopen's return value[string]");
DEFINE_string(set_dlsym_value, "NULL", "please set dlsym's return value[string]");
DEFINE_int64(pid_size,-1,"process num");


DEFINE_string(so_path,"./libakhook.so","");
DEFINE_string(cmd,"ls -l","");

DEFINE_int32(malloc_flag,-1,"malloc_flag");
DEFINE_int32(popen_flag,-1,"popen_flag");
DEFINE_int32(send_flag,-1,"send_flag");
DEFINE_int32(recv_flag,-1,"recv_flag");
DEFINE_int32(write_flag,-1,"write_flag");
DEFINE_int32(open_flag,-1,"open_flag");
DEFINE_int32(fork_flag,-1,"fork_flag");
DEFINE_int32(fread_flag,-1,"fread_flag");
DEFINE_int32(read_flag,-1,"read_flag");
DEFINE_int32(fwrite_flag,-1,"fwrite_flag");
DEFINE_int32(pthread_create_flag,-1,"pthread_create_flag");
DEFINE_int32(mkfifo_flag,-1,"mkfifo_flag");
DEFINE_int32(pipe_flag,-1,"pipe_flag");
DEFINE_int32(execl_flag,-1,"execl_flag");
DEFINE_int32(link_flag,-1,"link_flag");
DEFINE_int32(fstat_flag,-1,"fstat_flag");
DEFINE_int32(dlopen_flag,-1,"dlopen_flag");
DEFINE_int32(dlsym_flag,-1,"dlsym_flag");
