


#include "Sales_data.h"

using namespace std;


int main()
{


    Sales_data total;
    
    if( read( cin, total) )
    {
        Sales_data trans;

        while( read( cin, trans) )
        {
            if( total.isbn() == trans.isbn() )
            {
                add(total, trans);
            }
            else
            {
                print( cout, total );
                cout << endl;
                total = trans;
            }
        }
        print( cout, total );
        cout << endl;
        
    }
    else
    {
        cout << "No data?" << endl;
        return EXIT_FAILURE;
    }

    return 0;

}