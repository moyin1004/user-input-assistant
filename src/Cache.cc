/// @file    Cache.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-24 20:08:02
 
#include "Mylogger.h"
#include "Cache.h"
#include <iostream>
#include <fstream>
 
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
 
namespace wd {

void Cache::readFromFile(const string &filename) {
    ifstream ifs(filename.c_str());
    if (!ifs.good()) logError(">> open cache file error!");

    string key, value;
    while(ifs >> key) {
        ifs.seekg(1, std::ios::cur);
        getline(ifs, value);
        _hashMap.insert(std::make_pair(key, value));
    }
    ifs.close();
}

void Cache::writeToFile(const string &filename) {
    ofstream ofs(filename.c_str());
    if (!ofs.good()) logError(">> ofstream:write cache file error");

    for (auto it = _hashMap.begin(); it != _hashMap.end(); ++it) {
        ofs << it->first << " " << it->second << endl;
    }
    cout << ">> save Cache to file" << endl;
    ofs.close();
}

void Cache::update(const Cache &rhs) {
    for (auto it = rhs._hashMap.begin(); it != rhs._hashMap.end(); ++it)
        _hashMap.insert(*it);
}

void Cache::addElem(const string & key, const string & value) {
    _hashMap[key] = value;  
}

string Cache::query(const string & word) {
    auto it = _hashMap.find(word);
    if (it != _hashMap.end()) {
        return it->second;
    }
    else {
        return string();
    }
}

void Cache::debug() {
    cout << "Cache begin:" << endl;
    for (auto & elem : _hashMap) cout << elem.first << elem.second << endl;
    cout << "Cache end" << endl;
}

} //end of namespace wd
