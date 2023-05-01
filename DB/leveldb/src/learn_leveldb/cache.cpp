/*
    缓存：数据库的内容存储在文件系统的一组文件中，每个文件存储一系列压缩块。
*/
#include <iostream>
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/cache.h"

using namespace std;

int main()
{
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    // 如果数据库已存在，则抛出一个错误
    options.error_if_exists = true;
    
    // 1. cache: 未压缩数据
    options.block_cache = leveldb::NewLRUCache(100*1024*1024);  // 100MB cache

    std::string dbpath = "testdb";

    // step1: 打开一个 leveldb 数据库, 对应于当前路径下 testdb 目录
    leveldb::Status s = leveldb::DB::Open(options, dbpath, &db);   

    // Invalid argument: testdb: exists (error_if_exists is true)
    if(!s.ok()) {
        cerr << s.ToString() << endl;
    }

    // dbpath 存在：Assertion failed: (s.ok()),
    assert(s.ok());
    
    // 切片 Slice: vs string 
    leveldb::Slice s1 = "hello";
    string str("world");
    leveldb::Slice s2 = str;

    cout << "The Slice is: " << s2.ToString() << endl;

    assert(str == s2.ToString());

    

    // populate the database
    leveldb::Slice key1 = "1:3";
    leveldb::Slice key2 = "2:3";
    leveldb::Slice key3 = "2:1";
    leveldb::Slice key4 = "2:100";
    std::string val1 = "one";
    std::string val2 = "two";
    std::string val3 = "three";
    std::string val4 = "four";
    db->Put(leveldb::WriteOptions(), key1, val1);
    db->Put(leveldb::WriteOptions(), key2, val2);
    db->Put(leveldb::WriteOptions(), key3, val3);
    db->Put(leveldb::WriteOptions(), key4, val4);


    leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
    for(it->SeekToFirst(); it->Valid(); it->Next()) {
        cout << it->key().ToString() << ":" << it->value().ToString() << endl;
    }

    // close db
    delete db;    
    delete options.block_cache;
    return 0;

}