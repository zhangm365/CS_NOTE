


#include <iostream>

using namespace std;


void print( int *p )
{
    if( p )
        cout << *p << endl;

}


void print( const int *begin, const int *end )
{
    while ( begin != end )
    {
        cout << *begin++ << " ";
    }
    
    cout << endl;

}


int main()
{


    int i = 2;
    int arr[2] = { 3, 6 };
    print(i);
    print( begin(arr), end(arr) );

    return 0;

}