#ifndef _COMPLEXH
#define _COMPLEXH
#include <string>

class Complex
{
	public:
	Complex(double r, double i);
	double Re(void);
	double Im(void);
	void setReal(double re);
	void setImaginary(double im);
	void fromString(const std::string& complexString);
	double thisAbs();
	inline double abs(Complex x);
	
	Complex operator+(Complex& theComplex);
	Complex operator-(Complex& theComplex);
	Complex operator*(Complex& theComplex);
	Complex operator/(Complex& theComplex);
	
	private:
	double real;
	double imaginary;
};

#endif
