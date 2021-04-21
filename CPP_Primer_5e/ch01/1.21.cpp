


#include <iostream>

#include "Sales_item.h"

using namespace std;


int main()
{

    Sales_item ite1, ite2;

    cin >> ite1 >> ite2;
    if( ite1.isbn() != ite2.isbn() )
    {
        std::cerr << "errno : Sales_item must be same isbn" << endl;
        return -1; 
    }

    cout << ite1 + ite2 << endl;

    return 0;


}