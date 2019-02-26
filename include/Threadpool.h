/// @file    Threadpool.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-10 19:57:10
 
#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__
    
#include "TaskQueue.h"
#include <vector>
#include <memory>

namespace wd {

using Task = std::function<void()>;

class Thread;
class Threadpool {
public:
    Threadpool(size_t threadNum = 4, size_t queSize = 10);
    ~Threadpool();

    void addTask(Task &&task);
    void start();
    void stop();

private:
    void threadFunc();
    Task getTask();

    size_t _threadNum;
    size_t _queSize;
    std::vector<std::unique_ptr<Thread>> _threads;
    TaskQueue _taskque;
    bool _isExit;
};

} // end of namespace wd

#endif
