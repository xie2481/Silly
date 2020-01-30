#include "thread.h"
#include "log.h"
#include <exception>

namespace Silly{

static thread_local Thread * currentThread = nullptr;  

Thread::Thread(const std::function<void()> & cb,const std::string & name)
:m_cb(cb),
 m_name(name)
{
    int ret = ::pthread_create(&m_thread,NULL,Thread::run,(void*)this);
    if(ret){
       SILLY_LOG_ERROR("system") << "Thread " << name << " create failure"; 
       throw std::logic_error("Thread " + name + " create failure");
    } 
    currentThread = this;
    pthread_setname_np(m_thread,m_name.substr(0,15).c_str());     
}

void Thread::join(){
   int ret = ::pthread_join(m_thread,NULL); 
    if(ret){
       SILLY_LOG_ERROR("system") << "Thread " << m_name << " join failure"; 
       throw std::logic_error("Thread " + m_name + " join failure");
    } 
    m_thread = 0;
}

Thread::~Thread(){
    if(m_thread){
        ::pthread_detach(m_thread);
    } 
    m_thread = 0;
}
         
Thread * Thread::GetThis(){
    return currentThread;
}

std::string Thread::GetName(){
    if(currentThread){
        return currentThread->m_name;
    } else {
        return "UNKONWN";
    }
} 

void * Thread::run(void * arg){
    Thread * newThread = static_cast<Thread*>(arg);
    std::function<void()> cb;
    cb.swap(newThread->m_cb);
    cb();
    return nullptr;
}

} // end of namespace
