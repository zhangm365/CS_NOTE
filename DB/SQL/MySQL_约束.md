- [SQL约束](#sql约束)
	- [1. 主键(primary key)](#1-主键primary-key)
		- [1.1 主键需要满足的条件：](#11-主键需要满足的条件)
	- [2. 外键(`foreign key`)](#2-外键foreign-key)
	- [3. 唯一约束(`unique`)](#3-唯一约束unique)
	- [4. 检查约束(check)](#4-检查约束check)
# SQL约束

## 1. 主键(primary key)

主键是一种特殊的约束，用来保证一列(或一组列)中的值是唯一的，而且永不改动。换句话说，表中的一列(或一组列)可以唯一标识表中的每一行。

### 1.1 主键需要满足的条件：

1. 任意两行的主键值都不相同；
2. 每行都具有一个主键值；(列中不允许出现`NULL`)
3. 包含主键值的列从不修改或更新；
4. 主键值不能重用；(如果删除表中的某一行，其主键值不能分配给新行)

代码例子：指定表`Vendors`中的列`vend_id`为该表的主键

```mysql
CREATE TABLE Vendors
(    
    vend_id         CHAR(10)       NOT NULL PRIMARY KEY,    
    vend_name       CHAR(50)       NOT NULL,    
    vend_address    CHAR(50)       NULL,    
    vend_city       CHAR(50)       NULL,    
    vend_state      CHAR(5)        NULL,    
    vend_zip        CHAR(10)       NULL,    
    vend_country    CHAR(50)       NULL
);
/*
    方法1：在此例子中，给表的vend_id列定义添加关键字PRIMARY KEY，使其成为主键。
*/

ALTER TABLE Vendors ADD CONSTRAINT PRIMARY KEY (vend_id);

/*
	方法2 ：使用constraint语法，结果同方法1。
*/
```



## 2. 外键(`foreign key`)

外键是表中的一列，其值必须列在另一个表中的主键中。外键是保证引用完整性的极其重要部分。除此之外，外键可以防止意外删除数据。

代码例子：在表`Orders`顾客`ID`列上定义一个外键，该列的值是表`Customers`的主键值。

```mysql
CREATE TABLE Orders
(    
    order_num    INTEGER    NOT NULL PRIMARY KEY,    
 	order_date   DATETIME   NOT NULL,    
 	cust_id      CHAR(10)   NOT NULL REFERENCES Customers(cust_id)
);

/*
	使用references关键字，表示cust_id中的任何值都必须是表Customers中的cust_id列的值
*/

alter table Orders add foreign key(cust_id) references Customers(cust_id);

```


## 3. 唯一约束(`unique`)

唯一约束保证一列(一组列)中的数据是唯一的。它类似于主键，但和主键有以下重要区别：

1. 表中可以多个唯一约束，但每个表中只有一个主键；
2. 唯一约束列可包含`NULL`值；
3. 唯一约束列可修改或更新；
4. 唯一约束列中的值可以重复使用；
5. 与主键不同，唯一约束不能定义外键；

## 4. 检查约束(check)

检查约束用来保证一列(一组列)中的数据满足一组指定的条件。有以下几个常见用途：

1. 检查最大或最小值；
2. 指定范围；
3. 只允许特定的值；例如，在性别字段中只允许M或F。

```mysql
CREATE TABLE OrderItems
(    
	order_num     INTEGER        NOT NULL,    
	order_item    INTEGER        NOT NULL,    
	prod_id       CHAR(10)       NOT NULL,    
	quantity      INTEGER        NOT NULL 	CHECK (quantity > 0),    
	item_price    decimal(8,2)   NOT NULL
);

/*
	保证插入的行数据时，会保证所有物品数量quantity > 0
*/
# 性别字段中只允许M或F
add constraint check(gender like '[MF]');
```

