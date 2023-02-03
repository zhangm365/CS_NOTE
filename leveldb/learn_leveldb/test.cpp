#include <iostream> 
#include "leveldb/db.h"
#include "leveldb/write_batch.h"

int main()
{
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    std::string dbpath = "testdb";

    // 打开一个 leveldb 数据库, 对应于当前路径下 testdb 目录
    leveldb::Status s = leveldb::DB::Open(options, dbpath, &db);    
    assert(s.ok());
    std::string key1 = "k1";
    std::string val = "v1";

    // 在数据库中插入(key1, val)键值对
    s = db->Put(leveldb::WriteOptions(), key1, val);   

    std::cout << "leveldb.Put status: " << s.ok() << std::endl;
    
    std::string key2 = "k2";

    // 获取键key对应的值val
    s = db->Get(leveldb::ReadOptions(), key1, &val); 

    std::cout << "leveldb.Get status: " << s.ok() << ". The value is: " << val << std::endl;
    
    /*
    if (s.ok())    // 将key1对应的值改为key2的值
    {
        s = db->Put(leveldb::WriteOptions(), key2, val);
        s = db->Delete(leveldb::WriteOptions(), key1);
    }
    */

    if (s.ok())    // 使用WriteBatch类原子性地提交一组更新
    {
        leveldb::WriteBatch batch;
        batch.Delete(key1);    // 删除键key1
        batch.Put(key2, val);    // 插入键值对（key2，val）
        s = db->Write(leveldb::WriteOptions(), &batch);
    }

    std::cout << s.ok() << std::endl;
    
    s = db->Get(leveldb::ReadOptions(), key2, &val);
    std::cout << s.ok() << " " << val << std::endl;
    delete db;    // close db
    return 0;

}