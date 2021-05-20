

#include <iostream>
#include <string>

using namespace std;


int main( int argc, char *argv[] )
{


    if( argc < 2 )
    {
        cout << "uage : please input more than three parameters\n";
        return -1;
    }

    string s = "";
    
    for( size_t i = 1; i != argc; ++i )
        s += string(argv[i]) + " ";

    cout << s << endl;

    return 0;

}