/// @file    Thread.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-10 11:04:57
 
#ifndef __THREAD_H__
#define __THREAD_H__
    
#include "Noncopyable.h"
#include <pthread.h>
#include <functional>

namespace current_thread_num {
extern int num;
}

namespace wd {

class Thread
:Noncopyable
{
public:
    using ThreadCallback = std::function<void()>;
    Thread(ThreadCallback &&);
    ~Thread();

    void start();
    void join();

    bool isRunning() const {  return _isRunning;  }
    pthread_t getThreadID() const {  return _pthid;  }
    void setSerialNum(int num);

private:
    static void *threadFunc(void *);

    ThreadCallback _callback;
    pthread_t _pthid;
    bool _isRunning;
    int _serialNum;
};

} //end of namespace wd

#endif
