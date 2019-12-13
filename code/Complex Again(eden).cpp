#include <iostream>

class Complex {

    //A friend function to print Complex numbers like a+bi where a is the real part and b is the imaginary part

   friend std::ostream &operator<<(std::ostream& out, const Complex& a);
    
public:
   Complex(double re, double im);
   Complex();
   ~Complex();
   Complex(Complex& a);

   //Some function about operator overloading.
   friend Complex operator+(const Complex& a, const Complex& b);
   friend Complex operator-(const Complex& a, const Complex& b);
   friend Complex operator*(const Complex& a, const Complex& b);
   friend Complex operator/(const Complex& a, const Complex& b);

   Complex& operator+=(const Complex& a);
   Complex& operator-=(const Complex& a);
   Complex& operator*=(const Complex& a);
   Complex& operator/=(const Complex& a);

   friend Complex operator==(const Complex& a, const Complex& b);
   friend Complex operator!=(const Complex& a, const Complex& b);


   void SetReal(double re){real = re;}
   void SetImag(double im){imag = im;}
private:
   double real; 
   double imag; 
};



#include "Complex.hpp"
#include <iostream>

using namespace std;

Complex::Complex(double re, double im){
    real = re;
    imag = im;
}

Complex::Complex(){
    real = 0;
    imag = 0;
}

Complex::~Complex(){

}

Complex::Complex(Complex& a){
	real = a.real;
	imag = a.imag;
}

ostream &operator<<(ostream& out, const Complex& a){
	if(a.imag == 0 && a.real != 0)
	{
		out << a.real;
	}
	else if(a.imag == 0 && a.real == 0)
	{
		out << 0;
	}
	else if(a.real == 0 && a.imag != 0)
	{
		out << a.imag << "i" << endl;
	}
	else
	{
		if(a.imag > 0)
		{
			out << a.real << "+" << a.imag << "i" << endl;
		}
		else
		{
			out << a.real << a.imag << "i" << endl;
		}
	}
    
}

   //Some function about operator overloading.
Complex operator+(const Complex& a, const Complex& b){
	Complex temp;
	temp.real = a.real + b.real;
	temp.imag = a.imag + b.imag;
return temp;
}

Complex operator-(const Complex& a, const Complex& b){
	Complex temp;
	temp.real = a.real - b.real;
	temp.imag = a.imag - b.imag;
return temp;	
}

Complex operator*(const Complex& a, const Complex& b){
	Complex temp;
	temp.real = a.real * b.real - a.imag * b.imag;
	temp.imag = a.real * b.imag + a.imag * b.real;
return temp;	
}

Complex operator/(const Complex& a, const Complex& b){
	Complex temp;
	temp.real = (a.real * b.real + a.imag * b.imag) / (b.real * b.real + b.imag * b.imag);
	temp.imag = (a.imag * b.real - a.real * b.imag) / (b.real * b.real + b.imag * b.imag);
return temp;	
}

Complex& Complex::operator+=(const Complex& a){
    real = real + a.real;
    imag = imag + a.imag;
return *this;
}

Complex& Complex::operator-=(const Complex& a){
    real = real - a.real;
    imag = imag - a.imag;
return *this;
}

Complex& Complex::operator*=(const Complex& a){
	double te = real;
	real = real * a.real - imag * a.imag;
	imag = te * a.imag + imag * a.real;
return *this;
}

Complex& Complex::operator/=(const Complex& a){
	double te = real;
	real = (real * a.real + imag * a.imag) / (a.real * a.real + a.imag * a.imag);
	imag = (imag * a.real - te* a.imag) / (a.real * a.real + a.imag * a.imag);
return *this;
}


Complex operator==(const Complex& a, const Complex& b){
    Complex temp;
    temp.imag = 0;
    if(a.real == b.real && a.imag == b.imag)
    {
    	temp.real = 1;
    }
    else
    {
    	temp.real = 0;
    }
return temp;
}

Complex operator!=(const Complex& a, const Complex& b){
    Complex temp;
    temp.imag = 0;
    if(a.real == b.real && a.imag == b.imag)
    {
    	temp.real = 0;
    }
    else
    {
    	temp.real = 1;
    }
return temp;
}

