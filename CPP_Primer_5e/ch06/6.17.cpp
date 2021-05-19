

#include <iostream>
#include <string>

using namespace std;

bool any_capital( const string &s )
{
    auto n = s.size();

    for( decltype(n) i = 0 ; i != n; ++i )
    {
        if(isupper(s[i]))
        {
            return true;
        }        

    }
    
    return false;

}

void to_lowercase( string &s )
{
    for( auto& ch : s )
    {
        ch = tolower(ch);
    }    

}

int main()
{

    for( string s; cin >> s; )
    {
        cout << any_capital(s) << endl;
        to_lowercase(s);
        cout << s << endl;
    }


    return 0;

}