#include "../Silly/silly.h"

void fun(){
    SILLY_LOG_INFO("root") << "fun started";
    Silly::Fiber::GetThis()->swapOut();
    SILLY_LOG_INFO("root") << "again enter fun";
    Silly::Fiber::YieldToReady();
}

void fun1(){
    SILLY_LOG_INFO("root") << "context reset";
}

void test(){
   // Silly::Fiber::GetThis();
    Silly::Fiber fiber(fun);
    fiber.swapIn();
    SILLY_LOG_INFO("root") << "swap out from fun";
    fiber.swapIn();
    SILLY_LOG_INFO("root") << "finish fun";
}
int main(){
    /*for(int i = 0; i < 5; ++i){
        Silly::Thread(test,"thread" + std::to_string(i)).join();
    }*/
    test();
    test();
    return 0;
}