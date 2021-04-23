

#include <iostream>

using namespace std;



int main()
{

    unsigned int u = 10, u2 = 42;

    cout << u2 - u << endl; // 32
    cout << u - u2 << endl; // 4294967264    2^32 = 4294967296


    int i = 10, i2 = 42;    // 

    cout << i2 - i << endl; // 32
    cout << i - i2 << endl; // -32
    cout << i - u << endl;  // 0
    cout << u - i << endl;  // 0

    int a = -1;
    unsigned int b = 1;
    // 当表达式里含有符号和无符号类型时，有符号数会自动转为无符号数。
    cout << a - b << endl;  // 4294967294

    double f = 3.1415e0;
    cout << f << endl;

    //int x = 1024f;  // error


    cout << "-------------" << endl;

    int x = -1;
    int y = -5;

    cout << "-1 % -5 = " << (x % y) << endl; 

    x = 1; y = -5;
    cout << " 1 % -5 = " << (x % y) << endl;
    
    return 0;


}