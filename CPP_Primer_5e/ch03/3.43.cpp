

#include <iostream>


using namespace std;


int main()
{


    int arr[3][4] = {

        { 0, 1, 2, 3 },
        { 4, 5, 6, 7 },
        { 8, 9, 10, 11 }

    };

    

    cout << "---version 1---\n";

    // version 1
    for ( const int (&row)[4] : arr )
    { 
        for ( int col : row )
            cout << col << " ";
    }
    cout << endl;

    cout << "---version 2---\n";

    for( size_t i = 0; i !=3 ; ++i )
    {
        for( size_t j = 0; j != 4; ++j )
        {
            cout << arr[i][j] << " ";
        }
    }
    cout << endl;

    cout << "---version 3---\n";

    for( int (*p)[4] = arr; p != arr+3; ++p )
    {
        for( int *q = *p; q != *p + 4; ++q )
            cout << *q << " ";
    }
    cout << endl;

    cout << "---version 4---\n";

    for ( auto &row : arr )
    {
        for ( auto col : row )
            cout << col << " ";
    }
    cout << endl;



    return 0;

}