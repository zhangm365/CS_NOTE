





#ifndef _TEXTQUERY_H_V
#define _TEXTQUERY_H_V

#include <iostream>

#include <vector>
#include <string>

#include <map>
#include <set>

#include <fstream>

#include <memory>

#include "strblobptr_v1.h"

using std::vector;
using std::string;
using std::shared_ptr;


class QueryResult;

class TextQuery
{

    public:

        TextQuery() {}
        TextQuery( std::ifstream &ifs );
        QueryResult query( const string &s ) const;


    private:

        StrBlob file;
        std::map<string, shared_ptr<std::set<StrBlob::size_type>>> result;  // 单词和它所在的行号的集合的映射
        

};


class QueryResult
{

    public:
        QueryResult() {}
        QueryResult( const string &_word, shared_ptr<std::set<StrBlob::size_type>> _nos, StrBlob _input ) : word(_word), nos(_nos), rfile(_input)  {}


    private:
        string word;    // 查询单词
        shared_ptr<std::set<StrBlob::size_type>> nos;    // 出现的行号
        
        StrBlob rfile;
        // shared_ptr<vector<string>> rfile;   // 返回的查询文本

        friend std::ostream& print( std::ostream &out, const QueryResult& );

};

std::ostream& print( std::ostream &out, const QueryResult& );


#endif