#ifndef NET_HELPER
#define NET_HELPER

#include "gflags/gflags.h"
#include "common.h"
#include <stdio.h>
#include "net_tools.pb.h"
#include "sofa/pbrpc/pbrpc.h"



class NetControl:public ResourceControl {
public:
    NetControl();
    virtual int run();
private:
    std::map<std::string,std::string> m_addrs;
};




#endif
