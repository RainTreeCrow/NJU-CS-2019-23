#include <iostream>
using namespace std;

struct Node {
	int content;
	Node* next;
};

int list_tail_insert(Node* list_head, int var) {
	Node* p = new Node;
	p->content = var;
	p->next = NULL;
	if (list_head == NULL) {
		cout << "There is no list!" << endl;
		return -1;
	}
	Node* q = list_head;
	for (q; q->next != NULL; q = q->next);
	q->next = p;
	return 0;
}

Node* list_head_insert(Node* list_head, int var) {
	Node* p = new Node;
	p->content = var;
	p->next = list_head;
	return p;
}

Node* list_specific_insert(Node* list_head, int location, int var) {
	if (location == 1)
		return list_head_insert(list_head, var);
	Node* p = new Node;
	p->content = var;
	p->next = NULL;
	Node* q = list_head;
	int i;
	for (i = 1; i < location - 1 && q->next!= NULL; i++) {
		q = q->next;
	}
	if (i == location - 1) {
		p->next = q->next;
		q->next = p;
	}
	else {
		cout << "The list is not long enough!" << endl;
	}
	return list_head;
}

void print_list(Node* list_head) {
	Node* p;
	for (p = list_head; p->next != NULL; p = p->next) {
		cout << p->content << ' ';
	}
	cout << p->content << endl;
}

void reverse_print_helper(Node* list_head) {
	if (list_head->next == NULL)
		cout << list_head->content;
	else {
		reverse_print_helper(list_head->next);
		cout << ' ' << list_head->content;
	}
}

void reverse_print_list(Node* list_head) {
	reverse_print_helper(list_head);
	cout << endl;
}

void change_specific_var(Node* list_head, int old_var, int new_var) {
	Node* q = list_head;
	for (q; q != NULL; q = q->next) {
		if (q->content == old_var)
			q->content = new_var;
	}
}

Node* del_specific_var(Node* list_head, int del_var) {
	Node* q = list_head;
	Node* temp;
	for (q; q->next != NULL;) {
		if (q->next->content == del_var) {
			temp = q->next->next;
			q->next = temp;
		}
		else
			q = q->next;
	}
	if (list_head->content == del_var)
		list_head = list_head->next;
	return list_head;
}

Node* sort(Node* list_head) {
	Node* p, * q;
	int temp;
	for (p = list_head; p != NULL; p = p->next) {
		for (q = p->next; q != NULL; q = q->next) {
			if (p->content > q->content) {
				temp = p->content;
				p->content = q->content;
				q->content = temp;
			}
		}
	}
	return list_head;
}

int main()
{
	Node* head = NULL;
	int temp;
	head = list_head_insert(head, 1);
	head = list_head_insert(head, 2);
	head = list_head_insert(head, 2);
	temp = list_tail_insert(head, 5);
	temp = list_tail_insert(head, 6);
	head = list_specific_insert(head, 4, 4);
	print_list(head);
	head = sort(head);
	print_list(head);
	reverse_print_list(head);
	change_specific_var(head, 2, 3);
	print_list(head);
	head = del_specific_var(head, 3);
	print_list(head);
	return 0;
}