#include <iostream>
#include <cmath>

#include "complex.h"
#include "types.h"

using namespace std;



Complex::Complex() : real_(0), imag_(0), format_option_(FORMAT_OPTION_TEXT)
{
}

Complex::Complex(format_option_t f_o) : real_(0), imag_(0), format_option_(f_o)
{
}

Complex::Complex(double r) : real_(r), imag_(0), format_option_(FORMAT_OPTION_TEXT)
{
}

Complex::Complex(double r, double i) : real_(r), imag_(i), format_option_(FORMAT_OPTION_TEXT)
{
}

Complex::Complex(double r, double i, format_option_t f_o) : real_(r), imag_(i), format_option_(f_o)
{
}

Complex::Complex(Complex const &c) : real_(c.real_), imag_(c.imag_), format_option_(c.format_option_)
{
}

Complex const &
Complex::operator=(Complex const &c)
{
  real_ = c.real_;
  imag_ = c.imag_;
  format_option_ = c.format_option_;
  return *this;
}

Complex const &
Complex::operator*=(Complex const &c)
{
  double re = real_ * c.real_
           - imag_ * c.imag_;
  double im = real_ * c.imag_
           + imag_ * c.real_;
  real_ = re, imag_ = im;
  return *this;
}

Complex const &
Complex::operator+=(Complex const &c)
{
  double re = real_ + c.real_;
  double im = imag_ + c.imag_;
  real_ = re, imag_ = im;
  return *this;
}

Complex const &
Complex::operator-=(Complex const &c)
{
  double re = real_ - c.real_;
  double im = imag_ - c.imag_;
  real_ = re, imag_ = im;
  return *this;
}

Complex::~Complex()
{
}

double
Complex::real() const
{
  return real_;
}

double Complex::imag() const
{
  return imag_;
}

format_option_t Complex::format_option() const
{
  
  return format_option_;
  
}

double
Complex::abs() const
{
  return std::sqrt(real_ * real_ + imag_ * imag_);
}

double
Complex::abs2() const
{
  return real_ * real_ + imag_ * imag_;
}

double
Complex::phase() const
{
  return atan2(imag_, real_);
}

Complex const &
Complex::conjugate()
{
  imag_*= -1;
  return *this;
}

Complex const
Complex::conjugated() const
{
  return Complex(real_, -imag_);
}

bool
Complex::iszero() const
{
#define ZERO(x) ((x) == +0.0 && (x) == -0.0)
  return ZERO(real_) && ZERO(imag_) ? true : false;
}

Complex const
operator+(Complex const &x, Complex const &y)
{
  Complex z(x.real_ + y.real_, x.imag_ + y.imag_);
  return z;
}

Complex const
operator-(Complex const &x, Complex const &y)
{
  Complex r(x.real_ - y.real_, x.imag_ - y.imag_);
  return r;
}

Complex const
operator*(Complex const &x, Complex const &y)
{
  Complex r(x.real_ * y.real_ - x.imag_ * y.imag_,
            x.real_ * y.imag_ + x.imag_ * y.real_);
  return r;
}

Complex const
operator/(Complex const &x, Complex const &y)
{
  return x * y.conjugated() / y.abs2();
}

Complex const
operator/(Complex const &c, double f)
{
  return Complex(c.real_ / f, c.imag_ / f);
}

bool
operator==(Complex const &c, double f)
{
  bool b = (c.imag_ != 0 || c.real_ != f) ? false : true;
  return b;
}

bool
operator==(Complex const &x, Complex const &y)
{
  bool b = (x.real_ != y.real_ || x.imag_ != y.imag_) ? false : true;
  return b;
}

istream &
operator>>(istream &is, Complex &c)
{
  switch (c.format_option_) {
    
    case FORMAT_OPTION_TEXT:
      return read_format_text(is, c);
    
    case FORMAT_OPTION_U8:
      return read_format_U8(is, c);
    
  }

  return is;
}

ostream &
operator<<(ostream &os, const Complex &c)
{
  switch (c.format_option_) {
    
    case FORMAT_OPTION_TEXT:
      return write_format_text(os, c);
    
    case FORMAT_OPTION_U8:
      return write_format_U8(os, c);
    
  }
  
  return os;
}

// Lee en formato texto "(Real, Imaginario)"
istream &
read_format_text(istream &is, Complex &c)
{

  int good = false;
  int bad  = false;
  double re = 0;
  double im = 0;
  char ch = 0;

  if (is >> ch
      && ch == '(') {
      if (is >> re
        && is >> ch
        && ch == ','
        && is >> im
        && is >> ch
        && ch == ')')
        good = true;
    else
        bad = true;
  } else if (is.good()) {
       is.putback(ch);
    if (is >> re)
      good = true;
    else
    bad = true;
  }

  if (good)
    c.real_ = re, c.imag_ = im;
  if (bad)
    is.clear(ios::badbit);

  return is;
  
}

// Lee en formato binario Real8bits seguido de Imaginario8bits
istream &
read_format_U8(istream &is, Complex &c)
{

  int good = false;
  int bad  = false;
  unsigned char re = 0;
  unsigned char im = 0;

  if (is >> re && is >> im)
  good = true;
  else
    bad = true;

  if (good)
  c.real_ = re - 128;
  c.imag_ = im - 128;
  if (bad)
  is.clear(ios::badbit);

  return is;
  
}

// Escribe en formato texto "(Real, Imaginario)"
ostream &
write_format_text(ostream &os, const Complex &c)
{
  
  return os << "(" 
          << c.real()
          << ", " 
          << c.imag()
          << ")";
  
}

// Escribe en fomato binario Real8bits seguido de Imaginario8bits
ostream &
write_format_U8(ostream &os, const Complex &c)
{
  
  return os << (char)c.real()
          << (char)c.imag();
  
}
