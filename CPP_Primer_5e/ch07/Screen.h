


#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <iostream>
#include <string>

class Screen
{

    public:
        typedef std::string::size_type pos; // 定义一个类型成员

        Screen() = default;
        Screen( pos ht, pos wd ) : height(ht), width(wd), contents( ht*wd, ' ') {}
        Screen( pos ht, pos wd, char c ) : height(ht), width(wd), contents( ht*wd, c ){}
        
        
        char get() const { return contents[cursor]; }    // 读取光标处的字符

        char get( pos ht, pos wd ) const;   // 获取 行ht, 列wd 坐标下的字符

        Screen &move( pos ht, pos wd );     // 将光标移到 (ht,wd) 位置

        Screen &set( char c );
        Screen &set( pos r, pos c, char );

        Screen &display( std::ostream &os )
        {
            do_display(os);
            return *this;
        }

        const Screen &display( std::ostream &os ) const
        {
            // std::cout << "const function\n";
            do_display( os );
            return *this;
        }


    private:

        pos cursor = 0 ;    // 当前光标位置
        pos height = 0 ;    // 屏幕的高 
        pos width = 0 ;     // 屏幕的宽

        std::string contents;   // 屏幕的内容

        void do_display( std::ostream &os ) const
        {
            os << contents;
        }

};


inline
Screen &Screen::set( char c )
{
    contents[cursor] = c;
    return *this;

}

inline
Screen &Screen::set( pos ht, pos wd, char ch )
{
    pos row = ht * width;
    contents[row + wd] = ch;    // 设置给定位置的新值
    return *this;

}


inline 
char Screen::get( pos ht, pos wd ) const
{

    pos row = ht * width;
    return contents[row + wd];

}

inline 
Screen &Screen::move( pos ht, pos wd )
{

    pos row = ht * width;
    cursor = row + wd;
    return *this;

}


#endif
