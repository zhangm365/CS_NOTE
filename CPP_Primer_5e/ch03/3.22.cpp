

#include <iostream>

#include <string>

#include <vector>


using namespace std;


int main()
{


    vector<string> text;

    for( string str; getline(cin, str); text.push_back(str));

    cout << endl;
    
    for( auto& word : text )
    {
        for( auto& ch : word )
            if( isalpha(ch) ) ch = toupper(ch);

        cout << word << ",";
    
    }
    
    return 0;

}