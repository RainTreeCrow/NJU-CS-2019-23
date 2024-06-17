#include <iostream>
#include "polynomial.h"
#include "polynomial.cpp"
using namespace std;

int main()
{	
	double w[1] = { 1 };
	int n = 1;
	double w1[2] = { 1, 1 };
	double w2[3] = { -3, 2, 1 };
	Polynomial p(w, n);
	p.display();
	Polynomial p1(w1, 2);
	p1.display();
	Polynomial p2(w2, 3);
	p2.display();
	Polynomial p3=p1+p2;
	p3.display();
	Polynomial p4=p3*p2;
	p4.display();
	Polynomial p5=p4(p1);
	p5.display();
	double result = p5(1.5);
	double d = p5.derivative(1.5);
	cout << result << " " << d << endl;
	return 0;
}