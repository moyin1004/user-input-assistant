/// @file    SpellCorrectServer.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-23 21:00:35
 
#ifndef __WD_SPELLCORRECTSERVER_H__
#define __WD_SPELLCORRECTSERVER_H__
    
#include "TcpServer.h"
#include "Threadpool.h"
#include <memory>

namespace wd {

class SpellCorrectServer 
: public std::enable_shared_from_this<SpellCorrectServer>
{
public:
    SpellCorrectServer(std::string &ip, unsigned short port, int threadNum, int queSize);
    SpellCorrectServer(std::string &ip, unsigned short port);
    void start();
    void stop();

    void onConnection(const std::shared_ptr<TcpConnection> &connection);
    void onMessage(const std::shared_ptr<TcpConnection> &connection);
    void onClose(const std::shared_ptr<TcpConnection> & connection);

private:
    TcpServer _tcpserver;
    Threadpool _threadpool;
};

} //end of namespace wd

#endif
