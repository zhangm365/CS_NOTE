# SQL视图

视图是虚拟的表。与包含数据的表不一样，它只包含使用时动态检索数据的查询。所以，视图仅仅是用来查看存储在别处数据的一种设施。

视图本身不包含任何列或数据，因此它返回的数据是从其他表中检索出来的。

视图的好处：

1.  重用SQL语句；
2.  简化复杂的SQL语句。在编写查询后，可以方便重用而不必知道其基本查询细节；
3.  使用表的一部分而不是整个表；这样可以起到保护数据的作用。即可以授权用户访问表的特定部分的权限，而不是整个表的访问权限；



```mysql
-- 语法规则
CREATE VIEW viewname
SELECT ID FROM tablename
WHERE ...;


-- 原来用法: 查询购买产品id为"RGAN01"的顾客
SELECT cust_name, cust_contact
FROM Customers, Orders, OrderItems
WHERE Customers.cust_id = Orders.cust_id 
AND OrderItems.order_num = Orders.order_num 
AND prod_id = 'RGAN01';

-- 具体用法: 创建名为ProductCustomer的视图。它联结了三个表, 返回已订购任意产品的所有顾客列表。
CREATE VIEW ProductCustomer AS
SELECT cust_name, cust_contact, prod_id
FROM Customers, Orders, OrderItems
WHERE Customers.cust_id = Orders.cust_id
AND Orders.order_num = OrderItems.order_num;

-- 使用视图：查询订购了产品RGAN01的顾客
SELECT cust_name, cust_contact
FROM ProductCustomers	-- 已创建的视图名
WHERE prod_id = 'RGAN01';

-- 删除视图
DROP VIEW ProductCustomer;

```

