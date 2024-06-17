#include <iostream>
#include <Windows.h>
#include<time.h>
#pragma warning (disable:4996);
using namespace std;

/*
class A {
public:
	A(const char* s) {
		cout << s << endl;
	}~A() {
		cout << "destructor of A" << endl;
	}
};

class B : virtual public A {
public:
	B(const char* s1, const char* s2) :A(s1) {
		cout << s2 << endl;
	}
	~B() {
		cout << "destructor of B" << endl;
	}
};

class C : virtual public A {
public:
	C(const char* s1, const char* s2) :A(s1) {
		cout << s2 << endl;
	}
	~C() {
		cout << "destructor of C" << endl;
	}
};

class D : public B, public C {
public:
	D(const char* s1, const char* s2, const char* s3, const char* s4) :
		B(s1, s2), C(s1, s3), A(s1) {
		cout << s4 << endl;
	}
	~D() {
	cout << "destructor of D" << endl;
	}
};

int main() {
	D* ptr = new D("string1", "string2", "string3", "string4");
	delete ptr;
}
*/

class Screen {
	int length;
	int width;
public:
	Screen(int l, int w) {
		length = l;
		width = w;
	}
	void display(char* message, int len) {
		int i, j, k;
		for (i = 0; i < length; i++) {
			for (j = 0; j < width; j++) {
				k = i * width + j;
				if (k == len)
					goto L;
				else
					cout << message[k];
			}
			cout << endl;
		}
	L:;
		cout << endl;
	}
};

class Mainboard {
	int delay;
public:
	Mainboard(int d) {
		delay = d;
	}
	void encode(char* message, int*& code, int len) {
		code = new int[len];
		for (int i = 0; i < len; i++) {
			if (message[i] == ' ')
				code[i] = 26;
			else if (message[i] == '\0')
				code[i] = -1;
			else
				code[i] = (int)(message[i] - 97);
			Sleep(delay);
		}
	}
	void decode(char*& message, int* code, int len) {
		message = new char[len];
		for (int i = 0; i < len; i++) {
			if (code[i] == 26)
				message[i] = ' ';
			else if (code[i] == -1)
				message[i] = '\0';
			else
				message[i] = (char)(code[i] + 97);
			Sleep(delay);
		}
	}
};

class TestPhone {
	Screen* screen;
	Mainboard* board;
public:
	TestPhone(int length, int width, int delay) {
		screen = new Screen(length, width);
		board = new Mainboard(delay);
	}
	void sendMessage() {
		cout << "Please imput message: ";
		char message[1000];
		cin.getline(message, 1000);
		int* code = NULL;
		cout << "Encoding message into code..." << endl;
		board->encode(message, code, strlen(message));
		cout << "Code: " << endl;
		char char_code[1000];
		int count = 0;
		for (int i = 0; i < strlen(message); i++) {
			if (code[i] == -1) {
				char_code[count] = '-';
				char_code[count + 1] = '1';
				count += 2;
			}
			else if (code[i] > 9) {
				char_code[count] = code[i] / 10 + 48;
				char_code[count + 1] = code[i] % 10 + 48;
				count += 2;
			}
			else {
				char_code[count] = code[i] + 48;
				count += 1;
			}
			char_code[count] = ' ';
			count += 1;
		}
		char_code[count] = '\0';
		screen->display(char_code, count);
	}
	void receiveMessage() {
		int len;
		cout << "Please imput length of code: ";
		cin >> len;
		int* code = new int[len];
		cout << "Please imput code: ";
		for (int i = 0; i < len; i++)
			cin >> code[i];
		char* message = NULL;
		cout << "Decoding code into message..." << endl;
		board->decode(message, code, len);
		cout << "Message: " << endl;
		screen->display(message, len);
	}
};

class ReleasePhone :public TestPhone {
public:
	ReleasePhone(int length, int width, int delay)
		:TestPhone(length, width, delay) {};
	void dateAndTime() {
		cout << endl;
		char system_time[200];
		time_t now_time = time(NULL);
		strcpy(system_time, asctime(localtime(&now_time)));
		cout << "The time is " << system_time;
	}
};

int main()
{
	ReleasePhone Phone(15, 5, 10);
	Phone.sendMessage();
	Phone.receiveMessage();
	Phone.dateAndTime();
	return 0;
}