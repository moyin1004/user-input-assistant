/// @file    EditDistance.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-28 19:47:57
 
#include <iostream>
#include "Mylogger.h"
using std::string;

namespace wd {

//utf-8 编码首字节开头1的个数为该字符占用字节数
size_t nBytesCode(const char ch) {
    if (ch & (1 << 7)) {
        int nBytes = 1;
        for (int i = 0; i != 6; ++i) { //判断该字节位为1的个数
            if (ch & (1 << (6 - i))) {
                ++nBytes;
            }
            else {
                break;
            }
        }
        return nBytes;
    }
    return 1; //1字节字符开头位为0
}

std::size_t length(const string &str) {
    std::size_t len = 0;
    for (std::size_t i = 0; i != str.size();) {
        int nBytes = nBytesCode(str[i]);
        i += nBytes;
        ++len;
    }
    return len; //字符数量 非字节数量
}

int tripleMin(const int &a, const int &b, const int &c) {
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

int editDistance(const string &lhs, const string &rhs) {
    size_t lhs_len = length(lhs);
    size_t rhs_len = length(rhs);
    int editDist[lhs_len + 1][rhs_len + 1] = {0};
    for (size_t i = 0; i <= lhs_len; ++i) {
        editDist[i][0] = i;
    }

    for (size_t i = 0; i <= rhs_len; ++i) {
        editDist[0][i] = i;
    }

    string sublhs, subrhs;
    for (std::size_t dist_i = 1, lhs_i = 0; dist_i <= lhs_len; ++dist_i) {
        size_t nBytes = nBytesCode(lhs[lhs_i]);
        sublhs = lhs.substr(lhs_i, nBytes);
        lhs_i += nBytes;

        for (std::size_t dist_j = 1, rhs_j = 0; dist_j <= rhs_len; ++dist_j) {
            nBytes = nBytesCode(rhs[rhs_j]);
            subrhs = rhs.substr(rhs_j, nBytes);
            rhs_j += nBytes;
            if (sublhs == subrhs) {
                editDist[dist_i][dist_j] = editDist[dist_i - 1][dist_j - 1];
            }
            else {
                editDist[dist_i][dist_j] = tripleMin(
                    editDist[dist_i][dist_j - 1] + 1,
                    editDist[dist_i - 1][dist_j] + 1,
                    editDist[dist_i - 1][dist_j - 1] + 1);
            }
        }
    }
    return editDist[lhs_len][rhs_len];
}

} //end of namespace wd
