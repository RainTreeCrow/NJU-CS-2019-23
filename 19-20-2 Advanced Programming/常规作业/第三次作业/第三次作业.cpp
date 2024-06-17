#include <iostream>
using namespace std;

class Array {
	int* array;
	friend class Matrix;
public:
	Array(int n);
	~Array();
};

Array::Array(int n) {
	array = new int[n];
}

Array::~Array() {
	delete[]array;
}

class Matrix {
	int row;
	int col;
	Array* arr;
public:
	Matrix(int r, int c);
	void input(int* a, int length);
	Matrix* inverse();
	void print();
};

Matrix::Matrix(int r, int c) {
	row = r;
	col = c;
	arr = new Array(row * col);
}

void Matrix::input(int* a, int length) {
	int i;
	if (row * col > length) {
		for (i = 0; i < length; i++)
			arr->array[i] = a[i];
		for (i = length; i < row * col; i++)
			arr->array[i] = 0;
	}
	else {
		for (i = 0; i < row * col; i++)
			arr->array[i] = a[i];
	}
}

Matrix* Matrix::inverse() {
	Matrix* inversed_m = new Matrix(row, col);
	for (int i = 0; i < row * col; i++)
		inversed_m->arr->array[i] = - arr->array[i];
	return inversed_m;
}

void Matrix::print() {
	int i, j;
	for (i = 0; i < row; i++) {
		cout << '[';
		for (j = 0; j < col - 1; j++)
			cout << arr->array[i * col + j] << ", ";
		cout << arr->array[(i + 1) * col - 1] << ']' << endl;
	}
}

class String {
	char* s;
	friend void string_join(String a, String b, String& c);
public:
	String();
	String(char* c);
	int string_length();
	void print_string();
};

String::String() {
	s = new char[100];
	for (int i = 0; i < 100; i++)
		s[i] = '\0';
}

String::String(char* c) {
	int i;
	s = new char[100];
	for (i = 0; c[i] != '\0'; i++)
		s[i] = c[i];
	s[i] = '\0';
}

int String::string_length() {
	int length = 0;
	for (; s[length] != '\0'; length++);
	return length;
}

void string_join(String a, String b, String& c) {
	int i, j;
	for (i = 0; a.s[i] != '\0'; i++)
		c.s[i] = a.s[i];
	for (j = 0; b.s[j] != '\0'; j++) {
		c.s[i] = b.s[j];
		i += 1;
	}
	c.s[i] = '\0';
}

void String::print_string() {
	cout << s << endl;
}

class Single{
	Single() {}
	static bool exist;
	static Single* the_one;
public:
	static Single* create_the_one(){
		if (exist == false) {
			the_one = new Single;
			exist = true;
		}
		return the_one;
	}
};

bool Single::exist = false;
Single* Single::the_one = NULL;

int main()
{
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
	Matrix* reversed = m.inverse();
	reversed->print();

	char* temp1 = new char[50];
	char* temp2 = new char[50];
	cin >> temp1 >> temp2;
	String SA(temp1), SB(temp2);
	String SC;
	string_join(SA, SB, SC);
	SA.print_string();
	SB.print_string();
	SC.print_string();
	cout << SC.string_length() << endl;

	Single* one = Single::create_the_one();
	Single* two = Single::create_the_one();
	cout << one << " " << two << endl;

	return 0;
}