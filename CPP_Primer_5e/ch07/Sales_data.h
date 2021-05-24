
#ifndef _SALES_DATA_H_
#define _SALES_DATA_H_

#include <iostream>
#include <string>

// forward declaration
class Sales_data;

std::istream &read( std::istream &is, Sales_data &rhs );
std::ostream &print( std::ostream &out, const Sales_data &rhs );


class Sales_data
{

    // 非成员函数做友元声明
    friend std::istream &read( std::istream &is, Sales_data &rhs );
    friend std::ostream &print( std::ostream &out, const Sales_data &rhs );


    public:
        
        Sales_data() = default;
        Sales_data( const std::string &s ) : bookNo(s) {}
        Sales_data( const std::string &s, unsigned n, double p ) : bookNo(s), units_sold(n), revenue( n*p ) {}
        
        Sales_data( std::istream &is )
        {
            read( is, *this );
        }


        std::string isbn() const { return bookNo; } // const function
        Sales_data& combine( const Sales_data &lhs );
        

    private:
        double avg_price() const ;  // const function
        std::string bookNo;
        unsigned units_sold = 0;    // 类内初始值
        double revenue = 0.0;

};



inline 
Sales_data& Sales_data::combine( const Sales_data &lhs )
{

    units_sold += lhs.units_sold;
    revenue += lhs.revenue;
    return *this;

}

inline
double Sales_data::avg_price() const
{

    if( units_sold )
        return revenue / units_sold;
    
    return 0;

}




// 如果非类成员函数是类接口的组成部分，则这些函数的声明与类放在同一个头文件内
// friend function
std::istream &read( std::istream &is, Sales_data &item )
{

    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = item.units_sold * price;

    return is;

}

std::ostream &print( std::ostream &os, const Sales_data &item )
{
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();

    return os;
}


Sales_data add( const Sales_data &lhs, const Sales_data &rhs )
{

    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;

}

#endif