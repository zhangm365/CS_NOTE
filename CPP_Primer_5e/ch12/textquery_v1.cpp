

#include "textquery_v1.h"

#include <sstream>

TextQuery::TextQuery( std::ifstream &is ) 
{

    string text;
    while( getline(is, text) )
    {

        file.push_back(text);
        int n = file.size() - 1;  // 当前行号

        std::istringstream line(text);  // 将行文本分解为单词

        string word;

        while( line >> word ) 
        {

            auto &lines = result[word];     // 查询单词

            if( !lines )    // 第一次遇到这个单词
            {
                lines.reset( new std::set<StrBlob::size_type> );
            }

            lines->insert(n);   // 如果一个单词在一行中出现多次, 则只显示一次
                    
        }

    }


}



QueryResult TextQuery::query( const string &str ) const
{

    static shared_ptr<std::set<StrBlob::size_type>> nodata( new std::set<StrBlob::size_type> );

    auto loc = result.find(str);
    if( loc == result.end() )
    {
        return QueryResult( str, nodata, file );
    }


    return QueryResult(str, loc->second, file );

}

std::ostream& print( std::ostream &out, const QueryResult &rhs )
{

    out << rhs.word << " occurs " << rhs.nos->size()
        << ( rhs.nos->size() > 1 ? " times" : " time" ) << std::endl;
    
    
    for( const auto &num : *rhs.nos )
    {
        ConstStrBlobPtr p(rhs.rfile, num);
        out << "\t(line " << num + 1 << ") " 
            << p.deref() << std::endl;
    }

    return out;

}