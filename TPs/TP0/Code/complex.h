#ifndef _COMPLEX_H_INCLUDED_
#define _COMPLEX_H_INCLUDED_

#include <iostream>

#include "types.h"

class Complex 
{
  public:
    Complex();
    Complex(double);
    Complex(format_option_t);
    Complex(double, double);
    Complex(double r, double i, format_option_t f_o);
    Complex(const Complex &);
    Complex const &operator=(Complex const &);
    Complex const &operator*=(Complex const &);
    Complex const &operator+=(Complex const &);
    Complex const &operator-=(Complex const &);
    ~Complex();

    double real() const;
    double imag() const;
    format_option_t format_option() const;
    double abs() const;
    double abs2() const;
    double phase() const;
    Complex const &conjugate();
    Complex const conjugated() const;
    bool iszero() const;

    friend Complex const operator+(Complex const &, Complex const &);
    friend Complex const operator-(Complex const &, Complex const &);
    friend Complex const operator*(Complex const &, Complex const &);
    friend Complex const operator/(Complex const &, Complex const &);
    friend Complex const operator/(Complex const &, double);

    friend bool operator==(Complex const &, double);
    friend bool operator==(Complex const &, Complex const &);

    friend std::ostream &operator<<(std::ostream &, const Complex &);
    friend std::istream &operator>>(std::istream &, Complex &);
  
  private:
    double real_, imag_;
    format_option_t format_option_;
  
  // Lee en formato texto "(Real, Imaginario)"
  friend std::istream &read_format_text(std::istream &, Complex &);
  // Lee en formato binario Real8bits seguido de Imaginario8bits
  friend std::istream &read_format_U8(std::istream &, Complex &);
  // Escribe en formato texto "(Real, Imaginario)"
  friend std::ostream &write_format_text(std::ostream &, const Complex &);
  // Escribe en fomato binario Real8bits seguido de Imaginario8bits
  friend std::ostream &write_format_U8(std::ostream &, const Complex &);
  
}; // class Complex

#endif // _COMPLEX_H_INCLUDED_
