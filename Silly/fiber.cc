#include "fiber.h"
#include "config.h"
#include "macro.h"

namespace Silly {

    //��ǰЭ��
    static thread_local Fiber * cur_fiber = nullptr;
    //��Э��
    static thread_local Fiber::ptr main_fiber = nullptr;
    //Э��������
    static thread_local uint64_t fibers_total = 0;
    //����Ĭ��ջ�ռ�
    ConfigVar<uint32_t>::ptr p_fiber_stacksize =
            Config::lookup<uint32_t>("fiber.stacksize",1024 * 1024);

    Fiber::Fiber(std::function<void()> cb, uint32_t stacksize)
    :m_cb(cb),
     m_id(++fibers_total){
        //����ջ�ռ䣬���Ϊ0������Ĭ�����ã�����ʹ���û�ָ���Ĵ�С
        m_size = stacksize ? stacksize : p_fiber_stacksize->getVal();
        m_state = INIT;
        //����Э��������
        if(getcontext(&m_ctx)){
            SILLY_ASSERT2(false,"getcontext");
        }
        m_ctx.uc_stack.ss_sp = StackAllocator::Malloc(m_size);
        m_ctx.uc_stack.ss_size = m_size;
        m_ctx.uc_link = nullptr;
        makecontext(&m_ctx,Fiber::Main,0);
        //��Э���Ƿ�Ϊ��
        if(!main_fiber){
            main_fiber = Fiber::ptr(new Fiber());
        }
        //����ǰЭ������Ϊ����Э��
        SetThis(this);
    }

//�л���ǰЭ������
    void Fiber::swapIn(){
        //�ж��쳣״̬
        SILLY_ASSERT(m_state != TERM
                    && m_state != EXEC
                    && m_state != EXCEPT);
        m_state = EXEC;
        SetThis(this);
        if(swapcontext(&main_fiber->m_ctx,&m_ctx)){
            SILLY_ASSERT2(false,"swapcontext");
        }
    }

//�л���ǰЭ�̵���̨,���л�����Э������
    void Fiber::swapOut(){
        //�ж��쳣״̬
        SILLY_ASSERT(m_state == EXEC);
        m_state = READY;
        if(swapcontext(&m_ctx,&main_fiber->m_ctx)){
            SILLY_ASSERT2(false,"swapcontext");
        }
    }

//��Э��ջ�ռ���,���õ�ǰЭ��,����Ҫ��������ucontext
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

//��ȡ��ǰЭ��
    Fiber * Fiber::GetThis(){
        if(!cur_fiber){
            return main_fiber.get();
        }
        return cur_fiber;
    }

//���õ�ǰ����Э��
    void Fiber::SetThis(Fiber *ptr){
        SILLY_ASSERT(main_fiber.get() != ptr);
        cur_fiber = ptr;
    }

//���õ�ǰЭ�̵���̨���У�����״̬ΪReady
    void Fiber::YieldToReady(){
        SILLY_ASSERT(cur_fiber);
        cur_fiber->swapOut();
    }

//���õ�ǰЭ�̵���̨���У�����״̬ΪHold
    void Fiber::YieldToHold(){
        SILLY_ASSERT(cur_fiber);
        cur_fiber->swapOut();
        cur_fiber->m_state = HOLD;
    }

//��ȡ��ǰ�̴߳�����Э������
    uint64_t Fiber::GetTotalFibers(){
        return fibers_total;
    }

//���ڴ�����Э��
    Fiber::Fiber()
    :m_id(0){

    }

 //ִ��Э�̵ĺ���
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