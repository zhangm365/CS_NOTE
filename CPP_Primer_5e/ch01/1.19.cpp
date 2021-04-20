

#include <iostream>


using namespace std;



int main()
{

    int a, b;

    cin >> a >> b;

    if( a > b )
    {
        int tmp = a;
        a = b;
        b = tmp;
    }

    while( a <= b )
    {
        cout << a ;
        if( a != b ) cout << " ";
        a++;
    }

    cout << endl;
    
    return 0;


}