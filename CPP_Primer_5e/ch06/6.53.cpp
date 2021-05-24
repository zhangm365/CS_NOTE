


#include <iostream>


using namespace std;

/*
int calc( char *, char * )
{
    cout << "parameter : char *, char * " << endl;
    return 0;
}


int calc( char * const, char * const )  // error: redefinition of ‘int calc(char*, char*)’
{
    cout << "parameter: char * const, char * const" << endl;
    return 0;
}
*/


int calc( const char *, const char * )
{
    cout << "parameter: const char * , const char * " << endl;
    return 0;
}


string::size_type sumLenth( const string &, const string & )
{

}

decltype(sumLenth) *getFunc( const string &)
{
    
}


int main() 
{

    char c1 = 'a';
    char c2 = 'b';

    calc(&c1, &c2);

    const char c3 = 'a';
    const char c4 = 'b';

    calc( &c3, &c4 );
    return 0;


}
