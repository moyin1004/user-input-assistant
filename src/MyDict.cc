/// @file    MyDict.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-26 11:07:09
 
#include "MyDict.h"
#include "Mylogger.h"
#include "Configuration.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
 
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::set;
using std::map;
using std::pair;
using std::ifstream;
 
namespace wd {

MyDict *MyDict::_pInstance = nullptr;
pthread_once_t MyDict::_once = PTHREAD_ONCE_INIT;

MyDict *MyDict::getInstance() {
    pthread_once(&_once, init);
    return _pInstance;
}

void MyDict::init() {
    _pInstance = new MyDict();
    ::atexit(destroy);
}

void MyDict::destroy() {
    if (_pInstance) delete _pInstance;
}

void MyDict::showIndexTable() {
    auto it = _indexTable.begin();
    int T = 50;
    while (T--) {
        cout << it->first << endl;
        ++it;
    }
}

vector<pair<string, int> > &MyDict::getDict() {
    return _dict;
}

map<string, set<int> > &MyDict::getIndexTable() {
    return _indexTable;
}

void MyDict::initDict(const string &endict, const string &zhdict) {
    readFrom(endict);
    readFrom(zhdict);
    for (size_t i= 0; i != _dict.size(); ++i) {
        recordToIndex(i);
    }
}

MyDict::MyDict() {
    initDict(Configuration::getInstance()->getMap()["ENDictPath"],
             Configuration::getInstance()->getMap()["ZHDictPath"]);
}

void MyDict::readFrom(const string dictpath) {
    ifstream ifs(dictpath);
    if (!ifs.good()) {
        logError("dict open error");
    }
    
    string key;
    int value;
    while(ifs >> key >> value) {
        _dict.push_back(make_pair(key, value));
    }
    ifs.close();
}

void MyDict::recordToIndex(int index) {
    string key;
    string word = _dict[index].first;
    for (size_t i = 0; i != word.size(); ++i) {
        char ch = word[i];
        if (ch & (1 << 7)) { //判断是否是ASCII的字母
            //提取utf8编码的中文单个汉字
            if ((ch & 0xF0) == 0xC0 || (ch & 0xF0) == 0xD0) {
                key = word.substr(i, 2);
                ++i;
            }
            else if((ch & 0xF0) == 0xE0) {
                key = word.substr(i, 3);
                i += 2;
            }
            else if ((ch & 0xFF) == 0xF0 ||
                     (ch & 0xFF) == 0xF1 ||
                     (ch & 0xFF) == 0xF2 ||
                     (ch & 0xFF) == 0xF3 ||
                     (ch & 0xFF) == 0xF4 ||
                     (ch & 0xFF) == 0xF5 ||
                     (ch & 0xFF) == 0xF6 ||
                     (ch & 0xFF) == 0xF7) 
            {
                key = word.substr(i, 4);
                i += 3;
            }
            else if((ch & 0xFF) == 0xF8 ||
                    (ch & 0xFF) == 0xF9 ||
                    (ch & 0xFF) == 0xFA ||
                    (ch & 0xFF) == 0xFB)
            {
                key = word.substr(i, 5);
                i += 4;
            }
            else if((ch & 0xFF) == 0xFC) {
                key = word.substr(i, 6);
                i += 5;
            }
        } //end of if
        else key = word.substr(i, 1);
        //logDebug("indexTable key = %s", key.c_str());
        _indexTable[key].insert(index);
    } //end of for
}

} //end of namespace wd
