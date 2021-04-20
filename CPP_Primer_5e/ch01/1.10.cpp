


#include <iostream>


using namespace std;



int main()
{

    int val = 10;
    while(val >= 0)
    {
        cout << val;
        if( val ) cout << " ";
        --val;
    }
    
    cout << endl;
    return 0;
}


