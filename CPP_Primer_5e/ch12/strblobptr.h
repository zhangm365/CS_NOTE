


#ifndef _STRBLOBPTR_H

#define _STRBLOBPTR_H

#include <iostream>
#include <string>
#include <vector>

#include <memory>

#include <initializer_list>

#include <exception>

class StrBlobPtr;

class StrBlob
{

    public:
        typedef std::vector<std::string>::size_type ctype;

        // add for StrBlobPtr
        friend class StrBlobPtr;

        StrBlobPtr begin(); 
        StrBlobPtr end() ;


        // 默认构造函数分配一个空std::vector
        StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}
        
        StrBlob( std::initializer_list<std::string> ls) : data(std::make_shared<std::vector<std::string>>(ls)) {}

        ctype size() const { return data->size(); }
        bool empty() const { return data->empty(); }

        // 添加或删除元素
        void push_back(const std::string &arg) { data->push_back(arg); }
        // 重载 const 的 push_back 没有必要
        // void push_back(const std::string &arg) const { std::cout << "const" << std::endl; data->push_back(arg); }
        void pop_back();

        // 元素访问
        std::string& front();
        const std::string& front() const;

        std::string& back();
        const std::string& back() const;

    private:

        std::shared_ptr<std::vector<std::string>> data;

        // 检查如果data[i]不合法, 则抛出一个异常
        void check( ctype i, const std::string &msg ) const;


};


void StrBlob::pop_back()
{

    check(0, "pop_back on empty StrBlob");
    data->pop_back();

}

std::string& StrBlob::front()
{
    check(0, "front on the empty StrBlob");
    return data->front();
}

std::string& StrBlob::back()
{

    check(0, "back on the empty StrBlob");
    return data->back();

}


const std::string& StrBlob::front() const
{
    
    check(0, "front on the empty StrBlob");
    return data->front();
}

const std::string& StrBlob::back() const
{
    check(0, "back on the empty StrBlob");
    return data->back();

}


void StrBlob::check( ctype i, const std::string &msg ) const
{
    if( i >= data->size() )
        throw std::out_of_range(msg);
}




class StrBlobPtr
{

    public:

        StrBlobPtr() : curr(0) {}
        StrBlobPtr( StrBlob &rhs, std::size_t sz = 0 ) : wptr(rhs.data), curr(sz) {}

        bool operator!=(const StrBlobPtr& p) { return p.curr != this->curr; }

        std::string& deref() const; // 解引用

        StrBlobPtr& incr(); // 前缀递增


    private:

        // 弱引用
        std::weak_ptr<std::vector<std::string>> wptr;
        
        // 在数组中的当前位置
        std::size_t curr;

        // 若检查成功, check 返回一个指向 vector 的 shared_ptr
        std::shared_ptr<std::vector<std::string>>
        check(std::size_t, const std::string& ) const;


};


StrBlobPtr StrBlob::begin() 
{ 
    return StrBlobPtr(*this); 
}


StrBlobPtr StrBlob::end()
{
    
    auto ret = StrBlobPtr(*this, data->size());
    return ret;

}


/*
    由于 weak_ptr 不参与 shared_ptr 的引用计数, StrBlobPtr 所指向的vector 可能被释放了
*/

std::shared_ptr<std::vector<std::string>> 
StrBlobPtr::check( std::size_t i, const std::string &msg ) const
{
    // 判断 wptr 所指向的底层 vector 还存在吗？ 
    auto ret = wptr.lock();

    if( !ret )  // 若 vector 已经销毁, lock 返回为空。
    {
        throw std::runtime_error("Unbound StrBlobPtr");
    }

    if( i >= ret->size() )
    {
        throw std::out_of_range(msg);
    }

    return ret;

}


std::string& StrBlobPtr::deref() const
{

    auto p = check( curr, "dereference past end" );
    
    return (*p)[curr];

}


StrBlobPtr& StrBlobPtr::incr()
{

    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;

}



#endif