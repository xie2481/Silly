#ifndef __SILLY_THREAD_H__
#define __SILLY_THREAD_H__

#include "util.h"
#include <memory>
#include <pthread.h>
#include <functional>
#include <string>
namespace Silly{
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
    };
    
} // end of namespace
#endif

