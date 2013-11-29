#include "net_control.h"


DECLARE_int32(net_in);
DECLARE_int32(net_out);
DECLARE_string(address);
DECLARE_string(server_address);

NetControl::NetControl(){
    m_addrs["bj"]="yx-testing-ps60841.yx01.baidu.com:12321";
    m_addrs["sz"]="szjjh-bvc-sandbox4.szjjh01.baidu.com:12321";
}

int NetControl::run(){
    char data[MAX_LEN];
    
    int len=MAX_LEN;
    if(FLAGS_net_out==-10){
        len=0;
        FLAGS_net_out=-1;
    }else if(FLAGS_net_in==-10){
        FLAGS_net_in=-1;
    }
    sofa::pbrpc::RpcClientOptions client_options;
    client_options.max_throughput_in=FLAGS_net_in;
    client_options.max_throughput_out=FLAGS_net_out;

    sofa::pbrpc::RpcClient rpc_client(client_options);
    sofa::pbrpc::RpcChannelOptions channel_options;

    if(FLAGS_address=="NULL"){
        if(m_addrs.find(FLAGS_server_address)==m_addrs.end()){
            LOG(ERROR)<<"cannot find the server place :"<<FLAGS_server_address.c_str();
            return -1;
        }
        FLAGS_address=m_addrs[FLAGS_server_address];
    }
    LOG(INFO)<<"server is "<<FLAGS_address;
    sofa::pbrpc::RpcChannel rpc_channel(&rpc_client, FLAGS_address, channel_options);

    TransRequest request;
    NetTools_Stub stub(&rpc_channel);
    

    while(1){
        sofa::pbrpc::RpcController cntl;
        cntl.SetTimeout(10000);
        TransResponse response;
        request.set_key(data,len);
        request.set_key_size(len);
        stub.trans(&cntl, &request, &response, NULL);
        if (cntl.Failed())
        {
            LOG(ERROR)<<"request failed: "<<cntl.ErrorText();
            return -1;
        }

    }
    return 0;
}
