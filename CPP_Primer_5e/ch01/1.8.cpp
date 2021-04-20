

#include <iostream>

using namespace std;



int main()
{

    cout << "/*";
    cout << "*/";
    //cout << /* "*/" */; // error
    cout << /* "*/" /* "/*" */;

    return 0;
}
