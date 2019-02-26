/// @file    Server.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-23 21:17:02
 
#include "Configuration.h"
#include "Mylogger.h"
#include "SpellCorrectServer.h"
#include "CacheManager.h"
#include <iostream>
#include <unistd.h>
#include <string>

using namespace wd;
using std::cin;
using std::cout;
using std::endl;
using std::string;

void myserver() {
    logSetPriority(Mylogger::Priority::INFO);
    Configuration *conf = Configuration::getInstance();
    conf->readConf("../conf/server.conf");
    conf->show();

    string ip(conf->getMap()["ServerIP"]);
    unsigned short port = static_cast<unsigned short>(std::stoi(conf->getMap()["Port"]));
    int threadNum = std::stoi(conf->getMap()["ThreadpoolCap"]);
    int queSize = std::stoi(conf->getMap()["TaskQueSize"]);

    CacheManager::initCache(threadNum, Configuration::getInstance()->getMap()["Cache"]);
    SpellCorrectServer server(ip, port, threadNum, queSize);

    cout << "\n------server start------" << endl << endl;
    server.start();
}

int main() {
    myserver();
    return 0;
}
