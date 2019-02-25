/// @file    main.cc
/// @data    2019-01-11 22:35:09
 
#include "Dictionary.h"
#include <iostream>
 
using std::cout;
using std::endl;
 
int main() {
    Dictionary *dic =  Dictionary::getInstance();
    dic->getEN("./english.txt");
    dic->getZH("./中文");
    dic->store();
    Dictionary::destory();
    return 0;
}
