#ifndef FD_CONTROL_H
#define FD_CONTROL_H

#include "common.h"
#include "disk/disk_write.h"

#include <errno.h>


class FdControl:public ResourceControl{
public:
    FdControl();
    virtual int run();
    virtual int init();
private:
    int CreazyOpen(int32_t num);
    int CreazyClose(int32_t num);
private:
    int32_t m_fd_num;
    int32_t m_cur_num;
    char m_file_path[XIAO_LEN];
};

#endif
