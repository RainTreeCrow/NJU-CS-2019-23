#include <iostream>
using namespace std;

struct Node
{
	int content;
	Node *next;
};

int main()
{
	int n, i;
	cin >> n;
	Node *head = NULL, *tail = NULL;
	for (i = 0; i < n; i++){
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
	for (Node* p = cur; p != NULL; p = p->next)
		cout << p->content <<' ';
	return 0;
}