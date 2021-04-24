


#include <iostream>


using namespace std;


int main()
{

    
    int i = 0, &r = i;

    
    auto a = r; // a:int

    // auto会忽略顶层const, 但底层const会保存下来
    const int ci = i, &cr = ci;

    auto b = ci;    //int

    auto c = cr;    // int
        
    auto d = &i;    // int *

    auto e = &ci;   // const int * [e是指向整数常量的指针, 对常量对象取地址是一种底层const]

    a = 32;
    b = 33;
    c = 34;
    *d = 35;    // i = 35
    e = &c;
    // *e = 36;  // error: assignment of read-only location ‘*e’
    cout << a << " " << b << " " << c << " " << i << " " << *e << endl;  

    auto &g = ci;
    // auto &h = 42;   // error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’

    const auto &j = 36; // 

    return 0;

}
