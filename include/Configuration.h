/// @file    Configuration.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-23 22:22:07
 
#ifndef __WD_CONFIGURATION_H__
#define __WD_CONFIGURATION_H__
    
#include <map>
#include <string>

namespace wd {

class Configuration {
public:
    static Configuration *getInstance();
    static void destroy();

    bool readConf(const std::string &);
    void show();
    std::map<std::string, std::string> &getMap();

private:
    Configuration() {}
    ~Configuration() {};
    static void init();

    static pthread_once_t _once;
    std::map<std::string, std::string> _map;
    static Configuration *_pInstance;
};

} //end of namespace wd

#endif
