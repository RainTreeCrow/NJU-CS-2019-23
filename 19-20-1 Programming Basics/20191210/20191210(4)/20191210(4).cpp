#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* buildList(const string& input) {
	vector<int> list;
	stringstream ss;
	ss.str(input);
	string item;
	while (getline(ss, item, '>')) {
		list.push_back(stoi(item));
	}

	ListNode* dummy = new ListNode(0);
	ListNode* ptr = dummy;
	for (int item : list) {
		ptr->next = new ListNode(item);
		ptr = ptr->next;
	}
	ptr = dummy->next;
	delete dummy;
	return ptr;
}

int main() {
	string s1, s2;
	cin >> s1 >> s2;
	ListNode* l1 = buildList(s1);
	ListNode* l2 = buildList(s2);

	int l = (s1.length() + 2) / 3 + (s2.length() + 2) / 3;
	int* p = new int[l];
	int i, j, temp, x = 0;
	for (ListNode* i = l1; i != NULL; i = i->next) {
		p[x] = i->val;
		x += 1;
	}
	for (ListNode* j = l2; j != NULL; j = j->next) {
		p[x] = j->val;
		x += 1;
	}
	for (i = 0; i < x; i++) {
		for (j = 0; j < x - 1 - i; j++) {
			if (p[j] > p[j + 1]) {
				temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}
	for (i = 0; i < x - 1; i++)
		cout << p[i] << "->";
	cout << p[x - 1];
	return 0;
}