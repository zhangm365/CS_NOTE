

#include "strblobptr.h"

#include <fstream>

using namespace std;



int main()
{

    ifstream ifs("test.txt");

    StrBlob blob;

    for( string str; getline(ifs, str); )
        blob.push_back(str);
    

    for ( StrBlobPtr pbeg(blob.begin()), pend(blob.end()); pbeg != pend; pbeg.incr() )
        cout << pbeg.deref() << endl;
    
    
    return 0;

}