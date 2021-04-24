


#include <iostream>
#include <string>

using namespace std;


class Sales_data
{

    public:
        Sales_data() : bookNo(""), units_sold(0), revenue(0.0){} ;



        string bookNo;  // isbn
        unsigned int units_sold; //销售数量 error initial:unsigned int units_sold(0)
        double revenue; // 总销售收入


};

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
                it1.units_sold += it2.units_sold;
                it1.revenue += it2.revenue;

            }
            else
            {
                cout << it1.bookNo << " " << it1.units_sold << " " << (it1.units_sold ? it1.revenue/it1.units_sold : 0) << endl;
                it1.bookNo = it2.bookNo;
                it1.units_sold = it2.units_sold;
                it1.revenue = it2.revenue;

            }

        }

        cout << it1.bookNo << " " << it1.units_sold << " " << (it1.units_sold ? it1.revenue/it1.units_sold : 0) << endl;

    }
    else
    {
        cerr << "Invalid data" << endl;
        return -1;
    }

    
    
    return 0;

}