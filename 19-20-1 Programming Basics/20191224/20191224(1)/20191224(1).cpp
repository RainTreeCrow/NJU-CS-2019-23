#include<iostream>
using namespace std;

struct Node {
	int data;
	Node* next;
	Node(int d) {
		data = d;
		next = NULL;
	}
};

class Stack {
public:
	Stack() { total_num = 0; head = NULL; }
	int Size();
	void Push(int d);
	int Pop();
private:
	Node* head;
	int total_num;
};

int Stack::Size() {
	return total_num;
}

void Stack::Push(int d) {
	Node* p = new Node(d);
	if (head == NULL) {
		head = p;
	}
	else {
		p->next = head;
		head = p;
	}
	total_num += 1;
}

int Stack::Pop() {
	Node* p = head;
	int x = head->data;
	head = p->next;
	delete p;
	total_num -= 1;
	return x;
}

int main() {
	Stack s;
	int m, n;
	cin >> m >> n;
	for (int i = 0; i < m; ++i) {
		int temp;
		cin >> temp;
		s.Push(temp);
	}

	for (int i = 0; i < n; ++i) {
		cout << s.Pop() << " ";
	}
	cout << s.Size() << endl;
}