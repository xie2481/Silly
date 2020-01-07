#include "util.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

#include <sys/syscall.h>
#define gettid() syscall(__NR_gettid)

uint32_t Silly::getThreadID(){
    return gettid();       
}
