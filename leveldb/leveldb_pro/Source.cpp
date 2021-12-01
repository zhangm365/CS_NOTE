#include <iostream> 
#include <leveldb/db.h>
#include <leveldb/write_batch.h>

int main()
{
	leveldb::DB* db;
	leveldb::Options options;
	options.create_if_missing = true;
	std::string dbpath = "testdb";
	leveldb::Status s = leveldb::DB::Open(options, dbpath, &db);	// 打开一个 leveldb 数据库, 对应于当前路径下 testdb 目录
	assert(s.ok());

	std::string key1 = "test1";
	std::string val1 = "1_value";

	std::string key2 = "test2";
	std::string val2 = "2_value";

	std::string key3 = "test3";
	std::string val3 = "3_value";

	std::string key4 = "test4";
	std::string val4 = "4_value";

	std::string key5 = "test5";
	std::string val5 = "5_value";

	db->Put(leveldb::WriteOptions(), key1, val1);	// 在数据库中插入(key1, val)键值对
	db->Put(leveldb::WriteOptions(), key2, val2);
	db->Put(leveldb::WriteOptions(), key3, val3);
	db->Put(leveldb::WriteOptions(), key4, val4);
	s = db->Put(leveldb::WriteOptions(), key5, val5);
	
	std::cout << s.ok() << std::endl;
	

	/*
		Print all key,value pairs in a database using the Iteration 
	*/

	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());

	for (it->SeekToFirst(); it->Valid(); it->Next())
	{
		std::cout << it->key().ToString() << ": " << it->value().ToString() << std::endl;
	}

	assert(it->status().ok());
	delete it;

	std::string key = "test";
	std::string val;
	s = db->Get(leveldb::ReadOptions(), key1, &val);	// 获取键key1对应的值val
	
	std::cout << "val = " << val << std::endl;
	
	/*
	if (s.ok())    // 将key1对应的值改为key的值
	{
		s = db->Put(leveldb::WriteOptions(), key, val1);
		s = db->Delete(leveldb::WriteOptions(), key1);
	}
	*/

	if (s.ok())    // 使用类WriteBatch原子性地提交一组更新
	{
		std::cout << "--------WriteBatch--------" << std::endl;
		leveldb::WriteBatch batch;
		batch.Delete(key1);
		batch.Put(key, val);
		s = db->Write(leveldb::WriteOptions(), &batch);
	}
	
	s = db->Get(leveldb::ReadOptions(), key, &val);
	std::cout << s.ok() << " " << key << std::endl;
	delete db;    // close db
	return 0;
}
