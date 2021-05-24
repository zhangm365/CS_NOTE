


#include "Sales_data.h"

using namespace std;


int main()
{

    Sales_data total( cin );
    if( !total.isbn().empty() )
    {

        std::istream &is = cin;
        while( is )
        {
            
            Sales_data trans(is);
            if( !is ) break;

            if( total.isbn() == trans.isbn() )
            {
                total.combine(trans);

            }
            else
            {
                print(cout, total) << endl;
                total = trans;
            }

        }

        print(cout, total) << endl;


    }
    else
    {
        cout << "No data?\n";
        return EXIT_FAILURE;
    }

    return 0;

}