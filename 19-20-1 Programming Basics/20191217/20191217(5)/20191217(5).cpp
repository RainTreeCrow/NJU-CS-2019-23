#include <iostream>
using namespace std;

struct Node
{
	int content;
	Node* next;
};

int main()
{
	int n, a, b, i, temp;
	cin >> n >> a >> b;
	Node* head = NULL, * tail = head;
	for (i = 0; i < n; i++) {
		Node* p = new Node;
		cin >> p->content;
		p->next = NULL;
		if (head == NULL)
			head = p;
		else
			tail->next = p;
		tail = p;
	}
	Node* pre = NULL;
	Node* cur = NULL;
	Node* nxt = head;
	while (nxt != NULL) {
		pre = cur;
		cur = nxt;
		nxt = cur->next;
		cur->next = pre;
	}
	Node* pa = NULL;
	Node* ca = NULL;
	Node* na = cur;
	for (i = 1; i < a; i++) {
		pa = ca;
		ca = na;
		na = ca->next;
	}
	Node* previous = ca;
	if (previous != NULL)
		previous->next = NULL;
	Node* start = na;
	for (i = 0; i <= b - a; i++) {
		pa = ca;
		ca = na;
		na = ca->next;
		ca->next = pa;
	}
	start->next = na;
	if (previous != NULL) {
		previous->next = ca;
		for (Node* p = cur; p != NULL; p = p->next)
			cout << p->content << ' ';
	}
	else {
		for (Node* p = ca; p != NULL; p = p->next)
			cout << p->content << ' ';
	}
	return 0;
}