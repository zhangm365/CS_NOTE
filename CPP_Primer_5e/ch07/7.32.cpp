

#include <iostream>
#include <string>
#include <vector>


class Screen;

class Window_mgr
{


    public:
        using ScreenIndex = std::vector<Screen>::size_type;

        void clear( ScreenIndex );
    private:
        std::vector<Screen> screens;
};



class Screen
{

    friend void Window_mgr::clear( ScreenIndex );   // 类Window_mgr中的成员函数clear声明为Screen的友元
    public:
        typedef std::string::size_type pos;

    private:
        pos cursor = 0 ;    // 当前光标位置
        pos height = 0 ;    // 屏幕的高 
        pos width = 0 ;     // 屏幕的宽

        std::string contents;   // 屏幕的内容
};

inline
void Window_mgr::clear( ScreenIndex i )
{

    if( i >= screens.size() ) return;
    
    Screen &s = screens[i];

    s.contents = string( s.height*s.width, ' ' );

}