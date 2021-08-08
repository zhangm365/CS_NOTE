

#ifndef __MYSTRING_H
#define __MYSTRING_H

#include <memory>

class String
{
    public:
        String() : elements(nullptr), end(nullptr) {};
        String( const char * );
        String( const String & );
        String& operator=( const String & );
        ~String();

        char *c_str() const { return elements; }
        std::size_t size() const { return end - elements; }
    

    private:
        // 分配空间并拷贝元素
        std::pair<char*, char*> alloc_n_copy( const char*, const char* );

        void range_initializer( const char*, const char* );

        void free();



    private:
        char *elements; // 指向数组首地址
        char *end;      // 指向尾地址
        std::allocator<char> alloc;

};



#endif