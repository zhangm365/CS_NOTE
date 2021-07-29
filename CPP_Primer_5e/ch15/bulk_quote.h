




#ifndef _BULK_QUOTE_H_
#define _BULK_QUOTE_H_

#include "quote.h"


class Bulk_quote : public Quote
{

    public:
        Bulk_quote() {};
        Bulk_quote( const std::string &book, double sales_price, std::size_t _min_qty, double _discount ) : Quote(book, sales_price), min_qty(_min_qty), discount(_discount) {} 
        double net_price( std::size_t cnt ) const override
        {
            std::cout << "Bulk_quote net_price" << "\n";
            if( cnt >= min_qty )
            {
                return cnt * (1-discount) * price;
            }
            else
            {
                return cnt * price;
            }
            
        }

        void debug() const override
        {
            Quote::debug();
            std::cout << "min_qty: " << min_qty << " discount: "  << discount << "\n";
        }

        
    private:
        std::size_t min_qty = 0;    // 适用折扣政策的最低购买量
        double discount = 0.0;        // 折扣额

};

#endif