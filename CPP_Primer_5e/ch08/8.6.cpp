

#include "../ch07/Sales_data.h"
#include <fstream>
using namespace std;


int main( int argc, char* argv[] )
{

    if ( argc != 3 )
    {
        cout << "usage:<a.out | book_in.txt | book_out.ext>\n";
        return -1;
    }

    string str_in = argv[1];
    string str_out = argv[2];

    ifstream ifs(str_in);
    ofstream ofs(str_out, ofstream::app);

    Sales_data total;

    if( read(ifs, total) )
    {
        Sales_data trans;
        while ( read(ifs, trans) )
        {
            /* code */
            if( trans.isbn() == total.isbn() )
            {
                total.combine(trans);

            }
            else
            {
                print(ofs, total) << endl;
                total = trans;
            }
        }
        
        print(ofs, total);
    }
    else
    {
        cerr << "No data?" << endl;
        return EXIT_FAILURE;
    }

    return 0;

}