/// @file    MyTask.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-23 21:38:20
 
#ifndef __WD_MYTASK_H__
#define __WD_MYTASK_H__
    
#include "TcpConnection.h"
#include <queue>
#include <set>

namespace wd {

struct MyResult {
    std::string _word;
    int _iFreq;
    int _iDist;
};

struct MyCompare {
    bool operator()(const MyResult & lhs, const MyResult & rhs) {
    if(lhs._iDist > rhs._iDist) return true;
    else if(lhs._iDist == rhs._iDist && lhs._iFreq < rhs._iFreq) {
        return true;
    }
    else if(lhs._iDist == rhs._iDist &&
            lhs._iFreq == rhs._iFreq && 
            lhs._word > rhs._word)
    {
        return true;
    }
    else
        return false;
    }
};

class Cache;
class MyTask {
public:
    MyTask(const std::string & request, std::shared_ptr<TcpConnection> conn);
    void process();

private:
    void queryIndexTable();
    void statistic(std::set<int> &statisticSet);
    int distance(const std::string &rhs);
    void response();

private:
    std::string _request;
    std::shared_ptr<TcpConnection> _connection;
    std::priority_queue<MyResult, std::vector<MyResult>, MyCompare> _resultQue;
};

} //end of namespace wd

#endif
