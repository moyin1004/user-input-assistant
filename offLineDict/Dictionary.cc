/// @file    Dictionary.cc
/// @data    2019-01-10 22:37:29

#include "Dictionary.h"
#include "./cppjieba/Jieba.hpp"
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <regex>

using std::string;
using std::vector;
using std::fstream;
using std::ifstream;
using std::stringstream;
using std::cout;
using std::endl;
using std::setfill;
using std::setw;
using std::ios;
using std::regex;
using std::transform;

Dictionary  *Dictionary::_pInstance = nullptr;

Dictionary *Dictionary::getInstance() { 
    if(nullptr == _pInstance) {
        _pInstance = new Dictionary();
    }
    return _pInstance;
}

void Dictionary::destory() {
    if(_pInstance)
         delete _pInstance;
}

void Dictionary::getZH(const string &dirname) {
    struct dirent * file;
    DIR *dir; 
    dir = opendir(dirname.c_str());

    while ((file = readdir(dir)) != NULL) {
        if (strcmp( file->d_name , "." ) == 0 || 
            strcmp( file->d_name , "..") == 0)
            continue;
        string filename = file->d_name;
        filename = "./中文/" + filename; 
        ifstream ifs(filename);
        if (!ifs.good()) {
            cout << "fstream open error" << endl;
            return ;
        }
        cout << filename << endl;
    
        cppjieba::Jieba jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);
        vector<string> words;
        vector<cppjieba::Word> jiebawords;
        string s;
        while(getline(ifs, s)){
            jieba.CutAll(s, words);
            for(auto it = words.begin(); it != words.end(); ++it){
                *it = preprocess(*it, "[^\u4e00-\u9fa5]");
                if ((*it == "\0") | (it->size() < 3)) continue;
                _ZHdic[*it]++;
            }
        }
        ifs.close();
    }
}

void Dictionary::getEN(const string &filename) {
    fstream fs(filename);
    if(!fs.good()) {
        cout << "fstream open " << filename << " error" << endl;
        return ;
    }

    cout << filename << endl;
    string str;
    cout << "start" << endl;
    while(fs >> str) {
        str = preprocess(str, "[0-9]|[^\\w]|_");
        if (str == "\0") continue;
        auto it = _dic.find(str);
        if(it != _dic.end())
            ++it->second;
        else 
            _dic[str] = 1;
    }
    cout << "end" << endl;
    fs.close();
}

void Dictionary::store() {
    fstream fs("../data/ENDict.dat", ios::out); //写入模式，不追加
    if(!fs.good()) {
        cout << "fstream open error" << endl;
        return ;
    }

    for (auto it = _dic.begin(); it != _dic.end(); it++) {
        fs << it->first << " " << it->second  << endl;
    }
    fs.close();

    fs.open("../data/ZHDict.dat", ios::out);
    if(!fs.good()) {
        cout << "fstream open error" << endl;
        return ;
    }

    for (auto it = _ZHdic.begin(); it != _ZHdic.end(); it++) {
        fs << it->first << " " << it->second  << endl;
    }
    fs.close();
}

string Dictionary::preprocess(const string &word, const string &regular) {
    string s = regular;  //处理字符串中的特殊字符
    string str;
    regex r(s);
    str = regex_replace(word, r, "\0");
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
