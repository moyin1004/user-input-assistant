/// @file    SpellCorrectServer.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-23 21:05:08
 
#include "SpellCorrectServer.h" 
#include "TcpConnection.h"
#include "Mylogger.h"
#include "MyTask.h"
#include "CacheManager.h"
#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
using std::bind;

namespace wd {

SpellCorrectServer::SpellCorrectServer(std::string &ip, unsigned short port,
                                       int threadNum, int queSize)
: _tcpserver(ip, port)
, _threadpool(threadNum, queSize)
{}

SpellCorrectServer::SpellCorrectServer(std::string &ip, unsigned short port)
: _tcpserver(ip, port)
, _threadpool()
{}

void SpellCorrectServer::start() {
    using namespace std::placeholders;

    _threadpool.start();
    _tcpserver.setConnectionCallback(bind(&SpellCorrectServer::onConnection, this, _1));
    _tcpserver.setMessageCallback(bind(&SpellCorrectServer::onMessage, this, _1));
    _tcpserver.setCloseCallback(bind(&SpellCorrectServer::onClose, this, _1));
    _tcpserver.start();
}

void SpellCorrectServer::stop() {
    _threadpool.stop();
    _tcpserver.stop();
    CacheManager::_timerthread.stop();
}

void SpellCorrectServer::onConnection(const shared_ptr<TcpConnection> &connection) {
    cout << "\n>> " << connection->toString() << " has connection!" << endl;
}

void SpellCorrectServer::onMessage(const shared_ptr<TcpConnection> &connection) {
    string msg = connection->receive();
    logInfo("server receive: %s", msg.c_str());
    
    string data;
    int pos = msg.find('\n');
    if (pos > 0) data = msg.substr(0, pos);
    else data = msg;
    logDebug("need to query data: %s.", data.c_str());
    MyTask task(data, connection);
    _threadpool.addTask(std::bind(&MyTask::process, task));
}

void SpellCorrectServer::onClose(const shared_ptr<TcpConnection> & connection) {
    cout << "\n>> " << connection->toString() << " has closed!" << endl;
}

} //end of namespace wd
