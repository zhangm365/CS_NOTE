


#include <iostream>

using namespace std;




int main()
{


    int a = 3, b = 4;

    int &r = a;

    cout << sizeof(r) << endl;
    
    decltype(a) c = a; 

    decltype((b)) d = b;    // b is int&

    ++c;

    ++d;

    decltype( a = b ) e = a;    //e : int &


    ++e;

    cout << (c == a) << " " << (b == d) << " " << ( e == a ) << endl; 

    return 0;

}