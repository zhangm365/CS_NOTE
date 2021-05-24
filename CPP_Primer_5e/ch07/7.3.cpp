

#include "Sales_data.h"


using namespace std;


int main()
{

    Sales_data total;
    if( cin >> total.bookNo >> total.units_sold >> total.revenue )
    {
        Sales_data trans;

        while( cin >> trans.bookNo >> trans.units_sold >> trans.revenue )
        {

            if( total.isbn() == trans.isbn() )
            {
                total.combine(trans);

            }
            else
            {
                cout << total.bookNo  << " " << total.units_sold << " " << total.revenue << endl;
                total = trans;

            }

        }
        
        cout << total.bookNo  << " " << total.units_sold << " " << total.revenue << endl;

    }
    else
    {

        cout << "No data?" << endl;
        return EXIT_FAILURE;

    }

    return 0;

}