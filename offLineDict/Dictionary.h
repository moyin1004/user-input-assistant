/// @file    Dictionary.h
/// @data    2019-01-10 22:32:28
 
#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <string>
#include <map>

const char* const DICT_PATH = "./dict/jieba.dict.utf8";
const char* const HMM_PATH = "./dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "./dict/user.dict.utf8";
const char* const IDF_PATH = "./dict/idf.utf8";
const char* const STOP_WORD_PATH = "./dict/stop_words.utf8";

class Dictionary {
public:
    static Dictionary *getInstance();
    static void destory();

    void getEN(const std::string &filename);
    void getZH(const std::string &dirname);
    void store();
private:
    static Dictionary *_pInstance;
    std::map<std::string, int> _ZHdic;
    std::map<std::string, int> _dic;
    Dictionary(){};
    std::string preprocess(const std::string &word, const std::string &regular);
};

#endif
