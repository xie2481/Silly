#include "fiber.h"
#include "config.h"
#include "macro.h"

namespace Silly {

    //当前协程
    static thread_local Fiber * cur_fiber = nullptr;
    //主协程
    static thread_local Fiber::ptr main_fiber = nullptr;
    //协程总数量
    static thread_local uint64_t fibers_total = 0;
    //配置默认栈空间
    ConfigVar<uint32_t>::ptr p_fiber_stacksize =
            Config::lookup<uint32_t>("fiber.stacksize",1024 * 1024);

    Fiber::Fiber(std::function<void()> cb, uint32_t stacksize)
    :m_cb(cb),
     m_id(++fibers_total){
        //分配栈空间，如果为0，则用默认配置，否则使用用户指定的大小
        m_size = stacksize ? stacksize : p_fiber_stacksize->getVal();
        m_state = INIT;
        //设置协程上下文
        if(getcontext(&m_ctx)){
            SILLY_ASSERT2(false,"getcontext");
        }
        m_ctx.uc_stack.ss_sp = StackAllocator::Malloc(m_size);
        m_ctx.uc_stack.ss_size = m_size;
        m_ctx.uc_link = nullptr;
        makecontext(&m_ctx,Fiber::Main,0);
        //主协程是否为空
        if(!main_fiber){
            main_fiber = Fiber::ptr(new Fiber());
        }
        //将当前协程设置为工作协程
        SetThis(this);
    }

//切换当前协程运行
    void Fiber::swapIn(){
        //判断异常状态
        SILLY_ASSERT(m_state != TERM
                    && m_state != EXEC
                    && m_state != EXCEPT);
        m_state = EXEC;
        SetThis(this);
        if(swapcontext(&main_fiber->m_ctx,&m_ctx)){
            SILLY_ASSERT2(false,"swapcontext");
        }
    }

//切换当前协程到后台,即切换到主协程运行
    void Fiber::swapOut(){
        //判断异常状态
        SILLY_ASSERT(m_state == EXEC);
        m_state = READY;
        if(swapcontext(&m_ctx,&main_fiber->m_ctx)){
            SILLY_ASSERT2(false,"swapcontext");
        }
    }

//在协程栈空间上,重置当前协程,必须要重新生成ucontext
    void Fiber::reset(std::function<void()> cb){
        m_cb = cb;
        m_state = INIT;
        void * sp = m_ctx.uc_stack.ss_sp;
        if(getcontext(&m_ctx)){
            SILLY_ASSERT2(false,"getcontext");
        }
        m_ctx.uc_stack.ss_size = m_size;
        m_ctx.uc_stack.ss_sp = sp;
        m_ctx.uc_link = nullptr;
        makecontext(&m_ctx,Fiber::Main,0);
        SetThis(this);
    }

//获取当前协程
    Fiber * Fiber::GetThis(){
        if(!cur_fiber){
            return main_fiber.get();
        }
        return cur_fiber;
    }

//设置当前工作协程
    void Fiber::SetThis(Fiber *ptr){
        SILLY_ASSERT(main_fiber.get() != ptr);
        cur_fiber = ptr;
    }

//设置当前协程到后台运行，并置状态为Ready
    void Fiber::YieldToReady(){
        SILLY_ASSERT(cur_fiber);
        cur_fiber->swapOut();
    }

//设置当前协程到后台运行，并置状态为Hold
    void Fiber::YieldToHold(){
        SILLY_ASSERT(cur_fiber);
        cur_fiber->swapOut();
        cur_fiber->m_state = HOLD;
    }

//获取当前线程创建的协程总数
    uint64_t Fiber::GetTotalFibers(){
        return fibers_total;
    }

//用于创建主协程
    Fiber::Fiber()
    :m_id(0){

    }

 //执行协程的函数
    void Fiber::Main(){
        SILLY_ASSERT(cur_fiber->m_cb != nullptr)
        SILLY_ASSERT(cur_fiber->m_state != TERM
                     && cur_fiber->m_state != INIT
                     && cur_fiber->m_state != EXCEPT);
        cur_fiber->m_cb();
    }

    Fiber::~Fiber(){
        SILLY_LOG_DEBUG("system") << "~Fiber()";
        if(cur_fiber == this){
            cur_fiber = nullptr;
        }
        if(m_ctx.uc_stack.ss_sp){
            StackAllocator::Dealloc(m_ctx.uc_stack.ss_sp,m_size);
        }
    }
} // end of namespace