

#include <iostream>

using namespace std;


class Fraction
{
	public:
    	Fraction() = default;
    	
        Fraction( int num, int den = 1 ) : m_num(num), m_den(den) {}	//
    	
        operator double() const		// 将类类型转为double型
        {
            cout <<  __func__ << "\n" ;
            return (double)(m_num*1.0 / m_den);
        }
    
    	Fraction operator+( const Fraction & );
    
    private:
    	int m_num;	// 分子
    	int m_den;	// 分母

};

Fraction Fraction::operator+( const Fraction &rhs )
{
    cout <<  __func__ << "\n" ;
    return Fraction(((this->m_num) * (rhs.m_den) + (this->m_den) * (rhs.m_num)) / ((this->m_den) * (rhs.m_den)));
}




int main()
{


    Fraction ite = 2;	// 隐式的类类型转换。转换构造函数, 拷贝初始化
    // Fraction tmp(2, 1);
    // ite = tmp;  


    Fraction f1(3,5);
    // double d = 4 + f1;	// 将 f1 转为 double 型，即调用 operator double() 将 f1 转为0.6
    // cout << d << endl;

    Fraction f = 4 + f1 ;
    
    // Fraction f = f1 + 4;
    
    
    return 0;

}