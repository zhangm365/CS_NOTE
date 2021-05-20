

#include <iostream>

using namespace std;


// 返回数组中包含10个string对象的引用的声明
string (&func( string(&arrStr)[10] ))[10];


typedef string arrT[10];
using arrT = string[10];

arrT& func1( arrT& arrStr );


auto func2( arrT& arrStr ) -> string (&)[10];

string str[10] = { "zhang", "hello", "world" };


decltype(str) &func2( arrT& arr );

int calc( int, int );
int calc( const int, const int );