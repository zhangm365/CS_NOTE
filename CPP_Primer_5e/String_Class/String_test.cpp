

#include "String.h"

int main()
{

    String s1("world");
    String s2("hello");
    std::cout << sizeof(s2) << std::endl;
    String s3 ;
    s3 = s2;
    String s4(s1);
    s4 = s3 = s1;
    std::cout << s1 << " " << s2 << " " << s3 << " " << s4 << std::endl;


    return 0;
}