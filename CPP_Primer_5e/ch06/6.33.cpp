

#include <iostream>


#include <vector>


using namespace std;
using Iter = vector<int>::const_iterator;

void print( Iter v_beg, Iter v_end )
{
    
    if( v_beg != v_end )
    {
        cout << *v_beg << endl;
        print(++v_beg, v_end);
    }

}


int calc( int, int );


int calc( const int, const int );


int main()
{
    

    vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    print( vec.begin(), vec.end() );

    return 0;

}