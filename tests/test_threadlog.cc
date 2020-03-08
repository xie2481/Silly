//
// Created by add on 2020/2/29.
//
#include "../Silly/log.h"
#include "../Silly/thread.h"
#include "../Silly/util.h"

void fun(){
    SILLY_LOG_INFO("root") << "Thread " << Silly::GetThreadID()
                                  << "sdbafnjenjwenjwngjngkjngjkrngjkngjwngjiengjregnjrgnjergnrjgrjg";
}
void test(){
    for(int i = 0; i < 10; ++i){
        Silly::Thread(fun,"thread" + std::to_string(i)).join();
    }
}

int main(){
    test();
    return 0;
}
