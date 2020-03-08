#ifndef _SILLY_FIBER_H_
#define _SILLY_FIBER_H_

#include <memory>
#include <functional>
#include <ucontext.h>

namespace Silly{

    //����ջ�ռ�ķ�����ͷ���
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
        //�л���ǰЭ������
        void swapIn();
        //�л���ǰЭ�̵���̨
        void swapOut();
        //��ȡ��ǰЭ��id
        uint64_t getId() const { return m_id;}
        //��Э��ջ�ռ���,���õ�ǰЭ��
        void reset(std::function<void()> cb);

    public:
        //��ȡ��ǰЭ��
        static Fiber * GetThis();
        //���õ�ǰ����Э��
        static void SetThis(Fiber * ptr);
        //���õ�ǰЭ�̵���̨���У�����״̬ΪReady
        static void YieldToReady();
        //���õ�ǰЭ�̵���̨���У�����״̬ΪHold
        static void YieldToHold();
        //��ȡ��ǰ�̴߳�����Э������
        static uint64_t GetTotalFibers();
    private:
        //���ڴ�����Э��
        Fiber();
        //ִ��Э�̵ĺ���
        static void Main();
    private:
        //Э��ִ�к���
        std::function<void()> m_cb = nullptr;
        //Э��id
        uint64_t m_id = 0;
        //Э�̵�������
        ucontext_t m_ctx;
        //Э�̵�ջ��С
        uint32_t m_size = 0;
        //Э�̵�״̬
        State m_state;
    };
} // end of namespace
#endif