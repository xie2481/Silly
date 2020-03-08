#ifndef _SILLY_FIBER_H_
#define _SILLY_FIBER_H_

#include <memory>
#include <functional>
#include <ucontext.h>

namespace Silly{

    //定义栈空间的分配和释放器
    class MallocStackSize{
    public:
         static void * Malloc(int size){
             return malloc(size);
         }

         static void Dealloc(void * p,int size){
             free(p);
         }
    };

    using StackAllocator = MallocStackSize;

    class Fiber{
    public:
        typedef std::shared_ptr<Fiber> ptr;
        enum State{
            INIT,
            EXEC,
            READY,
            HOLD,
            TERM,
            EXCEPT
        };

        Fiber(std::function<void()> cb,uint32_t stacksize = 0);
        //切换当前协程运行
        void swapIn();
        //切换当前协程到后台
        void swapOut();
        //获取当前协程id
        uint64_t getId() const { return m_id;}
        //在协程栈空间上,重置当前协程
        void reset(std::function<void()> cb);

    public:
        //获取当前协程
        static Fiber * GetThis();
        //设置当前工作协程
        static void SetThis(Fiber * ptr);
        //设置当前协程到后台运行，并置状态为Ready
        static void YieldToReady();
        //设置当前协程到后台运行，并置状态为Hold
        static void YieldToHold();
        //获取当前线程创建的协程总数
        static uint64_t GetTotalFibers();
    private:
        //用于创建主协程
        Fiber();
        //执行协程的函数
        static void Main();
    private:
        //协程执行函数
        std::function<void()> m_cb = nullptr;
        //协程id
        uint64_t m_id = 0;
        //协程的上下文
        ucontext_t m_ctx;
        //协程的栈大小
        uint32_t m_size = 0;
        //协程的状态
        State m_state;
    };
} // end of namespace
#endif