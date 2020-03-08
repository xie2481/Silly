//
// Created by add on 2020/2/29.
//
#include "../Silly/macro.h"
#include "../Silly/log.h"
#include <vector>
#include <string>

void testBackTrace(){
    SILLY_LOG_INFO("root") << Silly::BackTrace();
}

void fun(){
    testBackTrace();
}

void testAssert(){
    SILLY_ASSERT(1 == 0);
}

int main(){
    testAssert();
    return 0;
}