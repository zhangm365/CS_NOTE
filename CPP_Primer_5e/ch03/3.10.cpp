

#include <iostream>

#include <string>


using namespace std;


int main()
{

    string str;
    string res;
    while( getline(cin, str) )
    {

        for( auto &c : str )
        {
            if( !ispunct(c) )
            {
                res.append(1, c);
            }
        }

        cout << res << endl;
    }


    return 0;

}