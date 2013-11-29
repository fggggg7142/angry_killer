#include "processor_control.h"


DECLARE_int32(user_pid);
DECLARE_uint64(dead_time);


int ProcessorControl::run() {
	m_user_pid = FLAGS_user_pid;
	m_dead_time = FLAGS_dead_time;
	if ( SendStopSignal(m_user_pid) != 0 ) {
		LOG(ERROR)<<"send stop signal to pid:["<<m_user_pid<<"] failed";
		return -1;
        }
	//sleep dead_time
	usleep(m_dead_time * 1000);
	if ( SendContSignal(m_user_pid) != 0 ) {
		LOG(ERROR)<<"send continue signal to pid:["<<m_user_pid<<"] failed";
		return -1;
	}
	return 0;
}

int ProcessorControl::SendStopSignal(int32_t pid) {
	if(kill(pid, SIGSTOP) != 0) {
		return -1;
	}
	LOG(INFO)<<"send stop signal to pid:["<<pid<<"] succ";
	return 0;
}
int ProcessorControl::SendContSignal(int32_t pid) {
	if(kill(pid, SIGCONT) != 0) {
		return -1;
	}
	LOG(INFO)<<"send continue signal to pid:["<<pid<<"] succ";
	return 0;
}

