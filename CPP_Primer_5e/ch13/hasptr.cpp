

#include "hasptr.h"

HasPtr &HasPtr::operator=( const HasPtr &rhs )
{

    ++*rhs.use;     // 先递增右侧运算对象的引用计数
    if( --*use == 0 )
    {
        delete ps;
        delete use;

    }

    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;

    return *this;   // 返回本对象

}


HasPtr::~HasPtr()
{

    if( --*use == 0 )   // 如果引用计数变为 0, 则释放内存
    {
        delete ps;  // 释放 所指向的 string 内存
        delete use; // 释放 计数器内存
    }


}