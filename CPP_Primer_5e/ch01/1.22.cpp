

#include <iostream>

#include "Sales_item.h"




using namespace std;


int main()
{

    Sales_item item;
    

    if( !(cin >> item) )
    {

        cerr << "errno : Invalid data" << endl;
        return -1;

    }

    Sales_item newItem;

    while( cin >> newItem )
    {
        if( newItem.isbn() != item.isbn() )
        {
            cout << "the back data : " << item << endl;
            item = newItem;
        }
        else
        { 
            item += newItem;
        }
        
 
    }

    cout << "the total record is : " << item << endl;

    return 0;


}