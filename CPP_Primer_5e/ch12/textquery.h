


#ifndef _TEXTQUERY_H
#define _TEXTQUERY_H

#include <iostream>

#include <vector>
#include <string>

#include <map>
#include <set>

#include <fstream>

#include <memory>


using std::vector;
using std::string;
using std::shared_ptr;


class QueryResult;

class TextQuery
{

    public:
        using LineNo = vector<string>::size_type;

        TextQuery() {}
        TextQuery( std::ifstream &ifs );
        QueryResult query( const string &s ) const;


    private:

        shared_ptr<vector<string>> input;
        std::map<string, shared_ptr<std::set<LineNo>>> result;  // 单词和它所在的行号的集合的映射
        

};


class QueryResult
{

    public:
        QueryResult() {}
        QueryResult( const string &_word, shared_ptr<std::set<TextQuery::LineNo>> _nos, shared_ptr<vector<string>> _input ) : word(_word), nos(_nos), rfile(_input)  {}


    private:
        string word;    // 查询单词
        shared_ptr<std::set<TextQuery::LineNo>> nos;    // 出现的行号
        shared_ptr<vector<string>> rfile;   // 返回的查询文本

        friend std::ostream& print( std::ostream &out, const QueryResult& );

};

std::ostream& print( std::ostream &out, const QueryResult& );


#endif