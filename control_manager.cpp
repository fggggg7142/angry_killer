#include "control_manager.h"

ControlManager::ControlManager(){
    m_cons["NULL"] = new ResourceControl();
    m_cons["cpu"]=new CpuControl();
    m_cons["mem"]=new MemControl();
    m_cons["net"]=new NetControl();
    m_cons["server"]=new NetServer();
    m_cons["processor"] = new ProcessorControl();
    m_cons["fd"] = new FdControl();
    m_cons["disk_write"] = new DiskWriteControl();
    m_cons["pid"] = new PidControl();
    m_cons["port"] = new PortControl();
}

int ControlManager::get_control(std::string &name,ResourceControl *&control){
    if(m_cons.find(name)==m_cons.end()){
        return -1;
    }
    control=m_cons[name];
    return control->init();
}

ControlManager::~ControlManager(){
    for(std::map<std::string,ResourceControl*>::iterator it=m_cons.begin();it!=m_cons.end();++it){
        delete it->second;
    }
}

