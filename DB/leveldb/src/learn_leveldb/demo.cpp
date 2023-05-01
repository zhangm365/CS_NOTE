#include <iostream> 
#include "leveldb/db.h"
#include "leveldb/write_batch.h"

using namespace std;

int main()
{
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    // 如果数据库已存在，则抛出一个错误
    options.error_if_exists = true;

    std::string dbpath = "testdb";

    // step1: 打开一个 leveldb 数据库, 对应于当前路径下 testdb 目录
    leveldb::Status s = leveldb::DB::Open(options, dbpath, &db);   
    
    // Invalid argument: testdb: exists (error_if_exists is true)
    if(!s.ok()) {
        cerr << s.ToString() << endl;
    }

    // dbpath 存在：Assertion failed: (s.ok()),
    assert(s.ok());

    std::string key1 = "k1";
    std::string val1 = "v1";

    // step2: 读写数据库。在数据库中插入(key1, val)键值对
    s = db->Put(leveldb::WriteOptions(), key1, val1);   

    std::cout << "leveldb.Put(k1, v1) status: " << s.ok() << std::endl;
    
    std::string key2 = "k2";

    // 获取键key对应的值val
    s = db->Get(leveldb::ReadOptions(), key1, &val1); 

    std::cout << "leveldb.Get(k1) status: " << s.ok() << ". The value is: " << val1 << std::endl;
    
    /*
    if (s.ok())    // 将key1对应的值改为key2的值
    {
        s = db->Put(leveldb::WriteOptions(), key2, val1);
        s = db->Delete(leveldb::WriteOptions(), key1);
    }
    */

    // 使用WriteBatch类原子性地提交一组更新
    if (s.ok())    
    {
        leveldb::WriteBatch batch;
        batch.Delete(key1);    // 先删除键 key1
        batch.Put(key2, val1);    // 插入键值对（key2，val1）
        s = db->Write(leveldb::WriteOptions(), &batch);
    }

    std::cout << s.ok() << std::endl;
    
    string val2 = "v2";

    string  key3 = "k3", val3 = "v3";
    // 在数据库中插入(key2, val2)键值对，插入相同的 key 时，如果 value 不同，则更新该值。
    s = db->Put(leveldb::WriteOptions(), key2, val2);
    cout << "put the same key in leveldb, the status is: " << s.ok() << endl;

    s = db->Put(leveldb::WriteOptions(), key3, val3);
    
    // step3: iterator：迭代器。
    cout << "---------the Forward iterator start---------------" << endl;
    leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());

    for(it->SeekToFirst(); it->Valid(); it->Next()) {
        cout << it->key().ToString() << ": " << it->value().ToString() << endl;
    }
    
    /*
    // the reverse iterator
    it = db->NewIterator(leveldb::ReadOptions());
    
    for(it->SeekToLast(); it->Valid(); it->Prev()) {
        cout << it->key().ToString() << ": " << it->value().ToString() << endl;
    }
    */

    delete it;

    cout << "---------the iterator end-----------------" << endl;

    // step4: 快照，保存数据库中的一个特定状态。
    leveldb::ReadOptions r_options;
    r_options.snapshot = db->GetSnapshot();

    // other update
    string key4 = "k4", val4 = "v4";
    string key5 = "k5", val5 = "v5";
    db->Put(leveldb::WriteOptions(), key4, val4);
    db->Put(leveldb::WriteOptions(), key5, val5);


    cout << "-------The snapshot start--------" << endl;
    it = db->NewIterator(r_options);
    
    for(it->SeekToFirst(); it->Valid(); it->Next()) {
        cout << it->key().ToString() << ": " << it->value().ToString() << endl;
    }
    
    delete it;
    db->ReleaseSnapshot(r_options.snapshot);
    cout << "-------The snapshot is end-------" << endl;

    cout << "---------The newest state of db start------------" << endl;
    it = db->NewIterator(leveldb::ReadOptions());
    
    for(it->SeekToFirst(); it->Valid(); it->Next()) {
        cout << it->key().ToString() << ": " << it->value().ToString() << endl;
    }
    delete it;
    cout << "---------The newest state of db end-------------" << endl;

    // close db
    delete db;    
    
    return 0;

}