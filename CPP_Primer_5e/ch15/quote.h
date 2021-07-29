

#ifndef _QUOTE_H_
#define _QUOTE_H_

#include <string>

class Quote
{

    public:
        Quote() {}
        
        Quote( const std::string &book, double sales_price ) : bookNo(book), price(sales_price) {}
        
        std::string isbn() const { return bookNo; }

        virtual double net_price( std::size_t n ) const
        {
            std::cout << "Quote net_price" << "\n";
            return n * price;
        }

        virtual void debug() const
        {
            std::cout << "bookNo: " << bookNo << " price: " << price << "\n";
        }


        virtual ~Quote() {}

    private:
        std::string bookNo;
    
    protected:
        double price = 0.0;


};


#endif