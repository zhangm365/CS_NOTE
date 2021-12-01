
// 防卫式声明

#ifndef __COMPLEX_H__
#define __COMPLEX_H__

#include <iostream>
// forward declarations
class complex;

// global function
// do assignment plus
complex& __doapl( complex *, const complex & );
// do assignment minus
complex& __doami( complex *, const complex & );
// do assignment multiply
complex& __doaml( complex *, const complex & );

complex& __doadv( complex *, const complex &);

class complex 
{
    public:
        complex(double r = 0, double i = 0) : re(r), im(i) {}


        // member function
        double real() const { return re; }
        double imag() const { return im; }

        // 
        complex& operator += (const complex &);
        complex& operator -= (const complex &);
        complex& operator *= (const complex &);
        complex& operator /= (const complex &);

    private:
        double re, im;

        // friend function
        friend complex& __doapl( complex *, const complex &r );
        friend complex& __doami( complex *, const complex &r );
        friend complex& __doaml( complex *, const complex &r );
        friend complex& __doadv( complex *, const complex &);
}; 

inline double
real( const complex &r )
{
    return r.real();
}

inline double
imag( const complex &r )
{
    return r.imag();
}


inline complex&
__doapl( complex *ths, const complex &r )
{
    ths->re += r.re;
    ths->im += r.im;
    return *ths;    
}


inline complex&
complex::operator += (const complex &r)
{
    return __doapl(this, r);

}

inline complex&
__doami(complex *ths, const complex &r)
{
    ths->re -= r.re;
    ths->im -= r.im;
    return *ths;
}

inline complex&
complex::operator -= (const complex &r)
{
    return __doami(this, r);
}


inline complex&
__doaml( complex *ths, const complex &r )
{
    double ret = (ths->re) * (r.re) - (ths->im) * (r.im);
    
    ths->im = (ths->re) * (r.im) + (ths->im) * (r.re);
    ths->re = ret;
    return *ths;

}

inline complex&
complex::operator *= (const complex &r)
{
    return __doaml(this, r);
}

inline complex&
__doadv( complex *ths, const complex &r )
{
    if( r.re == 0 && r.im == 0 )
        return *ths;
    
    double ret = (ths->re*r.re + ths->im*r.im) / (r.re*r.re + r.im*r.im);

    ths->im = (ths->im*r.re - ths->re*r.im) / (r.re*r.re + r.im*r.im);

    ths->re = ret;

    return *ths;

}


inline complex&
complex::operator /= ( const complex &r )
{

    return __doadv(this, r);
}



inline complex
operator + (const complex &x, const complex &y)
{
    return complex( real(x) + real(y), imag(x) + imag(y) );
}

inline complex
operator + ( const complex &x, double y )
{
    return complex( real(x) + y, imag(x) );
}

inline complex
operator + ( double x, const complex &y )
{
    return complex( x + real(y), imag(y) );
}


inline complex
operator - (const complex &x, const complex &y)
{
    return complex( real(x) - real(y), imag(x) - imag(y) );
}

inline complex
operator - ( const complex &x, double y )
{
    return complex( real(x) - y, imag(x) );
}

inline complex
operator - ( double x, const complex &y )
{
    return complex( x - real(y), -imag(y) );
}


inline complex
operator * (const complex &x, const complex &y)
{
    return complex( real(x)*real(y) - imag(x)*imag(y), real(x)*imag(y) + imag(x)*real(y) );
}

inline complex
operator * ( const complex &x, double y )
{
    return complex( real(x)*y, imag(x)*y );
}

inline complex
operator * ( double x, const complex &y )
{
    return complex( x*real(y), x*imag(y) );
}


inline complex
operator / ( const complex &x, double y )
{
    return complex( real(x)/y, imag(x)/y );
}

inline complex
operator + ( const complex &r )
{
    return r;
}

inline complex
operator - ( const complex &x )
{
    return complex( -real(x), -imag(x) );
}

inline bool
operator == ( const complex &x, const complex &y )
{
    return ( real(x) == real(y) ) && ( imag(x) == imag(y) );
}

inline bool
operator == ( const complex &x, double y )
{
    return ( real(x) == y ) && ( imag(x) == 0 );
}

inline bool
operator == ( double x, const complex &y )
{
    return ( x == real(y) ) && ( imag(y) == 0 );
}


inline bool
operator != ( const complex &x, const complex &y )
{
    return ( real(x) != real(y) ) || ( imag(x) != imag(y) );
}

inline bool
operator != ( const complex &x, double y )
{
    return ( real(x) != y ) || ( imag(x) != 0 );
}

inline bool
operator != ( double x, const complex &y )
{
    return ( x != real(y) ) && ( imag(y) != 0 );
}


#include <cmath>

inline complex
polar( double r, double t )
{
    return complex( r*cos(t), r*sin(t) );
}

inline complex
conj( const complex &x )
{

    return complex( real(x), -imag(x) );
}

inline complex
norm( const complex &x )
{
    return real(x) * real(x) + imag(x) * imag(x);
}


std::ostream &
operator << (std::ostream &os, const complex &r)
{
    return os << "(" << real(r) << "," << imag(r) << ")";
}
#endif
