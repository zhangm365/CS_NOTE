

#include "textquery.h"
#include <sstream>

TextQuery::TextQuery( std::ifstream &is ) : input( new vector<string> )
{

    string text;
    while( getline(is, text) )
    {

        input->push_back(text);
        int n = input->size() - 1;  // 当前行号

        std::istringstream line(text);  // 将行文本分解为单词

        string word;

        while( line >> word ) 
        {

            auto &lines = result[word];     // 查询单词

            if( !lines )    // 第一次遇到这个单词
            {
                lines.reset( new std::set<LineNo> );
            }

            lines->insert(n);   // 如果一个单词在一行中出现多次, 则只显示一次
                    
        }

    }


}



QueryResult TextQuery::query( const string &str ) const
{

    static shared_ptr<std::set<LineNo>> nodata( new std::set<LineNo> );

    auto loc = result.find(str);
    if( loc == result.end() )
    {
        return QueryResult( str, nodata, input );
    }


    return QueryResult(str, loc->second, input );

}

std::ostream& print( std::ostream &out, const QueryResult &rhs )
{

    out << rhs.word << " occurs " << rhs.nos->size()
        << ( rhs.nos->size() > 1 ? " times" : " time" ) << std::endl;
    
    for( const auto &num : *rhs.nos )
    {
        out << "\t(line " << num + 1 << ") " 
            << *(rhs.rfile->begin() + num) << std::endl;
    }

    return out;

}