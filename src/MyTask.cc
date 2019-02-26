/// @file    MyTask.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-24 22:01:51
 
#include "Mylogger.h"
#include "MyTask.h"
#include "CacheManager.h"
#include "Thread.h"
#include "EditDistance.h"
#include "MyDict.h"
#include <iostream>
 
using std::cout;
using std::endl;
using std::set;
using std::string;
using std::shared_ptr;
 
namespace wd {

MyTask::MyTask(const string & request, shared_ptr<TcpConnection> conn)
: _request(request)
, _connection(conn)
{}

void MyTask::process() {
    //从cache里查找
    logDebug("current_thread: %d", current_thread_num::num);
    Cache &cache = CacheManager::getCache(current_thread_num::num);
    string result = cache.query(_request);
    if (result != "\0") {
        _connection->sendInLoop(result);
        cout << ">> Cache already has result" << endl;
        cout << ">> reponse client" << endl;
        return;
    }

    queryIndexTable();
    response();
}

void MyTask::response() {
    string result;
    if(_resultQue.empty()) {
        result = "no answer!";
        _connection->sendInLoop(result);
    }
    else {
        for (size_t i = 0; i < 5; ++i) {
            MyResult myresult = _resultQue.top();
            result = result + "[" + myresult._word + "] ";
            _resultQue.pop();
        }

        _connection->sendInLoop(result);

        cout << ">> current_thread: " << current_thread_num::num << endl;
        Cache & cache = CacheManager::getCache(current_thread_num::num);
        cache.addElem(_request, result);  //在缓存中添加新的查询结果
        cout << ">> respone(): add Cache" << endl;
    }
    cout << ">> reponse client" << endl;
}

void MyTask::queryIndexTable() {
    auto indexTable = MyDict::getInstance()->getIndexTable();
    string ch;
    //MyDict::getInstance()->showIndexTable();

    for (size_t i = 0; i != _request.size();) {
        size_t nBytes = nBytesCode(_request[i]);
        //logDebug("character's bytes = %u.", nBytes);
        ch = _request.substr(i, nBytes);
        //logDebug("find character %s in indexTable", ch.c_str());
        i += nBytes;
        if(indexTable.count(ch)) {
            cout << ">> indexTable has character " << ch << endl;
            statistic(indexTable[ch]);
        }
    }
}

void MyTask::statistic(set<int> & statisticSet) {
    auto dict = MyDict::getInstance()->getDict();
    auto it = statisticSet.begin();
    char bitmap[7000]; //词典大概一共50000多词 7000*8 = 56000
    for(; it != statisticSet.end(); ++it) {
        string rhsWord = dict[*it].first;
        int byteIndex = *it / 8;
        int bitIndex = *it % 8;
        if (bitmap[byteIndex] & 1 << (7 - bitIndex)) continue;
        else bitmap[byteIndex] |= 1 << (7 - bitIndex);
        //logDebug("word: %s.", rhsWord.c_str());
        int idist = distance(rhsWord);  //进行最小编辑距离的计算
        //logDebug("mindist = %d", idist);
        if(idist < 4) {
            MyResult res;
            res._word = rhsWord;
            res._iFreq = dict[*it].second;
            res._iDist = idist;
            //logDebug(">> add a result to resultQue");
            _resultQue.push(res);
        }
    }
}

int MyTask::distance(const string & rhsWord) {
    return ::editDistance(_request, rhsWord);
}

} //end of namespace wd
