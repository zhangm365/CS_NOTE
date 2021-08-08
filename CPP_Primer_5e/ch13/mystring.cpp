

#include "mystring.h"

#include <iostream>

#include <algorithm>


std::pair<char*, char*>
String::alloc_n_copy( const char *b, const char *e )
{

    auto str = alloc.allocate( e - b ); // 分配空间保存给定范围内的元素
    return { str, std::uninitialized_copy(b,e,str) };
 
}


void String::range_initializer( const char *first, const char *last )
{

    auto newStr = alloc_n_copy( first, last );
    elements = newStr.first;
    end = newStr.second;

}


String::String( const char *s ) 
{

    char *sl = const_cast<char*>(s);
    while( *sl )
    {
        ++sl;
    }

    range_initializer(s, sl);


}


String::String( const String &rhs )
{
    
    range_initializer(rhs.elements, rhs.end);
    std::cout << "copy constructor\n";

    
}


String& String::operator=( const String &rhs )
{

    if( this != &rhs )
    {
        
        this->free();
        auto newStr = alloc_n_copy( rhs.elements, rhs.end );

        elements = newStr.first;
        end = newStr.second;
        std::cout << "copy-assignment\n" ;

    }

    return *this;

}


void String::free()
{
    if(elements)
    {
        std::for_each( elements, end, [this](char &c){alloc.destroy(&c);} );
        alloc.deallocate( elements, end - elements );
    }

}


String::~String()
{
    free();
}

