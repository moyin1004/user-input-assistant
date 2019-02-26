/// @file    Cache.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-24 20:01:34
 
#ifndef __WD_CACHE_H__
#define __WD_CACHE_H__
    
#include <string>
#include <unordered_map>

namespace wd {

class Cache {
public:
    void readFromFile(const std::string &filename);
    void writeToFile(const std::string &filename);
    void update(const Cache & rhs);
    void addElem(const std::string &key, const std::string &value);
    void debug();
    std::string query(const std::string &word);

private:
    std::unordered_map<std::string, std::string> _hashMap;
};

} //end of namesapce wd

#endif
