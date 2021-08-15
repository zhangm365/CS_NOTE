

#include <iostream>
#include <utility>

template <typename T>
void print( T &val )
{
    val = 3;
    printf("print(T&)\n");
}

template <typename T>
void print( T &&val )
{

    val = 6;
    printf("print(T&&)\n");

}



template <typename T>
void temTest( T &&v )
{

    print(v);   // 总是调用 print( T& )
    print(std::forward<T>(v));    // 完美转发
    print(std::move(v));    // 总是调用 print(T&&)

}

int main()
{

    int i = 0;
    temTest(i);
    std::cout << i << "\n";

    printf("===============\n");
    
    i = 0;
    temTest(std::move(i));
    std::cout << i << "\n";

    return 0;

}