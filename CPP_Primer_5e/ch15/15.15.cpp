

#include <iostream>

#include "bulk_quote_v2.h"

using namespace std;

static double print_price( ostream &out, const Quote &obj, size_t n )
{
    double ret = obj.net_price(n);
    cout << "ISBN:" << obj.isbn() << " # sold: " << n << " total due: " << ret << "\n";

    return ret;

}


int main()
{

    
    Quote Q1( string("8-90-3421224389"), 25.99 );
    print_price(cout, Q1, 12);

    Bulk_quote B1( string("8-90-3421224389"), 25.99, 10, 0.2 );
    print_price(cout, B1, 12);
    
    Quote Q3 = B1;
    print_price(cout, Q3, 12);
    

    Quote *Q4 = &B1;
    // Q4->net_price(12);
    print_price(cout, *Q4, 12);
    
    // Disc_quote D1;  // error: cannot declare variable ‘D1’ to be of abstract type ‘Disc_quote’
    
    return 0;

}