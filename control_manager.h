#ifndef CONTROL_MANAGER
#define CONTROL_MANAGER

#include <map>
#include <string>

#include "common.h"
#include "mem_control.h"
#include "cpu_control.h"
#include "net/net_control.h"
#include "net/net_server.h"
#include "net/port_control.h"
#include "processor_control.h"
#include "fd_control.h"
#include "disk/disk_write.h"
#include "process/pid_control.h"

class ControlManager{
public:
    std::map<std::string,ResourceControl*> m_cons;
    ControlManager();

    int get_control(std::string &name,ResourceControl *&control);

    ~ControlManager();
    
};



#endif
