

#include <iostream>

using namespace std;

int main()
{

    float a = 1.f / 81;
    float b = 0;
    for( int i = 0 ; i < 729; ++i )
        b += a;
    
    printf("%.7g\n", b);    // 9.000023


    double c = 1.0 / 81;
    double d = 0;
    for( int i = 0; i < 729; ++i )
    {
        d += c;
    }

    printf("%.15g\n", d);   // 8.99999999999996


    // 给无符号类型赋值一个超出它表示范围的值, 结果是初始值对无符号类型表示数值总数取模后的余数
    unsigned char ch = -1;  // [char: 0 - 255]，此时输出为255

    printf("unsigned char : %d\n", ch); // 255


    // 有符号类型赋值超出它范围的值，结果是未定义的
    char c2 = 256;

    printf("%d\n", c2);

    return 0;
    
}