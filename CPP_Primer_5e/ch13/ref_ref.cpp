

#include <iostream>
#include <vector>

template <typename T>
void f( T&& val )
{

    // std::vector<T> vec;
    T t = val;

    t = 6;
    val = 7;
    if( t == val )
    {
        printf("T is &\n");
        printf("%d %d\n", t, val);
    }
    else
    {
        printf("T is NOT &\n");
        printf("%d %d\n", t, val);
    }

    

} 


int main()
{

    int x = 0;
    int y = 0;
    int z = 0;
    int a = 0;

    // typedef int& rf;
    using rf1 = int&;
    using rf2 = int&&;
    using rf3 = int&;
    
    using rf4 = int&&;
    
    rf1 &r1 = x;
    rf2 &r2 = y;
    rf3 &&r3 = z;
    
    // rf4 &&r4 = a;   // cannot bind rvalue reference of type ‘rf4’ {aka ‘int&&’} to lvalue of type ‘int’
    rf4 &&r4 = 1;

    r1 = 3;
    std::cout << x << " " << typeid(rf1).name() << "\n";

    r2 = 5;
    std::cout << y << " " << typeid(rf2).name() << "\n";
    
    r3 = 8;
    std::cout << z << " " << typeid(rf3).name() << "\n";


    std::cout << "-------------\n";

    

    f(15);
    f(x); 
    return 0;

}