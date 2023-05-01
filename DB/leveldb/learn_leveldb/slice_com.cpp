#include <iostream> 
#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include "leveldb/comparator.h"

using namespace std;

// 比较器 Comparator: 自定义比较器
class TwoPartComparator : public leveldb::Comparator {
public:
    int Compare(const leveldb::Slice& a, const leveldb::Slice& b) const override {

        long a1, a2, b1, b2;
        ParseKey(a, &a1, &a2);
        ParseKey(b, &b1, &b2);
        // 先比较数值的前半部分，如果它们相同，则比较数值的后半部分
        if(a1 < b1) return -1;
        if(a1 > b1) return 1;
        if(a2 < b2) return -1;
        if(a2 > b2) return 1;
        
        return 0;
    }

    //
    const char* Name() const override { return "TwoPartComparator"; }
    void FindShortestSeparator(std::string*, const leveldb::Slice&) const override { }
    void FindShortSuccessor(std::string*) const override { } 
    
private:
    // 将一个字符串按 ':' 分割为左右两个整数
    static void ParseKey(const leveldb::Slice& k, long* x1, long* x2) {

        string str = k.ToString();
        auto index = str.find_first_of(':');
        *x1 = strtol(str.substr(0,index).c_str(), nullptr, 10);
        *x2 = strtol(str.substr(index+1, str.size()-1).c_str(), nullptr, 10);

    }
};

int main()
{
    leveldb::DB* db;
    TwoPartComparator cmp;
    
    leveldb::Options options;
    options.comparator = &cmp;
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
        cout << it->key().ToString() << "-->" << it->value().ToString() << endl;
    }
    /*
        default output:
            1:3-->one
            2:1-->three
            2:100-->four
            2:3-->two
        
        User-defined cmp output:


    */

    // close db
    delete db;    

    return 0;

}