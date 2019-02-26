/// @file    Configuration.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-23 22:28:13
 
#include "Mylogger.h"
#include "Configuration.h"
#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream> 

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::ifstream;
using std::istringstream;
 
namespace wd {

Configuration *Configuration::_pInstance = nullptr;
pthread_once_t Configuration::_once = PTHREAD_ONCE_INIT;

bool Configuration::readConf(const string &filename) {
    ifstream ifs(filename.c_str());
    if (!ifs.good()) {
        logError(">> file read");
        return false;
    }
    string line;
    while (getline(ifs, line)) {
        istringstream iss(line);
        string key, value;
        iss >> key >> value;
        _map.insert(make_pair(key, value));
    }
    ifs.close();
    return true;
}

void Configuration::show() {
    map<string, string>::const_iterator it = _map.begin();
    for(; it != _map.end(); ++it) {
        cout << it->first << " --> " << it->second << endl;
    }
}

map<string, string> &Configuration::getMap() {
    return _map;
}

Configuration *Configuration::getInstance() {
    pthread_once(&_once, init);
    return _pInstance;
}

void Configuration::init() {
    _pInstance = new Configuration();
    ::atexit(destroy);
}

void Configuration::destroy() {
    if (_pInstance) delete _pInstance;
}

} //end of namespace wd
