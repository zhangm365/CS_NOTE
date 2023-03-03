
#include <vector>
#include <sstream>
#include <string>

using namespace std;


/*
    @brief: 将源字符串按分割符进行分割
    @param s: the origin string
    @param delim: the delim char
    @return: the result string
*/
vector<string> split(const string& s, char delim) {

    stringstream ss(s);
    
    vector<string> res;

    string item;

    while(getline(ss, item, delim)) {

        if(!item.empty()) {
            res.emplace_back(item);
        }
    }
    
    /* version 2:
    while(!ss.eof()) {
        getline(ss, item, delim);
        res.emplace_back(item);
    }
    */
    return res;

}



/*
    the split_native solution
*/

#include <vector>
#include <string>

using namespace std;

vector<string> split_naive(const string &s, char delim) {
    vector<string> elems;
    string item;
    for (char ch: s) {
        if (ch == delim) {
            if (!item.empty())
                elems.emplace_back(item);
            item.clear();
        }
        else {
            item += ch;
        }
    }
    if (!item.empty())
        elems.emplace_back(item);
    return elems;
}
