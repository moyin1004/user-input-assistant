# user-input-assistant

## Description
* 该项目旨在为用户提供更好的的查询建议，根据输入词在词库中进行查询，提供给用户最相似的结果。
* 使用cppjieba分词库建立中文词典。
* 实现reactor + thread pool组合的并发服务器，完成解耦，由IO线程处理数据的收发，thread pool中的计算线程处理业务逻辑。
* 实现了中英文最小编辑距离算法
* 由unorder_map存储的简易内存cache
* 使用log4cpp日志库记录日志。

## Dependency
* [log4cpp](http://log4cpp.sourceforge.net/)
* [cppjieba](https://github.com/yanyiwu/cppjieba)

## Specifcation
- offLineDict 文件夹属于离线部分，用于根据语料库生成服务器运行所需的中英文字典．
- client 文件夹存放一个简单的客户端程序．

## Future-Update
* 使用[redis数据库](https://redis.io/)作为缓存（利用resis的[C接口](https://github.com/redis/hiredis)）
* 使用LRU缓存算法
