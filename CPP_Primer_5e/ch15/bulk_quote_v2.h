




#ifndef _BULK_QUOTE_V2_H_
#define _BULK_QUOTE_V2_H_

#include "disc_quote.h"


class Bulk_quote : public Disc_quote
{

    public:
        Bulk_quote() {};
        Bulk_quote( const std::string &book, double sales_price, std::size_t min_qty, double discount ) : Disc_quote( book, sales_price, min_qty, discount ) {} 
        double net_price( std::size_t cnt ) const override
        {
            std::cout << "Bulk_quote net_price" << "\n";
            if( cnt >= min_qty )
            {
                return cnt * ( 1-discount ) * price;
            }
            else
            {
                return cnt * price;
            }
            
        }
    

};

#endif