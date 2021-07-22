

#include <iostream>

#include "quote.h"

using namespace std;

double print_price( ostream &out, const Quote &obj, size_t n )
{
    double ret = obj.net_price(n);
    cout << "ISBN:" << obj.isbn() << " # sold: " << n << " total due: " << ret << "\n";

    return ret;

}


int main()
{

    Quote Q1;
    Quote Q2( string("8-90-3421224389"), 24.99 );

    print_price(cout, Q1, 3);

    print_price(cout, Q2, 8);



    return 0;

}