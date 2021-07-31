

#ifndef _DISC_QUOTE_H_

#define _DISC_QUOTE_H_

#include "quote.h"

// 抽象类
class Disc_quote : public Quote
{

    public:
        Disc_quote() {}
        Disc_quote( const std::string &book, double sales_price, std::size_t _min_qty, double _discount ) : Quote(book, sales_price), min_qty(_min_qty), discount(_discount) {}
        virtual double net_price( std::size_t n ) const override = 0;

    protected:
    
        std::size_t min_qty = 0;    // 适用折扣政策的最低购买量
        double discount = 0.0;        // 折扣额


};






#endif