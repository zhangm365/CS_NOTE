

#include <iostream>


using namespace std;


void retset( int &i )
{
    i = 0;

}

int main()
{

    
    for( int val; cin >> val; )
    {
        cout << "the origin val " << val << endl;
        retset(val);
        cout << "the reset val is " << val << endl;
    }



    return 0;

}