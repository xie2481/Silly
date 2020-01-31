#include "thread.h"
#include "log.h"
#include <exception>

namespace Silly{

static thread_local Thread * currentThread = nullptr;  

Semaphore::Semaphore(uint32_t count){
    if(::sem_init(&m_semaphore,0,count)){
        SILLY_LOG_ERROR("system") << "Init Semaphore error";
        throw std::logic_error("Init Semaphore error");
    }
}

Semaphore::~Semaphore(){
    if(::sem_destroy(&m_semaphore)){ 
        SILLY_LOG_ERROR("system") << "Destroy Semaphore error";
    } 
}

void Semaphore::wait(){
    if(::sem_wait(&m_semaphore)){
        SILLY_LOG_ERROR("system") << "Semaphore wait error";
        throw std::logic_error("Semaphore wait error");
    } 
}

void Semaphore::notify(){
   if(::sem_post(&m_semaphore) == -1){
       SILLY_LOG_ERROR("system") << "Notify error";
       throw std::logic_error("Notify error");
   } 
}

Mutex::Mutex(){
    if(::pthread_mutex_init(&m_mutex,nullptr)){
        SILLY_LOG_ERROR("system") << "Mutex init error";
        throw std::logic_error("Mutex init error");
    }
}

Mutex::~Mutex(){
    ::pthread_mutex_destroy(&m_mutex);
}

void Mutex::lock(){
   if(::pthread_mutex_lock(&m_mutex)){
       SILLY_LOG_ERROR("system") << "Mutex lock error";
       throw std::logic_error("Mutex lock error");
   } 
}

void Mutex::unlock(){
    if(::pthread_mutex_unlock(&m_mutex)){
       SILLY_LOG_ERROR("system") << "Mutex unlock error";
       throw std::logic_error("Mutex unlock error");
    }
}

RWMutex::RWMutex(){
    if(::pthread_rwlock_init(&m_mutex,nullptr)){
        SILLY_LOG_ERROR("system") << "RWMutex init error";
        throw std::logic_error("RWMutex init error");
    }
}

RWMutex::~RWMutex(){
    ::pthread_rwlock_destroy(&m_mutex);
}

void RWMutex::rdlock(){
    if(::pthread_rwlock_rdlock(&m_mutex)){
        SILLY_LOG_ERROR("system") << "RWMutex read lock error";
        throw std::logic_error("RWMutex read lock error");
    }
}

void RWMutex::wrlock(){
    if(::pthread_rwlock_wrlock(&m_mutex)){
        SILLY_LOG_ERROR("system") << "RWMutex write lock error";
        throw std::logic_error("RWMutex write lock error");
    }
}

void RWMutex::unlock(){
    if(::pthread_rwlock_unlock(&m_mutex)){
        SILLY_LOG_ERROR("system") << "RWMutex unlock error";
        throw std::logic_error("RWMutex unlock error");
    }
}

Thread::Thread(const std::function<void()> & cb,const std::string & name)
:m_cb(cb),
 m_name(name),
 m_semaphore(0)
{
    int ret = ::pthread_create(&m_thread,NULL,Thread::run,(void*)this);
    if(ret){
       SILLY_LOG_ERROR("system") << "Thread " << name << " create failure"; 
       throw std::logic_error("Thread " + name + " create failure");
    } 
    m_semaphore.wait();
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
    currentThread = newThread;
    pthread_setname_np(newThread->m_thread,newThread->m_name.substr(0,15).c_str());     
    std::function<void()> cb;
    cb.swap(newThread->m_cb);
    newThread->m_semaphore.notify();
    cb();
    return nullptr;
}

} // end of namespace
