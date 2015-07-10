#include <cmath>
#include <string>
#include <iostream>
#include "complex.h"

Complex::Complex(double r = 0, double i = 0)
: real(r), imaginary(i)
{ }

double Complex::Re()
{
	return this->real;
}
double Complex::Im()
{
	return this->imaginary;
}
void Complex::setReal(double re)
{
	this->real = re;
}
void Complex::setImaginary(double im)
{
	this->imaginary = im;
}
void Complex::fromString(const std::string& complexString)
{
	
}
double Complex::thisAbs()
{
	return (sqrt(real*real + imaginary*imaginary));
}
inline double Complex::abs(Complex x)
{
	return x.thisAbs();
}
Complex Complex::operator+(Complex& theComplex)
{
	this->real += theComplex.Re();
	this->imaginary += theComplex.Im();
	return *this;
}
Complex Complex::operator-(Complex& theComplex)
{
	this->real -= theComplex.Re();
	this->imaginary -= theComplex.Im();
	return *this;
}
Complex Complex::operator*(Complex& theComplex)
{
	this->real = (this->real)*(theComplex.Re())-(this->imaginary)*(theComplex.Im());
	this->imaginary = (this->real)*(theComplex.Im()) + (theComplex.Re())*(this->imaginary);
	return *this;
}
std::ostream& operator<<(std::ostream& out, Complex& theComplex)
{
	out << theComplex.Re() << " + " << theComplex.Im() << "i" << std::endl;
	return out;
}

