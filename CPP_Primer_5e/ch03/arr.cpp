


#include <iostream>
#include <cstring>

using namespace std;

int main()
{

    constexpr unsigned sz = 10; // const expression

    int arr[sz] = {0,1,2,3,4,5,6,7,8,9};

    auto pa(arr);   // pa是一个整型指针, pa指向数组中的第一个元素
    *pa = 15;

    cout << sizeof(arr) << endl;
    cout << arr[0] << endl;

    // int* pb = std::begin(arr);

    // int* pl = std::end(arr);

    // for( ; pb != pl; ++pb )
    //     cout << *pb << endl;

    int *p = &arr[2];

    int i = p[1] ;  // i = *(p+1), 即arr[3]的值

    cout << i << endl;
    cout << p[-2] << endl;  // arr[0]

    char ca[] = { 'a', 'b', 'c', '\0' };
    cout << strlen(ca) << endl;

    return 0;


}