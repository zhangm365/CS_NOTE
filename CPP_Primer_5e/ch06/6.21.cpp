

#include <iostream>

using namespace std;


int cmp( int v1, const int *v2 )
{

    if( v1 > *v2 ) return v1;
    else return *v2;

}

int main()
{


    int a, b;

    while( cin >> a >> b )
    {
        cout << "the biggest number is : " << cmp(a, &b) << endl;
    }


    return 0;

}