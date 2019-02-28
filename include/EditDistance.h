/// @file    EditDistance.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-28 19:40:29
 
#ifndef __WD_EDITDISTANCE_H__
#define __WD_EDITDISTANCE_H__
    
#include <iostream>
#include <string>

namespace wd {

size_t nBytesCode(const char ch); //获取字节高位开头为1的个数

int editDistance(const std::string &lhs, const std::string &rhs);

} //end of namesapce

#endif
