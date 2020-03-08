#include "util.h"
#include "log.h"
#include "fiber.h"
#include <unistd.h>
#include <sys/syscall.h>
#include <malloc.h>
#include <execinfo.h>

#include <sys/syscall.h>
#define gettid() syscall(__NR_gettid)

uint32_t Silly::GetThreadID(){
    return gettid();       
}

uint64_t Silly::GetFiberID() {
    return Fiber::GetThis()->getId();
}

void Silly::BackTrace(std::vector<std::string> &info, int size, int skip) {
    void ** buffer = (void **)malloc(sizeof(void *) * size);
    int nptrs = 0;
    nptrs = backtrace(buffer,size);
    char ** strings = nullptr;
    strings = backtrace_symbols(buffer,size);
    if(strings == NULL){
        SILLY_LOG_ERROR("system") << "No backtrace info";
        return;
    }
    for(int i = skip; i < nptrs;++i){
        info.push_back(strings[i]);
    }
    free(strings);
}

std::string Silly::BackTrace(const std::string & prefix,int size, int skip) {
    std::vector<std::string> info;
    std::string res;
    res += prefix + "\n";
    BackTrace(info,size,skip);
    for(unsigned i = 0; i < info.size();++i){
        res += info[i];
        if(i != info.size() - 1)
            res += "\n";
    }
    return res;
}
