

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <initializer_list>

#include <exception>


using namespace std;

class StrBlob
{

    public:
        typedef vector<string>::size_type ctype;

        // 默认构造函数分配一个空vector
        StrBlob() : data(make_shared<vector<string>>()) {}
        
        StrBlob(initializer_list<string> ls) : data(make_shared<vector<string>>(ls)) {}

        ctype size() const { return data->size(); }
        bool empty() const { return data->empty(); }

        // 添加或删除元素
        void push_back(const string &arg) { cout << "no" << endl; data->push_back(arg); }
        // 重载 const 的 push_back 没有必要
        // void push_back(const string &arg) const { cout << "const" << endl; data->push_back(arg); }
        void pop_back();

        // 元素访问
        string& front();
        const string& front() const;

        string& back();
        const string& back() const;

    private:

        shared_ptr<vector<string>> data;

        // 检查如果data[i]不合法, 则抛出一个异常
        void check( ctype i, const string &msg ) const;


};


void StrBlob::pop_back()
{

    check(0, "pop_back on empty StrBlob");
    data->pop_back();

}

string& StrBlob::front()
{
    check(0, "front on the empty StrBlob");
    return data->front();
}

string& StrBlob::back()
{

    check(0, "back on the empty StrBlob");
    return data->back();

}


const string& StrBlob::front() const
{
    
    check(0, "front on the empty StrBlob");
    return data->front();
}

const string& StrBlob::back() const
{
    check(0, "back on the empty StrBlob");
    return data->back();

}




void StrBlob::check( ctype i, const string &msg ) const
{
    if( i >= data->size() )
        throw out_of_range(msg);
}




int main()
{


    StrBlob S1;
    const StrBlob S2 = { "HELLO", "WORLD", "SYSU" };

    
    S1 = S2;
    S1.push_back("zhang");
    S2.push_back("mao");
    cout << S1.back() << " " << S2.back() << endl;

    
    return 0;

}