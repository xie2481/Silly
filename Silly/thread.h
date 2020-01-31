#ifndef __SILLY_THREAD_H__
#define __SILLY_THREAD_H__

#include "util.h"
#include <memory>
#include <pthread.h>
#include <functional>
#include <string>
#include <semaphore.h>
namespace Silly{

    class Semaphore
    {
        public:
            Semaphore(uint32_t count);
            ~Semaphore();

            void wait();
            void notify();

        private:
            Semaphore(const Semaphore &) = delete;
            Semaphore(const Semaphore &&) = delete;
            Semaphore & operator=(const Semaphore &) = delete;
        
        private:
            sem_t m_semaphore;
    };

    template<class T>
    class ScopeMutexLock
    {
        public:
          ScopeMutexLock(T & mutex)
          :m_mutex(mutex),
           m_locked(false){
            lock();
          }

          ~ScopeMutexLock(){
            unlock();
          }
           
          void lock(){
            if(!m_locked){
                m_mutex.lock();
                m_locked = true;
            }
          }
          void unlock(){
            if(m_locked){
                m_mutex.unlock();
                m_locked = false;
            }
          } 
        private:
            T & m_mutex;
            bool m_locked;
    };

    class Mutex{
        public:
            typedef ScopeMutexLock<Mutex> MutexLock;
            Mutex();
            ~Mutex();

            void lock();
            void unlock();

        private:
            Mutex(const Mutex &) =delete;
            Mutex(const Mutex &&) = delete;
            Mutex & operator=(const Mutex &) = delete;
    
        private:
            pthread_mutex_t m_mutex;
    };

    template<class T>
    class ReadScopeMutexLock
    {
        public:
          ReadScopeMutexLock(T & mutex)
          :m_mutex(mutex),
           m_locked(false){
            lock();
          }

          ~ReadScopeMutexLock(){
            unlock();
          }
           
          void lock(){
            if(!m_locked){
                m_mutex.rdlock();
                m_locked = true;
            }
          }
          void unlock(){
            if(m_locked){
                m_mutex.unlock();
                m_locked = false;
            }
          } 
        private:
            T & m_mutex;
            bool m_locked;
    };

    template<class T>
    class WriteScopeMutexLock
    {
        public:
          WriteScopeMutexLock(T & mutex)
          :m_mutex(mutex),
           m_locked(false){
            lock();
          }

          ~WriteScopeMutexLock(){
            unlock();
          }
           
          void lock(){
            if(!m_locked){
                m_mutex.wrlock();
                m_locked = true;
            }
          }
          void unlock(){
            if(m_locked){
                m_mutex.unlock();
                m_locked = false;
            }
          } 
        private:
            T & m_mutex;
            bool m_locked;
    };
   
    class RWMutex
    {
        public:
            typedef ReadScopeMutexLock<RWMutex> ReadLock;
            typedef WriteScopeMutexLock<RWMutex> WriteLock;
            RWMutex();
            ~RWMutex();

            void rdlock();
            void wrlock();
            void unlock();

        private:
          pthread_rwlock_t m_mutex;
    }; 

    class Thread
    {
        public:
            typedef std::shared_ptr<Thread> ptr;
            Thread(const std::function<void()> & cb,const std::string & name);
            std::string getName() const { return m_name;}
            void join();
            uint32_t getID() const { return Silly::getThreadID(); }
            ~Thread();
             
            static Thread * GetThis();
            static std::string GetName();
            static void * run(void * arg);
        private:
            Thread(const Thread &) = delete;
            Thread(const Thread &&) = delete;
            Thread & operator=(const Thread &) = delete;
    
        private:
            std::function<void()> m_cb;
            pthread_t m_thread;
            std::string m_name;
            Semaphore m_semaphore;
    };
    
} // end of namespace
#endif

