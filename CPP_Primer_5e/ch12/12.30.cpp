

#include "textquery.h"


void runQueries( std::ifstream &infile )
{

    TextQuery tq(infile);
    while( true )
    {

        std::cout << "enter the word to look for, or q to quit: " ;
        string s; 

        if( !(std::cin >> s ) || s == "q" ) break;

        print(std::cout, tq.query(s) ) << std::endl;

    }


}


int main( int argc, char *argv[] )
{

    std::ifstream file("textquery.txt");
    runQueries( file ); 

    return 0;

}