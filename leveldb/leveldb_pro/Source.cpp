#include <iostream> 
#include <leveldb/db.h>
#include <leveldb/write_batch.h>

int main()
{
	leveldb::DB* db;
	leveldb::Options options;
	options.create_if_missing = true;
	std::string dbpath = "testdb";
	leveldb::Status s = leveldb::DB::Open(options, dbpath, &db);	// ��һ�� leveldb ���ݿ�, ��Ӧ�ڵ�ǰ·���� testdb Ŀ¼
	assert(s.ok());
	std::string key1 = "test";
	std::string val = "test_value";

	s = db->Put(leveldb::WriteOptions(), key1, val);	// �����ݿ��в���(key1, val)��ֵ��
	std::cout << s.ok() << std::endl;
	std::string key2;
	s = db->Get(leveldb::ReadOptions(), key1, &val);	// ��ȡ��key��Ӧ��ֵval
	std::cout << s.ok() << std::endl;
	std::cout << val << std::endl;
	
	/*
	if (s.ok())    // ��key1��Ӧ��ֵ��Ϊkey2��ֵ
	{
		s = db->Put(leveldb::WriteOptions(), key2, val);
		s = db->Delete(leveldb::WriteOptions(), key1);
	}
	*/

	if (s.ok())    // ʹ��WriteBatch��ԭ���Ե��ύһ�����
	{
		leveldb::WriteBatch batch;
		batch.Delete(key1);
		batch.Put(key2, val);
		s = db->Write(leveldb::WriteOptions(), &batch);
	}

	std::cout << s.ok() << std::endl;
	
	s = db->Get(leveldb::ReadOptions(), key2, &val);
	std::cout << s.ok() << " " << val << std::endl;
	delete db;    // close db
	return 0;
}
