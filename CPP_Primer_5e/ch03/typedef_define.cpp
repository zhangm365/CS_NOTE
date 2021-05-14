


#include <iostream>


// #include <vector>


using namespace std;

#define pd_char char *

typedef char * pt_char;



int main()
{

    char str[] = "abcde";

    const pt_char p1 = &str[0]; // p1 是一个指针常量
    pt_char p3, p4; // p3, p4 都是指针, #define定义达不到此作用
    p3 = &str[3];
    // p4 = str[4]; // error: invalid conversion from ‘char’ to ‘pt_char’ {aka ‘char*’} [-fpermissive]

    const pd_char p2 = &str[1]; // p2 是一个常量指针
    
    *p1 = 'z';

    // p1 = &str[3];   // error: assignment of read-only variable ‘p1’
    // *p2 = 't';      // error: assignment of read-only location ‘* p2’
    
    p2 = &str[2];

    return 0;

}