
# Database Security—Concepts,Approaches, and Challenges

论文阅读笔记

## 1. Introduction

研究内容主要有两点：

1. 数据机密性
    使用加密技术对数据进行加密，例如 OPE 加密算法。
2. 数据库的数据隐私保护
    使用隐私保护技术

## 2. Database Security

访问控制策略主要分为两类：

1. 自主访问控制 Discretionary Access Control

    权限管理策略包括中心化管理和所有权管理。其中，中心化管理指仅有特权对象可以进行授权和撤销权限。所有权管理指的是对象所有者在数据对象上进行授权和撤销权限的管理。

2. 强制访问控制 Mandatory Access Control
    该策略基于对系统中主体和对象的预定义分类来规范主体对数据的访问。
