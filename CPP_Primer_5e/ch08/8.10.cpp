
#include<iostream>
#include <vector>
#include <string>

#include <fstream>

#include <sstream>

using namespace std;

void ReadToVec( const string &filename, vector<string> &svc )
{

    ifstream ifs(filename);  // 默认打开文件

    if( ifs )    // 文件打开成功
    {
        
        string buf;
        while( getline(ifs, buf) )  // 将文件中的一行保存到svc
        {
            svc.push_back(buf);
        }

    }
    else
    {
        cerr << "file is null\n";
        return;
    }



}

int main( int argc, char *argv[] )
{

    if( argc != 2 ) 
    {
        cout << "usage< a.out | filename>" << endl;
        return -1;
    }

    vector<string> svc;

    ReadToVec(argv[1], svc);

    for( auto &str : svc )
    {
        istringstream iss(str);
        string word;
        while ( iss >> word )
        {
            cout << word << endl;
        } 
    }
    

    return 0;

}
