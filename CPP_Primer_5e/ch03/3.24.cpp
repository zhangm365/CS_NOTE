

#include <iostream>

#include <vector>

#include <string>


using namespace std;



int main()
{


    vector<int> vec;

    for(int x; cin >> x; )
        vec.push_back(x);

    
    // 输出每队相邻元素之和
    for( vector<int>::const_iterator ite = vec.cbegin(); ite != vec.cend(); ++ite )
    {
        if( (ite + 1) == vec.end() ) break;
        cout << *ite + *(ite+1) << endl;
    }
        

    // 依次输出首尾元素之和
    for( auto ite1 = vec.cbegin(), ite2 = vec.cend()-1; ite1 <= ite2; ++ite1, --ite2 )
    {
        
        cout << *ite1 + *ite2 << endl;

    }



    return 0;

}