
// 显示每条记录出现多少次

#include <iostream>

#include "Sales_item.h"

using namespace std;



int main()
{

    Sales_item ite;

    if( cin >> ite )
    {

        Sales_item newItem;
        int count = 1;
        while( cin >> newItem )
        {

            if( ite.isbn() == newItem.isbn() )
            {
                ++count;
            }
            else
            {
                cout << ite.isbn() << " occurs " << count << " times" << endl;
                ite = newItem;
                count = 1;
            }

        }        

        cout << ite.isbn() << " occurs " << count << " times" << endl;

    }
    else
    {
        cerr << "Invalid Data" << endl;
        return -1;
    }

    return 0;

}