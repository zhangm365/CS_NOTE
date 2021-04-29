# 1. 内联结

## 1. SQL内联结

联结是一种机制，用来在SELECT语句中关联表，因此称为联结。联结可以从不同的表中检索指定的列然后返回一组输出。

基于两个表之间的相等测试，称为等值联结，也称内联结(inner join)。

>   在SELECT语句中加入关键字**INNER JOIN**来指定为内联结。

内联结类型例如下：

```mysql

#从两个表Vendors, Products中检索指定的列。其中vend_name位于表Vendors, prod_name, prod_price位于表Products。
-- 等值连接语法
select vend_name, prod_name, prod_price 
from Vendors, Products 
where Vendors.vend_id = Products.vend_id;	-- 完全限定列名


-- ANSI INNER JOIN 语法
select vend_name, prod_name, prod_price
from Vendors
inner join Products						-- 显示指定内联结
on Vendors.vend_id = Products.vend_id;	  -- 联结条件


```

# 2. 外联结

内联结中将一个表中的行与另一个表中的相关的行相关联，但有时需要包含没有关联行的那些记录。外联结中包含了那些在相关表中没有关联的行。

>   在SELECT语句中加入**OUTER JOIN**关键字指定为外联结，同时必须使用**LEFT**或**RIGHT**关键字指定包含其所有行的表。RIGHT指出OUTER JOIN右边的表，而LEFT指出OUTER JOIN左边的表

例子：对每个顾客下的订单进行计数，包括那些至今没有下单的顾客。

外联结和内联结的对比实例如下：

```mysql

-- 内联结语法, 检索了所有顾客id及其所下的订单相关联的行, 但是不包含没有订单的顾客。

SELECT Customers.cust_id, Orders.order_num
FROM Customers 
INNER JOIN Orders ON Customers.cust_id = Orders.cust_id;	-- 内联结


-- 输出结果如下：
/*
    +------------+-----------+
    | cust_id    | order_num |
    +------------+-----------+
    | 1000000001 |     20005 |
    | 1000000001 |     20009 |
    | 1000000003 |     20006 |
    | 1000000004 |     20007 |
    | 1000000005 |     20008 |
    +------------+-----------+
    5 rows in set (0.00 sec)
*/


-- 外联结可以检索出所有顾客和其订单, 即包含没有订单的顾客。

SELECT Customers.cust_id, Orders.order_num
FROM Customers
LEFT OUTER JOIN Orders ON Customers.cust_id = Orders.cust_id;	-- 外联结, LEFT OUTER JOIN从FROM子句左边的表(Customers)中选择所有行来检索数据

-- 输出结果如下：包含了没有下单的顾客id：1000000002
/*
    +------------+-----------+
    | cust_id    | order_num |
    +------------+-----------+
    | 1000000001 |     20005 |
    | 1000000001 |     20009 |
    | 1000000002 |      NULL |
    | 1000000003 |     20006 |
    | 1000000004 |     20007 |
    | 1000000005 |     20008 |
    +------------+-----------+
    6 rows in set (0.00 sec)

*/

```



