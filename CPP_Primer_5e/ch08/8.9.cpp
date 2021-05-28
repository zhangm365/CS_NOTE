

#include <iostream>

#include <sstream>

using namespace std;

istream &print( istream &is )
{

    string buf;
    while( is >> buf )
    {
        cout << buf << endl;
    }

    return is;

}



int main()
{

    istringstream iss("hello");
    print(iss);
    return 0;

}