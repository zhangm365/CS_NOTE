


#include <iostream>
#include <string>



using namespace std;

istream &func( istream &is )
{

    int buf;
    while ( is >> buf )
        cout << buf << endl;

    //is.clear();   // 将条件状态位复位, 将流的状态设置为有效 
    return is;

}


int main()
{

    
    istream &is = func(cin);
    
    cout << is.rdstate() << " " << is.good() << endl;
    
    ostream *b_state = cin.tie();   // 指向关联的cout流 
    ostream *old_state = cin.tie(nullptr);

    if( old_state == b_state ) cout << "not null\n";
    

    return 0;

}