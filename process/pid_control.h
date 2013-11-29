#ifndef PID_CONTROL
#define PID_CONTROL

#include "common.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

#include <vector>

class PidControl:public ResourceControl{
public:
    virtual int run();

    static void SignalIntHandler(int sig);
    static std::vector<pid_t> m_pids;
};

#endif
