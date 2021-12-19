
#include <bits/stdc++.h>
using namespace std;

bool isMatch( const string &str );


int main()
{
    string str;
    cin >> str;

    bool ret = isMatch(str);
    printf("%d\n", ret);

    return 0;
}

bool isMatch( const string &str )
{

    if( str.size() == 0 ) return true;

    stack<char> st;
    // stack<char> st2;

    bool state = true;
    bool flag = false;

    for( auto ch : str )
    {
        char tmp = ' ';
        if( !st.empty() )
            tmp = st.top();

        if( ch >= 'a' && ch <= 'z' )
        {
            // if( state ) st2.pop();
            // if( !state && !st2.empty() ) return false;
            // st2.push(ch);
            if( !state ) return false;
            state = false;
            continue;
        }   


        switch (ch)
        {
            
            case ' ':
            case '\t':
            case '\n':
                break;

            case '(':
            case '{':
            case '[':

                if( flag ) return false;
                state = true;
                st.push(ch);
                break;

            case ')':
                if( st.empty() ) return false;
                st.pop();
                if( tmp != '(' ) return false;
                state = true;
                flag = true;
                break;

            case '}':
                if( st.empty() ) return false;
                st.pop();
                if( tmp != '{' ) return false;
                state = true;
                break;

            case ']':
                if( st.empty() ) return false;
                st.pop();
                if( tmp != '[' ) return false;
                state = true;

                break;

            default:
                return false;
        }
    }

    return st.empty();


}


