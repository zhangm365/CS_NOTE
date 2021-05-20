

#include <iostream>

using namespace std;


// 一个string是否为另一个string的子集
bool str_subrange( const string &s1, const string &s2 )
{

    if( s1.size() == s2.size() )
    {
        return s1 == s2;
    }

    auto size = (s1.size() < s2.size()) ? s1.size() : s2.size();

    for( decltype(size) i = 0; i != size; ++i )
    {
        if( s1[i] != s2[i] )
            return false;
    }

    return true;

}

int main()
{

    string s1("zhangmao");
    string s2("zhang");

    bool ret = str_subrange(s1, s2);
    cout << ret << endl;

    return 0;

}