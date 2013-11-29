#ifndef PROCESSOR_CONTROL_H
#define PROCESSOR_CONTROL_H

#include "common.h"
#include "signal.h"


class ProcessorControl:public ResourceControl{
public:
    virtual int run();
private:
    int SendStopSignal(int32_t pid);
    int SendContSignal(int32_t pid);
private:
    int32_t m_user_pid;
    uint64_t m_dead_time;
};

#endif
