#include <iostream>
#include <algorithm>
using namespace std;
#include "polynomial.h"

Polynomial::Polynomial() {
	w = { 0 };
	n = 1;
}

Polynomial::Polynomial(const Polynomial& p) {
	w = new double[p.n];
	for (int i = 0; i < p.n; i++)
		w[i] = p.w[i];
	n = p.n;
}

Polynomial::Polynomial(const double w[], const int n) {
	this->w = new double[n];
	for (int i = 0; i < n; i++)
		this->w[i] = w[i];
	this->n = n;
}

Polynomial Polynomial::operator+(const Polynomial& p)const {
	Polynomial result;
	if (n >= p.n) {
		result.n = n;
		result.w = new double[result.n];
		for (int i = 0; i < p.n; i++)
			result.w[i] = w[i] + p.w[i];
		for (int j = p.n; j < n; j++)
			result.w[j] = w[j];
	}
	else {
		result.n = p.n;
		result.w = new double[result.n];
		for (int i = 0; i < n; i++)
			result.w[i] = w[i] + p.w[i];
		for (int j = n; j < p.n; j++)
			result.w[j] = p.w[j];
	}
	return result;
}

Polynomial Polynomial::operator*(const Polynomial& p)const {
	Polynomial result;
	result.n = n + p.n - 1;
	result.w = new double[result.n];
	for (int k = 0; k < result.n; k++)
		result.w[k] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p.n; j++)
			result.w[i + j] += w[i] * p.w[j];
	}
	return result;
}

Polynomial Polynomial::operator()(const Polynomial& p)const {
	Polynomial result;
	result.n = (n - 1) * (p.n - 1) + 1;
	result.w = new double[result.n];
	for (int l = 0; l < result.n; l++)
		result.w[l] = 0.0;
	for (int i = 0; i < n; i++) {
		double t1[1] = { 1.0 };
		Polynomial temp(t1, 1);
		for (int j = 0; j < i; j++)
			temp = temp * p;
		double t2[1] = { w[i] };
		Polynomial helper(t2, 1);
		result = result + helper * temp;
		result.display();
	}
	return result;
}

double Polynomial::operator()(double x) const {
	double result = 0.0;
	for (int i = 0; i < n; i++)
		result += w[i] * pow(x, i);
	return result;
}

double Polynomial::derivative(double x) const {
	double result = 0.0;
	for (int i = 0; i < n; i++)
		result += w[i] * i * pow(x, i - 1);
	return result;
}

void Polynomial::display() {
	for (int i = 0; i < n - 1; i++)
		cout << w[i] << "x" << "^" << i << " + ";
	cout << w[n-1] << "x" << "^" << n-1 << endl;
}