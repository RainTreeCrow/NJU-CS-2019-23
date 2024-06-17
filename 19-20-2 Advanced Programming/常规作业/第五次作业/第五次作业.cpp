#include <iostream>
#include <time.h>
#include <string>
#pragma warning(disable:4996)
using namespace std;


/*
class fib {
	int starter;
public:
	fib(int i) { starter = i; };
	int operator()() {
		starter += 1;
		if (starter == 2 || starter == 3)
			return 1;
		else
			return fib(starter - 2)() + fib(starter - 3)();
	}
};

int main()
{
	fib Fib1(1), Fib2(2), Fib10(10);
	for(int i = 1; i <= 7; i++)
		cout << Fib1() << " ";
	cout << endl;
	for (int i = 1; i <= 7; i++)
		cout << Fib2() << " ";
	cout << endl;
	for (int i = 1; i <= 7; i++)
		cout << Fib10() << " ";
	cout << endl;
	return 0;
}
*/

/*
struct Point{
	int x;
	int y;
};

bool IsTrue(Point& rstCenter, int iRadius, Point& P1, Point& P2) {
	auto PointInCircle = [=](Point& p)->bool {return (p.x - rstCenter.x) * (p.x - rstCenter.x) 
		+ (p.y - rstCenter.y) * (p.y - rstCenter.y) < iRadius * iRadius; };
	return PointInCircle(P1) != PointInCircle(P2);
}

int main() {
	Point Center, P1, P2;
	Center.x = 0, Center.y = 0;
	int radius = 2;
	P1.x = 1, P1.y = 1;
	P2.x = 3, P2.y = 3;
	cout << IsTrue(Center, radius, P1, P2);
	return 0;
}
*/

class A {
public:
	void f1() {}
	void f2() {}
	void f3() {}
	void f4() {}
};

class B {
	A *p_a;
	string last_time;
public:
	B(){
		p_a = new A;
		last_time = "NULL";
	}
	A* operator->() {
		time_t now_time = time(NULL);
		last_time = asctime(localtime(&now_time));
		return p_a;
	}
	string string_access() const{
		return last_time;
	}
};

void visit(B &b) {
	b->f1();
	b->f2();
	b->f3();
	b->f4();
}

int main()
{
	B b;
	visit(b);
	cout << b.string_access() << endl;
	return 0;
}