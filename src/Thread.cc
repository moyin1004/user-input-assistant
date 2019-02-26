/// @file    Thread.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-09 19:27:56
 
#include "Thread.h"
#include <pthread.h>
#include <iostream>
 
namespace current_thread_num {
int num;
}

namespace wd {

Thread::Thread(ThreadCallback &&callback)
: _callback(std::move(callback))
, _pthid(0)
, _isRunning(false)
, _serialNum(0)
{}

void Thread::start() {
    pthread_create(&_pthid, NULL, threadFunc, this);
    _isRunning = true;
}

void * Thread::threadFunc(void *arg) {
    Thread *p = static_cast<Thread *>(arg);
    current_thread_num::num = p->_serialNum;
    if (p) p->_callback();
    return NULL;
}

void Thread::join() {
    if (_isRunning) {
        pthread_join(_pthid, NULL);
        _isRunning = false;
    }
}

Thread::~Thread() {
    if (_isRunning) {
        pthread_detach(_pthid);
        _isRunning = false;
    }
}

void Thread::setSerialNum(int num) {
    _serialNum = num;
}

} //end of namespace wd
