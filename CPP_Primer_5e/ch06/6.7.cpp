


#include <iostream>

using namespace std;

// 一个函数被调用多少次
size_t count_calls()
{
    static size_t ctr = 0;
    return ++ctr;

}




int main()
{


    for( size_t i = 0 ; i != 10; ++i )
    {
        int ret = count_calls();
        cout << ret << endl;
    }

    return 0;

}