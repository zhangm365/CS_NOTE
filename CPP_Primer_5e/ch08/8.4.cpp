


#include<iostream>
#include <fstream>
#include <vector>

using namespace std;

void ReadToVec( const string &filename, vector<string> &svc )
{

    ifstream ifs(filename);  // 默认打开文件

    if( ifs )    // 文件打开成功
    {
        
        string buf;
        while( ifs >> buf )
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

int main()
{

    vector<string> svc;
    ReadToVec("in.txt", svc);

    for( const auto &str : svc )
    {
        cout << str << endl;
    }    

    return 0;

}
