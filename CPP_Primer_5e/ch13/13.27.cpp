

#include "hasptr.h"

using namespace std;


int main()
{

    HasPtr h1;
    cout << h1.use_count() << endl;
    HasPtr h2(h1);
    HasPtr h3;

    h3 = h1;

    cout << h1.use_count() << " " << h2.use_count() << " " << h3.use_count() << endl;
    return 0;

}