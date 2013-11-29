#ifndef DISK_WRITE_H
#define DISK_WRITE_H

#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include "common.h"

class DiskWriteControl:public ResourceControl{
public:
    virtual int init();
    virtual int run();
    static int dirc(const char *src);
private:
    char m_file_path[XIAO_LEN];
};


#endif
