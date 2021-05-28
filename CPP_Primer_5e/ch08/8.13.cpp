




#include<iostream>

#include<string>
#include <vector>
#include <fstream>
#include <sstream>


using namespace std;

class PersonInfo
{

    public:
        string name;
        vector<string> phones;

};


int main( int argc, char *argv[] )
{

    if ( argc != 2 )
    {
        cout << "usage: <a.out | phone.txt>\n";
        return -1;
    }

    ifstream ifs(argv[1]);
    if( !ifs )
    {
        cerr << "the input phone txt is error\n";
        return -1;
    }
    
    string line, word;
    vector<PersonInfo> peoples;

    istringstream record;

    while( getline(ifs, line) )
    {
        PersonInfo info;

        record.clear();
        record.str(line);

        record >> info.name;

        while ( record >> word )
        {

            info.phones.push_back(word);

        }

        peoples.push_back(info);

    }

    for( const auto &val : peoples )
    {
        cout << val.name << " ";
        for( const auto &phone : val.phones )
        {
            cout << phone << " ";
        }
        cout << endl;
    }
    
    return 0;

}