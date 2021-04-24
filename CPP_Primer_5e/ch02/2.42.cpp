

#include "Sales_data.h"


int main()
{

    Sales_data it1;
    cout << "Please input the Sales_data : " << endl;
    double price;

    if( cin >> it1.bookNo >> it1.units_sold >> price )
    {

        it1.revenue = it1.units_sold * price;

        Sales_data it2;

        while( cin >> it2.bookNo >> it2.units_sold >> price )
        {
            it2.revenue = it2.units_sold * price;

            if( it1.bookNo == it2.bookNo )
            {
                it1.AddData(it2);
            }
            else
            {
                it1.PrintData();
                it1.InitData(it2);

            }

        }

        it1.PrintData();

    }
    else
    {
        cerr << "Invalid data" << endl;
        return -1;
    }

    
    
    return 0;

}