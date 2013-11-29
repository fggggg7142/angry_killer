#include "net_server.h"



DECLARE_int32(port);

void ServerImpl::trans(google::protobuf::RpcController* controller,
                  const TransRequest* request,
                  TransResponse* response,
                  google::protobuf::Closure* done){
    if(request->key_size()==0){
        response->set_key(m_data,MAX_LEN);
        response->set_key_size(MAX_LEN);
    }
    done->Run();
}
int NetServer::init(){
    // Define an rpc server.
    m_rpc_server=new sofa::pbrpc::RpcServer(m_options);
    // Start rpc server.
    char hname[1000];
    gethostname(hname, sizeof(hname));
    char addr[1000];
    sprintf(addr,"%s:%d",hname,FLAGS_port);
    if (!m_rpc_server->Start(addr)) {
        SLOG(ERROR, "start server failed");
        return -1;
    }
    
    // Register service.
    int ret=0;
    m_service=new ServerImpl();
    if (!m_rpc_server->RegisterService(m_service)) {
        LOG(ERROR)<<"export service failed "<<ret;
        return -1;
    }
    LOG(INFO)<<"start server at "<<addr;
    return 0;
}

int NetServer::run(){
    while (1) {
        sleep(1000);
    }
    return 0;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
