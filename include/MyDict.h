/// @file    MyDict.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-26 10:56:29
 
#ifndef __WD_MYDICT_H__
#define __WD_MYDICT_H__
    
#include <pthread.h>
#include <string>
#include <vector>
#include <set>
#include <map>

namespace wd {

class MyDict {
public:
    static MyDict *getInstance();
    static void destroy();

    void initDict(const std::string &endict, const std::string &zhdict);
    void showIndexTable();
    std::vector<std::pair<std::string, int> > &getDict();
    std::map<std::string, std::set<int> > &getIndexTable();

private:
    MyDict();
    static void init();
    void readFrom(const std::string dictpath);
    void recordToIndex(int index);

private:
    static MyDict *_pInstance;
    static pthread_once_t _once;
    std::vector<std::pair<std::string, int> > _dict;
    std::map<std::string, std::set<int> > _indexTable;
};

} //end of namespace wd

#endif
