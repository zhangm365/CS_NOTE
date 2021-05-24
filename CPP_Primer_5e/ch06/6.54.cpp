

#include <iostream>

#include <vector>

using namespace std;

inline int func( int a, int b );

typedef decltype(func) fp;


inline int NumAdd( const int a, const int b) { return a + b; }
inline int NumSub( const int a, const int b) { return a - b; }
inline int NumMul( const int a, const int b) { return a * b; }
inline int NumDiv( const int a, const int b) { return a / b; }

vector<fp*> vec = { NumAdd, NumSub, NumMul, NumDiv };   // vector中的每个元素是个函数指针

int main()
{

    for( auto ite = vec.cbegin(); ite != vec.cend(); ++ite )
    {

        cout << (*ite)( 3, 3 ) << endl;

    }

    return 0;

}
