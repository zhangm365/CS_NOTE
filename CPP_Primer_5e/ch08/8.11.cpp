


#include<iostream>

#include<string>
#include <vector>

#include <sstream>


using namespace std;

class PersonInfo
{

    public:
        string name;
        vector<string> phones;

};


int main()
{

    string line, word;
    vector<PersonInfo> peoples;

    istringstream record;

    while( getline(cin, line) )
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