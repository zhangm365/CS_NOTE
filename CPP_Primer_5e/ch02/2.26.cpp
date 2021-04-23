


#include <iostream>
#include <typeinfo>

using namespace std;



int main()
{

    int i = 42;
    
    // 允许常量引用绑定到一个非常量对象上
    /*
        编译器会把这条语句变为如下形式：
        const int tmp = i;
        const int &r = tmp;    // 让r1绑定这个临时变量
    */

    const int &r = i, r1 = 0;
    // r = 10;  // 不允许通过r修改i的值

    // cout << typeid(r1).name() << endl;

    //r1 = 8;     // error: assignment of read-only reference ‘r1’

    const int &r2 = r1;

    const int &r3 = 12;

    const int &r4 = r1 * 2;

    const int ci = 10;
    // 不允许将一个非常量引用绑定到const对象上
    //int &r5 = ci;   // error:binding reference of type ‘int&’ to ‘const int’ discards qualifiers

    cout << r1 << " " << r2 << endl;

    return 0;


}
