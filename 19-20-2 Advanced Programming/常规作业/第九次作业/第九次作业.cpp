#include<iostream>
using namespace std;

/*
template <typename T>
void f(T){ cout<<"f(T)"<<endl; }
template <typename T>
void f(const T*){ cout<<"f(const T*)"<< endl; }
template <typename T>
void g(T){ cout<<"g(T)"<<endl; }
template <typename T>
void g(T*){ cout<<"g(T*)"<<endl; }

int main()
{
	int a=1;
	int* b=&a;
	const int c=0;
	const int*d=&c;
	f(a);
	f(b);
	f(c);
	f(d);
	g(a);
	g(b);
	g(c);
	g(d);
}
*/

/*
template <class T>
struct Node {
	T value;
	Node* next;
};

template <class T>
class List {
	Node <T>* head;
	Node <T>* tail;
public:
	List() { head = NULL; tail = NULL; }
	void add(T dat);
	void display();
	~List();
};

template <class T>
void List <T>::add (T dat){
	Node <T>* temp = new Node <T>;
	temp->value = dat;
	temp->next = NULL;
	if (head == NULL) {
		head = temp;
		tail = temp;
	}
	else {
		tail->next = temp;
		tail = temp;
	}
}

template <class T>
void List <T>::display() {
	Node <T>* p;
	if (head != NULL) {
		for (p = head; p->next != NULL; p = p->next) {
			cout << p->value << ' ';
		}
		cout << p->value << endl;
	}
}

template <class T>
List <T>::~List() {
	Node <T>* p, * q;
	for (p = head; p != NULL; ) {
		q = p;
		p = p->next;
		q->next = NULL;
		delete q;
	}
}

int main()
{
	List<int> lst1;
	lst1.add(1);
	lst1.add(2);
	lst1.add(3);
	lst1.display();
	List<double> lst2;
	lst2.add(0.1);
	lst2.add(0.2);
	lst2.add(0.3);
	lst2.display();
	List<string> lst3;
	lst3.add("Hello");
	lst3.add("Hi");
	lst3.add("Goodbye");
	lst3.display();
	return 0;
}
*/

template <class T>
class Matrix {
	int row;
	int col;
	T** matrix;
public:
	Matrix(int r, int c) {
		row = r;
		col = c;
		matrix = new T * [row];
		for (int i = 0; i < row; i++) {
			matrix[i] = new T[col];
			memset(matrix[i], 0, col);
		}
	}
	Matrix(const Matrix& mat) {
		row = mat.row;
		col = mat.col;
		matrix = new T * [row];
		int i, j;
		for (i = 0; i < row; i++) {
			matrix[i] = new T[col];
			for (j = 0; j < col; j++)
				matrix[i][j] = mat.matrix[i][j];
		}
	}
	void setMatrix() {
		int i, j;
		T temp;
		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				cin >> temp;
				matrix[i][j] = temp;
			}
		}
	}
	void display() {
		int i, j;
		for (i = 0; i < row; i++) {
			for (j = 0; j < col - 1; j++) {
				cout << matrix[i][j] << ' ';
			}
			cout << matrix[i][col - 1] << endl;
		}
	}
	void transport() {
		Matrix<T> temp(*this);
		for (int i = 0; i < row; i++)
			delete[] matrix[i];
		delete[] matrix;
		matrix = NULL;
		int t = row;
		row = col;
		col = t;
		matrix = new T * [row];
		for (int i = 0; i < row; i++) {
			matrix[i] = new T[col];
			memset(matrix[i], 0, col);
		}
		int i, j;
		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				matrix[i][j] = temp.matrix[j][i];
			}
		}
	}
	void square() {
		T temp = matrix[0][0];
		int i, j;
		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				temp += matrix[i][j] * matrix[i][j];
			}
		}
		temp -= matrix[0][0];
		cout << temp << endl;
	}
	Matrix operator+(const Matrix& mat) {
		Matrix<T> temp(*this);
		int i, j;
		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				temp.matrix[i][j] += mat.matrix[i][j];
			}
		}
		return temp;
	}
	~Matrix() {
		for (int i = 0; i < row; i++)
			delete[] matrix[i];
		delete[] matrix;
	}
};

int main()
{
	Matrix<int> m1(3, 4);
	m1.setMatrix();
	m1.display();
	Matrix<int> m2(m1);
	m2.display();
	m2.transport();
	m2.display();

	Matrix<double> m3(2, 3);
	m3.setMatrix();
	m3.display();
	m3.square();
	Matrix<double> m4(2, 3);
	m4.setMatrix();
	m4.display();
	Matrix<double> m5 = m3 + m4;
	m5.display();
	return 0;
}