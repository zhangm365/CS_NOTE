


--insert into t_user select generate_series(1,1000),'username'||round(random()*1000),'password'||round(random()*1000),now(),0;

--insert into t_user select generate_series(1000*i+1,1000*(i+1)),'username'||round(random()*1000),'password'||round(random()*1000),now(),0;

/*
-- 创建表
create table if not exists t_user(
  id serial primary key,
  user_name varchar(255),
  pass_word varchar(255),
  create_time date,
  dr char(1)
)

-- 创建函数
CREATE OR REPLACE FUNCTION insert_data()
RETURNS void AS $$
BEGIN
  INSERT INTO t_user(id, user_name, pass_word, create_time, dr) SELECT 'value_' || generate_series(1,1000),
  'username'||round(random()*1000),'password'||round(random()*1000),now(),0;
END;
$$ LANGUAGE plpgsql;

-- 创建定时任务
CREATE OR REPLACE FUNCTION schedule_insert_data()
RETURNS void AS $$
BEGIN
  LOOP
    PERFORM insert_data();
    PERFORM pg_sleep(10);
  END LOOP;
END;
$$ LANGUAGE plpgsql;

SELECT schedule_insert_data();
*/

-- 创建表
CREATE TABLE t_user (
    id SERIAL PRIMARY KEY,
    column_name VARCHAR(50) NOT NULL
);

-- 创建函数：插入 1000 行数据
CREATE OR REPLACE FUNCTION insert_data()
RETURNS void AS $$
BEGIN
    BEGIN;
    -- 开始一个事务
    INSERT INTO t_user (column_name)
    SELECT 'value_' || generate_series(1, 1000);
    -- 提交事务
    COMMIT;
END;
$$ LANGUAGE plpgsql;

-- 创建定时任务
CREATE OR REPLACE FUNCTION schedule_insert_data()
RETURNS void AS $$
BEGIN
  LOOP
    PERFORM insert_data();
    PERFORM pg_sleep(10);   -- 定时 10s 插入一次数据
  END LOOP;
END;
$$ LANGUAGE plpgsql;

SELECT schedule_insert_data();





/*
-- 授权
grant usage on schema public to test;
grant all privileges on all tables in schema public to test;
grant all privileges on all sequences in schema public to test;
grant select,insert,update,delete on all tables in schema public to test;
grant all on schema public to test;
*/