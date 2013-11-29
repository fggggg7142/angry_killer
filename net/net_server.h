#ifndef NET_SERVER
#define NET_SERVER

#include "common.h"

#include "sofa/pbrpc/pbrpc.h"
#include "net_tools.pb.h"

class ServerImpl : public NetTools{
public:

private:
    virtual void trans(google::protobuf::RpcController* controller,
                  const TransRequest* request,
                  TransResponse* response,
                  google::protobuf::Closure* done);
    char m_data[MAX_LEN];
};

class NetServer:public ResourceControl{
public:
    virtual int init();
    virtual int run();
    sofa::pbrpc::RpcServerOptions m_options;
    sofa::pbrpc::RpcServer *m_rpc_server;

    NetTools* m_service;

};

#endif
