
// find(vec.begin(), vec.begin()+100, val) != (vec.begin()+100)
#include <bits/stdc++.h>

using namespace std;



string BigSum( const string &s1, const string &s2 )
{

    if( s1.size() == 0 ) return s2;

    if( s2.size() == 0 ) return s1;

    string ret;

    int l1 = s1.size(), l2 = s2.size();

    int sign = 0;   // 进位
    int i = l1-1, j = l2-1;
    int val = 0;

    while( i >= 0 && j >= 0 )
    {
        int x = s1[i] - '0';
        int y = s2[j] - '0';

        val = x + y + sign;
        
        //printf("%d\n",(x+y+sign));
        // if( val >= 10 )
        // {
        //     // int tmp = val;
        //     val %= 10;
        //     sign = 1;
            
        // }
        // else
        // {
        //     // val = (x+y+sign);
        //     sign = 0;
        // }
        // int tmp = val;
        sign = val / 10;
        val %= 10;
        
        // printf("val = %d\n", val);
        ret += (val + '0');

        i--;
        j--;
    }


    while( i >= 0 ) 
    {

        val = (sign + s1[i]-'0');
        sign = val / 10;
        ret += ((val % 10) + '0');
        
        i--;
        

    }

    while( j >= 0 ) 
    {
        val = (sign + s2[j]-'0');
        sign = val / 10;
        ret += ((val % 10) + '0');
        j--;

    }


    if(sign)
        ret += (sign + '0');

    reverse(ret.begin(), ret.end());

    return ret;

}


int main()
{


    string s1, s2;

    // cin >> s1 >> s2;
    
    // string ret = BigSum("999", "111");
    
    cout << BigSum("999", "1") << endl;

    cout << BigSum("1", "999") << endl;
    cout << BigSum("123", "111") << endl;

    cout << BigSum("119", "121") << endl;
    cout << BigSum("1234", "123") << endl;
    cout << BigSum("100", "6666") << endl;

    return 0;
}