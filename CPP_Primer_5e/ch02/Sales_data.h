


#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <iostream>
#include <string>



class Sales_data
{

    public:

        void InitData(const Sales_data &rhs); // 初始化成员变量
    
        void CalRevenue(const double &price);  // 计算总利润
        double AvgRevenue();  // 计算平均利润

        
        void AddData(const Sales_data &rhs);  // 相同的isbn号的数据相加
        void PrintData();   // 输出数据
            
    private:
    
        std::string bookNo;  // isbn
        unsigned int units_sold; //销售数量 error initial:unsigned int units_sold(0)
        double revenue; // 总销售收入


};

inline
void Sales_data::InitData(const Sales_data &rhs)
{
    
    if( this == &rhs ) return;

    this->bookNo = rhs.bookNo;
    this->units_sold = rhs.units_sold;
    this->revenue = rhs.revenue;

}


inline
void Sales_data::CalRevenue(const double &price)
{

    revenue = units_sold * price;

}


inline
double Sales_data::AvgRevenue()
{

    if( units_sold )
        return revenue / units_sold;

    return 0;

}


inline
void Sales_data::AddData(const Sales_data &rhs)
{

    this->units_sold += rhs.units_sold;
    this->revenue += rhs.revenue;

}


inline 
void Sales_data::PrintData()
{

    std::cout << bookNo << " " << units_sold << " " << AvgRevenue() << std::endl; 

}


#endif