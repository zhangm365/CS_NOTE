

#include <iostream>


using namespace std;



int main()
{

    int i, *const cp = &i;
    int *p1, *const p2 = &i;

    const int ic = 10, &rc = ic;

    const int *const p3 = &i;

    const int *p ;

    i = ic;
    // p1 = p3;    // error:invalid conversion from ‘const int*’ to ‘int*’ [-fpermissive]
    // p1 = &ic;    // error: invalid conversion from ‘const int*’ to ‘int*’ [-fpermissive]
    // p3 = &ic;   // error: assignment of read-only variable ‘p3’
    // p2 = p1;    // error: assignment of read-only variable ‘p2’
    // ic = *p3;   // error: assignment of read-only variable ‘ic’

    return 0;

}
