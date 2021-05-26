



#include <iostream>

// 字面值常量类

class Debug
{

    public:
        const Debug() = default;
        constexpr Debug( bool b ) : hw(b), io(b), other(b) {}
        constexpr Debug( bool h, bool i, bool o ) : hw(h), io(i), other(o) {}
        
        constexpr bool any() { return hw || io || other; }

        void set_io( bool b ) { i0 = b; }
        void set_hw( bool h ) { hw = h; }
        void set_other( bool o ) { other = o; }
        
    private:
        bool hw;    // 硬件错误
        bool io;    // io 错误
        bool other; // 其他错误
};