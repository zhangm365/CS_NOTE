# SQL联结

## 1. SQL内联结

联结是一种机制，用来在SELECT语句中关联表，因此称为联结。

基于两个表之间的相等测试，称为等值联结，也称内联结(inner join)。

```mysql

#从两个表Vendors, Products中检索指定的列。其中vend_name位于表Vendors, prod_name, prod_price位于表Products。
select vend_name, prod_name, prod_price 
from Vendors, Products 
where Vendors.vend_id = Products.vend_id;	-- 完全限定列名


-- 写法2
select vend_name, prod_name, prod_price
from Vendors
inner join Products						-- 显示指定内联结
on Vendors.vend_id = Products.vend_id;	  -- 等值联结


```

## 2. 外联结