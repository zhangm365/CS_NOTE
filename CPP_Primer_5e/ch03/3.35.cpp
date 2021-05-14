

#include <iostream>


using namespace std;


int main()
{

    
    constexpr unsigned sz = 10;

    int arr[sz];

    int *p = arr;

    int *end = arr + sz;

    for ( ; p != end; ++p )
        *p = 0;


    for ( auto i : arr ) 
        cout << i << " ";
    cout << endl;
    
    return 0;

}