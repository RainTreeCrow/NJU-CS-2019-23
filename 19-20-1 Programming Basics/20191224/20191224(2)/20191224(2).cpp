#include <iostream>
using namespace std;

int remained;

struct ListNode {
	int no;
	ListNode* link;
};

ListNode* Josephus(ListNode* cur, int M) {
	while (remained > 1) {
		for (int i = 1; i < M; i++)
			cur = cur->link;
		ListNode* p = cur->link;
		cur->link = p->link;
		delete p;
		remained -= 1;
	}
	return cur;
}

int main() {
	int n, m;
	cin >> n >> m;
	ListNode *first, *last;
	first = last = new ListNode;
	first->no = 1;
	for (int i = 2; i <= n; i++) {
		ListNode* p = new ListNode;
		p->no = i;
		last->link = p;
		last = p;
	}
	last->link = first;
	remained = n;
	ListNode* cur = last;
	cout << Josephus(cur, m)->no << endl;
	return 0;
}