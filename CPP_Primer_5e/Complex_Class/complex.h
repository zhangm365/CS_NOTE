
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

//complex& __doadiv( complex *, const complex &);

class complex 
{
    public:
        complex(double r = 0, double i = 0) : re(r), im(i) {}

        double real() const { return re; }
        double image() const { return im; }
        complex& operator += (const complex &);
        complex& operator -= (const complex &);
        complex& operator *= (const complex &);

    private:
        double re, im;

        // friend function
        friend complex& __doapl( complex *, const complex &r );
        friend complex& __doami( complex *, const complex &r );
        friend complex& __doaml( complex *, const complex &r );
}; 

inline double
real( const complex &r )
{
    return r.real();
}

inline double
image( const complex &r )
{
    return r.image();
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
    
    ths->re = (ths->re) * (r.re) - (ths->im) * (r.im);
    ths->im = (ths->re) * (r.im) + (ths->im) * (r.re);
    return *ths;

}

inline complex&
complex::operator *= (const complex &r)
{
    return __doaml(this, r);
}

inline complex
operator + (const complex &x, const complex &y)
{
    return complex( real(x) + real(y), image(x) + image(y) );
}

inline complex
operator + ( const complex &x, double y )
{
    return complex( real(x) + y, image(x) );
}

inline complex
operator + ( double x, const complex &y )
{
    return complex( x + real(y), image(y) );
}



std::ostream &
operator << (std::ostream &os, const complex &r)
{
    return os << "(" << real(r) << "," << image(r) << ")";
}
#endif
