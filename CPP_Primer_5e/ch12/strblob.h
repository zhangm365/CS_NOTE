

#ifndef _STRBLOB_H
#define _STRBLOB_H

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



#endif