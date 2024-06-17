#include <iostream>
using namespace std;

struct Node {
	int score;
	Node* next;
};

int n;

Node* bubble_sort(Node* head) {
	for (int i = 0; i < n; i++) {
		Node* q = head;
		for (int j = 0; j < n - i - 1; j++) {
			if (q->score > q->next->score) {
				int temp = q->score;
				q->score = q->next->score;
				q->next->score = temp;
			}
			q = q->next;
		}
	}
	return head;
}


int main()
{
	cin >> n;
	Node* head = NULL;
	for (int i = 0; i < n; i++) {
		Node* p = new Node;
		cin >> p->score;
		p->next = NULL;
		if (head == NULL)
			head = p;
		else {
			p->next = head;
			head = p;
		}
	}
	Node* r = bubble_sort(head);
	while (r != NULL) {
		cout << r->score << ' ';
		r = r->next;
	}
	return 0;
}