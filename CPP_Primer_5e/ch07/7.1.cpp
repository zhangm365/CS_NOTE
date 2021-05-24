

#include <iostream>

using namespace std;

struct Sales_data
{

    string bookNo;
    unsigned units_sold;
    double revenue = 0.0;

};


int main()
{

    Sales_data total;
    cout << "usage : <string>bookNO, <unsigned>units_sold, <double>revenue\n";
    if( cin >> total.bookNo >> total.units_sold >> total.revenue )
    {
        
        Sales_data trans;

        while( cin >> trans.bookNo >> trans.units_sold >> trans.revenue )
        {
            if( trans.bookNo == total.bookNo )
            {
                total.units_sold += trans.units_sold;
                total.revenue += trans.revenue;
            }
            else
            {
                cout << total.bookNo << " " << total.units_sold << " " << total.revenue << endl;
                total = trans;

            }

        }

        cout << total.bookNo << " " << total.units_sold << " " << total.revenue << endl;

    }
    else
    {
        cerr << "No data?" << endl;
        return -1;
    }


    return 0;

}