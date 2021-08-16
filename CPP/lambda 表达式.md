
- [lambda 表达式](#lambda-表达式)
  - [1. 语法定义](#1-语法定义)
  - [2. 用法](#2-用法)
  - [3. 向 `lambda` 传递参数](#3-向-lambda-传递参数)

# lambda 表达式

## 1. 语法定义

一个 `lambda` 表达式表示一个可调用的代码单元，可以理解为一个未命名的内联函数。
与函数类似，一个 `lambda` 具有一个返回类型、一个参数列表和一个函数体，而 **`lambda` 表达式可以定义在函数内部**。因此，一个 `lambda` 表达式定义如下：
**`[capture list](parameter list)->return type { function body }`**。
>`capture list` (捕获列表) 是一个 `lambda` 所在函数中定义的局部变量的列表，通常为空。
>`return type, parameter list, function body` 和普通函数一样，分别是返回类型、参数列表、函数体。

但与普通函数的区别如下：
1. `lambda` 表达式可以定义在函数内部；
2. `lambda` 必须使用尾置返回类型；
3. `lambda` 的参数列表不能有默认实参。

## 2. 用法

`lambda` 可以省略参数列表和返回类型，但必须包含**捕获列表和函数体**。

```cpp

// 定义一个可调用对象 f, 它不接受参数，返回 42.
auto f = [] { return 42; }

cout << f() << endl; // 输出 42

```

在 `lambda` 中忽略括号和参数列表等价于指定一个空参数列表。因此，当调用 `f` 时，参数列表是空的。
如果忽略返回类型，`lambda` 将根据函数体中的代码推断出返回类型。如果函数体中只有一个 `return` 语句，则返回类型从返回的表达式的类型推断而来。否则，返回类型为 `void`。

## 3. 向 `lambda` 传递参数

```cpp

// 一个带参数的 lambda 函数
[](const string &s1, const string &s2)
{ return s1.size() < s2.size(); }

// 与下面的函数等价
bool isShorter( const string &s1, const string &s2 )
{
    return s1.size() < s2.size();
}

```
