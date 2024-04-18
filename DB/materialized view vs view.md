
# materialized view vs view

物化视图和普通视图的区别。

## 1. 物化视图（materialized view）

物化视图是一种特殊类型的视图，它将预先计算的查询结果缓存在实际的物理表。

物化视图需要手动或定期执行 `REFRESH MATERIALIZED` 命令刷新引用基表的最新数据。

```sql

-- 创建物化视图
CREATE MATERIALIZED VIEW monthly_sales AS
SELECT DATE_TRUNC('month', order_date) AS month, SUM(total) AS sales
FROM orders
GROUP BY month;


-- 刷新物化视图
REFRESH MATERIALIZED VIEW monthly_sales;

```

## 2. 普通视图（view）

它是一个虚拟表，仅表示对基表中一个查询结果集的引用，不包括实际数据。
在重写器（rewriter）阶段，将视图查询转换为底层基表的查询语句，因此它获取的数据是实时更新的。

```sql

CREATE VIEW employee_info AS
SELECT name, salary
FROM employees;

SELECT * FROM employee_info;

```

## 3. 区别

他们都可以作为缓存优化查询的一种方式，但区别在于：

1. 普通视图是动态的，物化视图是静态的；
2. 普通视图是更轻量级和灵活的，而物化视图需要额外的存储空间和某些数据可能是过时的；
3. 在物化视图中可以直接建立索引列，而普通视图不支持；

## 4. 适用场景

物化视图更适合于 **数据仓库** 场景，在这种场景中频繁查询基表的成本可能更高。
