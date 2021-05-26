


#include <iostream>

#include <string>

using namespace std;

class Sales_data;

istream &read( istream &is, Sales_data & );

class Sales_data
{

    friend istream &read( istream &is, Sales_data &rhs );
    public:

        Sales_data( string str, unsigned cnt, double price ) : bookNo(str), units_sold(cnt), revenue(cnt*price) { cout << "three parameters ctor\n"; }

        // 委托构造函数
        Sales_data() : Sales_data( "", 0, 0 ) { cout << "default ctor \n" ; }
        explicit Sales_data( string s ) : Sales_data( s, 0, 0 ) { cout << "string parameter ctor\n"; }

        Sales_data( istream &is ) : Sales_data() { cout << "istream ctor\n"; read(is, *this); }

        string isbn() const { return bookNo; }


    private:

        string bookNo;
        unsigned units_sold;

        double revenue;


};


istream &read( istream &is, Sales_data &rhs )
{

    is >> rhs.bookNo >> rhs.units_sold >> rhs.revenue;
    return is;

}

int main()
{

    Sales_data item;
    Sales_data item1( "zhang", 3, 25.99 );
    // Sales_data item2( "zhang" );
    string str_no("zhang");
    Sales_data item2(str_no);    
    // Sales_data item2 = str_no;  // error: conversion from ‘std::string’ {aka ‘std::__cxx11::basic_string<char>’} to non-scalar type ‘Sales_data’ requested
    cout << item2.isbn() << endl;
    Sales_data item3( cin );
    int a(5);
    cout << a << endl;
    a = 3;
    cout << a << endl;
    return 0;


}