


#include <iostream>

using namespace std;


void swap( int &a, int &b )
{

    int tmp = a; 
    a = b;
    b = tmp;

}



int main()
{


    int a, b;

    while( cin >> a >> b )
    {
        cout << "the origin value is : " << a << " " << b << endl;

        swap(a, b);

        cout << "the swap : " << a << " " << b << endl;


    }
    
    return 0;

}