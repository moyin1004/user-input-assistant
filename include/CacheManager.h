/// @file    CacheManager.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-24 20:10:04
 
#ifndef __WD_CACHEMANAGER_H__
#define __WD_CACHEMANAGER_H__
    
#include "Cache.h"
#include "TimerThread.h"
#include "TimerThread.h"
#include <vector>

namespace wd {

class CacheManager {
    friend class SpellCorrectServer;
public:
    static void initCache(size_t size, const std::string &filename);
    static Cache &getCache(size_t i);
    static void periodicUpdateCaches();

private:
    static std::vector<Cache> _cacheList;
    static TimerThread _timerthread;
};

} //end of namespace wd

#endif
