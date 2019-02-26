/// @file    CacheManager.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-24 20:10:22
 
#include "Configuration.h"
#include "CacheManager.h"
#include <iostream>
 
using std::cout;
using std::endl;
 
namespace wd {

std::vector<Cache> CacheManager::_cacheList;
TimerThread CacheManager::_timerthread(std::bind(&CacheManager::periodicUpdateCaches), 5, 10);

void CacheManager::initCache(size_t size, const std::string &filename) {
    Cache cache;
    cache.readFromFile(filename);

    for (size_t i = 0; i < size; ++i) _cacheList.push_back(cache);
    _timerthread.start();
}

Cache &CacheManager::getCache(size_t i) {
    return _cacheList[i];
}

void CacheManager::periodicUpdateCaches() {
    cout << "\n----Starting update Cahces----" << endl;
    auto it1 =  _cacheList.begin();
    auto it2 = it1 + 1;
    for (; it2 != _cacheList.end(); ++it2) it1->update(*it2);

    it2 = it1 + 1;
    for (; it2 != _cacheList.end(); ++it2) it2->update(*it1);
 
    it1->writeToFile(Configuration::getInstance()->getMap()["Cache"]);

    cout << "----Update End----------------" << endl << endl;;
}

} //end of namespace wd
