

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

        // move ctor
        String(String &&) noexcept;

        // 拷贝赋值
        String& operator= (const String &);


        // move assign
        String& operator= (String &&) noexcept;
        
        
        ~String();

        char* get_c_str() const { return p_data; }

        static size_t DCtor;    // default ctor
        static size_t Ctor;     // ctor
        static size_t CCtor;    // copy ctor
        static size_t CAsgn;    // copy assign
        static size_t MCtor;    // move ctor
        static size_t MAsgn;    // move assign
        static size_t Dtor;     // dtor

    private:
        char *p_data;
        size_t len;
        void init_data(const char *);
};


size_t String::DCtor = 0;
size_t String::Ctor = 0;
size_t String::CCtor = 0;    
size_t String::CAsgn = 0;
size_t String::MCtor = 0;
size_t String::MAsgn = 0;
size_t String::Dtor = 0;


inline 
void String::init_data(const char *s)
{
    p_data = new char[len+1];
    memcpy(p_data, s, len);
    p_data[len] = '\0';
}


inline 
String::String( const char *data )
{
    if(data)
    {
        Ctor++;
        len = strlen(data);
        init_data(data);

    }
    else
    {
        DCtor++;
        len = 1;
        p_data = new char[1];
        p_data[0] = '\0';
    }
}


inline 
String::String( const String &str ) : len(strlen(str.p_data))
{
    CCtor++;
    init_data(str.p_data);

}

inline 
String::String(String &&str) noexcept
{

    MCtor++;
    len = str.len;
    p_data = str.p_data;

    str.len = 0;
    str.p_data = nullptr;    // 重要

}

inline 
String& String::operator= ( const String &str )
{
    
    CAsgn++;
    if( this == &str )
        return *this;
    
    // delete old data
    delete [] p_data;
    
    len = str.len;
    init_data(str.p_data);

    return *this;

}


inline 
String& String::operator= ( String &&str ) noexcept
{

    MAsgn++;
    if( this == &str ) return *this;
    
    len = str.len;
    p_data = str.p_data;
    
    str.len = 0;
    str.p_data = nullptr;
    return *this;

}


inline
String::~String()
{
    DCtor++;
    delete [] p_data;

}


std::ostream& operator << (std::ostream& os, const String &str )
{
    os << str.get_c_str();
    return os;

}

#endif