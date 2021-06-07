

#include "strblob.h"


using namespace std;


int main()
{


    StrBlob S1;
    const StrBlob S2 = { "HELLO", "WORLD", "SYSU" };

    
    S1 = S2;
    S1.push_back("zhang");
    // S2.push_back("mao");
    cout << S1.back() << " " << S2.back() << endl;

    
    return 0;

}