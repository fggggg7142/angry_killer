#ifndef PORT_HELPER
#define PORT_HELPER

#include "net_control.h"
#include "net_server.h"



class PortControl:public ResourceControl {
public:
    virtual int run();
private:
    ResourceControl *m_servers;
};




#endif
