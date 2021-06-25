

// class with pointer member

#ifndef __STRING__
#define __STRING__

#include <iostream>
#include <string.h>

class String
{
    public:

        String( const char *data = 0 );

        // 拷贝构造
        String( const String & );

        // 拷贝赋值
        String& operator = (const String &);
        ~String();

        char* get_c_str() const { return p_data; }

    private:
        char *p_data;
};

inline 
String::String( const char *data )
{
    if(data)
    {
        p_data = new char[strlen(data) + 1];
        strcpy(p_data, data);
        

    }
    else
    {
        p_data = new char[1];
        p_data[0] = '\0';
    }
}

inline 
String::String( const String &str )
{
    p_data = new char[strlen(str.p_data) + 1];
    strcpy(p_data, str.p_data);

}


inline 
String& String::operator = ( const String &str )
{
    if( this == &str )
        return *this;
    
    // delete old data
    delete [] p_data;
    p_data = new char[strlen(str.p_data) + 1];
    strcpy(p_data, str.p_data);

    return *this;

}

inline
String::~String()
{
    delete [] p_data;

}


std::ostream& operator << (std::ostream& os, const String &str )
{
    os << str.get_c_str();
    return os;

}

#endif