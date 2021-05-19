


#include <iostream>

using namespace std;

// by pointer
void swap( int *p, int *q )
{

    int tmp = *p;
    *p = *q;
    *q = tmp;

}

int main()
{

    int a, b;
    while( cin >> a >> b )
    {
        cout << "the back value is : " << a << " " << b << endl;
        swap(&a, &b);
        cout << "swap : " << a << " " << b << endl;
    }

    return 0;

}