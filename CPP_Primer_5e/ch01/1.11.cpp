


#include <iostream>


using namespace std;

int main()
{

    int a, b;
    cout << "please input the two number :" << endl;
    cin >> a >> b;

    while ( a <= b )
    {
        cout << a  << " ";
        ++a;
    }
    
    cout << endl;
    return 0;


}