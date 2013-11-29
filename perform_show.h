#ifndef PERFORM_SHOW
#define PERFORM_SHOW


#include "perform_helper.h"
#include "common.h"

#include <pthread.h>


class PerformShow{
public:
    PerformShow();
    static void *thread_run(void *args);
    int start();
    int show();
private:
    PerformHelper *m_helper;
};



#endif
