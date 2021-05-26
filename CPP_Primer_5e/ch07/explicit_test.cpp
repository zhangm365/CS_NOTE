
#include <iostream>



class Test
{
	public:
    	Test() = default;
    	Test( int val ) : i(val) {}
    	Test &combine( const Test & );
        // explicit Test &combine( const Test & );
    private:
    	int i;
};

Test &Test::combine( const Test &rhs )
{
    this->i += rhs.i;
    return *this;
}


int main()
{

    
    Test ite = 2;	// error: 当构造函数使用explicit时，抑制隐式的类类型转换。转换构造函数, 拷贝初始化
    Test ite2;
    ite2.combine(2); // error

    return 0;


}
