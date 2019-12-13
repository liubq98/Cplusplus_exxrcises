 #include "Complex.hpp"
#include <iostream>
using std::cout;

Complex::Complex(double real, double imaginary) {
 setComplexNumber(real, imaginary );
 } // end Complex constructor

Complex Complex::add(const Complex &right ){
 /* Write a statement to return a Complex object. Add
  the realPart of right to the realPart of this Complex
  object and add the imaginaryPart of right to the
  imaginaryPart of this Complex object */
    Complex temp;
    temp.realPart = right.realPart + realPart;
    temp.imaginaryPart = right.imaginaryPart + imaginaryPart;
return temp;
} // end function add

Complex Complex::subtract( const Complex &right ) {
 /* Write a statement to return a Complex object. Subtract
  the realPart of right from the realPart of this Complex
  object and subtract the imaginaryPart of right from
  the imaginaryPart of this Complex object */
    Complex temp;
    temp.realPart = realPart - right.realPart;
    temp.imaginaryPart = imaginaryPart - right.imaginaryPart;
return temp;
} // end function subtract

void Complex::printComplex() {
 cout << '(' << realPart << ", " << imaginaryPart << ')';
} // end function printComplex

void Complex::setComplexNumber( double rp, double ip ) {
 realPart = rp;
 imaginaryPart = ip;
} // end function setComplexNumber

 class Complex{
	public:
		Complex(double real = 0, double imaginary = 0);
		Complex add(const Complex &right );
		Complex subtract( const Complex &right );
		void printComplex();
		void setComplexNumber( double rp, double ip );
	private:
		double realPart;
		double imaginaryPart;
};
