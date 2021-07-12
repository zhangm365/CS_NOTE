


#ifndef _HASPTR_H_

#define _HASPTR_H_


#include <iostream>
#include <string>

using std::string;


// 引用计数类

class HasPtr
{

    public:

        HasPtr( const string &s = string() ) : ps(new string(s)), i(0), use(new std::size_t(1)) {}

        // 拷贝构造函数 : 拷贝三个数据成员，并递增计数器
        HasPtr( const HasPtr &rhs ) : ps(rhs.ps), i( rhs.i), use(rhs.use) { ++*rhs.use; }
        HasPtr &operator=( const HasPtr &rhs );
        ~HasPtr();

        // 返回引用计数
        std::size_t use_count() const { return *use; }

    private:
        string *ps;
        int i;
        std::size_t *use;   // 用来记录有多少个对象共享 *ps 的成员

};


#endif