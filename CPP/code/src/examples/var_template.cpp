
/*
    可变类型与可变参数个数

*/


#include <bits/stdc++.h>

using namespace std;


// 0个参数，作为递归退出条件
void printX()
{

}




template<typename T, typename... Types>
void printX( const T& firstArg, const Types&... args )
{
    cout << firstArg << endl;
    printX(args...);    // 通过递归调用
}


int maximum(int n)
{
    return n;
}


template<typename... Args>
int maximum(int n, Args... args)
{
    cout << sizeof...(Args) << endl;    //sizeof...() 获取元素个数
    return std::max(n, maximum(args...));
}



int main()
{


    // printX(2.2, bitset<16>(256), "Variadic Template");
    cout << maximum(1, 3, 8, 5, -1, 12, 6) << endl;
    
    return 0;

}