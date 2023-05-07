# coding:utf-8
import time
import psycopg2
from psycopg2.extras import DictCursor

# 连接数据库
conn = psycopg2.connect(
    dbname="test",
    user="biginsights",
    password="biginsights",
    host="192.168.50.81",
    port="5433"
)

# 插入 1000 行数据函数
def insert_data(cursor):
    # 记录开始时间
    start_time = time.time()
    cursor.execute("BEGIN;")
    cursor.execute("INSERT INTO t_user (column_name) SELECT 'value_' || generate_series(1, 1000);")
    cursor.execute("COMMIT;")
    # 记录结束时间
    end_time = time.time()
    elapsed_time = end_time - start_time

    # 打印耗时
    print("Insert 1000 rows into t_user in %.2f seconds." % elapsed_time)

# 每隔10秒插入数据
while True:
    # 获取数据库连接游标
    with conn.cursor(cursor_factory=DictCursor) as cursor:
        # 插入数据
        insert_data(cursor)
        # 提交事务并关闭游标
        conn.commit()

    # 暂停10秒
    time.sleep(10)
