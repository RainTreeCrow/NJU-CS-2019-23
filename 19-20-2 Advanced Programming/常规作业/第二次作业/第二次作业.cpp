#include <iostream>
using namespace std;

class BoxWithFixedHeight {
	const int height = 10;
	const int area = 200;
	int length;
	int width;
public:
	BoxWithFixedHeight();
	void change_length(int l);
	int volumn();
};

BoxWithFixedHeight::BoxWithFixedHeight() {
	length = 5;
	width = 5;
}

void BoxWithFixedHeight::change_length(int l) {
	length = l;
	width = 10 - l;
}

int BoxWithFixedHeight::volumn() {
	return length * width * height;
}

class Matrix {
	int rows;
	int colums;
	int* m;
public:
	Matrix(int row, int col);
	~Matrix();
	void input(int* a, int length);
	void print();
	void transpose();
};

Matrix::Matrix(int row, int col) {
	rows = row;
	colums = col;
	m = new int[row * col];
}

Matrix::~Matrix() {
	delete[]m;
}

void Matrix::input(int* a, int length) {
	int i;
	if (rows * colums > length) {
		for (i = 0; i < length; i++)
			m[i] = a[i];
		for (i = length; i < rows* colums; i++)
			m[i] = 0;
	}
	else {
		for (i = 0; i < rows * colums; i++)
			m[i] = a[i];
	}
}

void Matrix::print() {
	int i, j;
	for (i = 0; i < rows; i++) {
		cout << '[';
		for (j = 0; j < colums - 1; j++)
			cout << m[i * colums + j] << ", ";
		cout << m[(i + 1) * colums - 1] << ']' << endl;
	}
}

void Matrix::transpose() {
	int i, j, t, count = 0;
	int* temp = new int[rows * colums];
	for (j = 0; j < colums; j++) {
		for (i = 0; i < rows; i++) {
			temp[count] = m[i * colums + j];
			count++;
		}
	}
	t = rows;
	rows = colums;
	colums = t;
	for (i = 0; i < rows * colums; i++)
		m[i] = temp[i];
	delete[]temp;
}

int main()
{
	BoxWithFixedHeight b;
	b.change_length(2);
	cout << b.volumn() << endl;
	b.change_length(4);
	cout << b.volumn() << endl;
	int r, l;
	cin >> r >> l;
	Matrix m(r, l);
	int* a, length;
	cin >> length;
	a = new int[length];
	for (int i = 0; i < length; i++)
		cin >> a[i];
	m.input(a, length);
	m.print();
	m.transpose();
	m.print();
	return 0;
}