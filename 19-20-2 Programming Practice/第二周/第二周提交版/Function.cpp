#include <iostream>
#include "Function.h"
using namespace std;

int list_tail_insert(Node* list_head, int var) {
	Node* p = new Node;
	p->var = var;
	p->link = NULL;
	if (list_head == NULL) {
		cout << "There is no list!" << endl;
		return -1;
	}
	Node* q = list_head;
	for (q; q->link != NULL; q = q->link);
	q->link = p;
	return 0;
}

Node* list_head_insert(Node* list_head, int var) {
	Node* p = new Node;
	p->var = var;
	p->link = list_head;
	return p;
}

Node* list_specific_insert(Node* list_head, int location, int var) {
	if (location == 1)
		return list_head_insert(list_head, var);
	Node* p = new Node;
	p->var = var;
	p->link = NULL;
	Node* q = list_head;
	int i;
	for (i = 1; i < location - 1 && q->link != NULL; i++) {
		q = q->link;
	}
	if (i == location - 1) {
		p->link = q->link;
		q->link = p;
	}
	else {
		cout << "The list is not long enough!" << endl;
	}
	return list_head;
}

void print_list(Node* list_head) {
	Node* p;
	for (p = list_head; p->link != NULL; p = p->link) {
		cout << p->var << ' ';
	}
	cout << p->var << endl;
}

void reverse_print_helper(Node* list_head) {
	if (list_head->link == NULL)
		cout << list_head->var;
	else {
		reverse_print_helper(list_head->link);
		cout << ' ' << list_head->var;
	}
}

void reverse_print_list(Node* list_head) {
	reverse_print_helper(list_head);
	cout << endl;
}

void change_specific_var(Node* list_head, int old_var, int new_var) {
	Node* q = list_head;
	for (q; q != NULL; q = q->link) {
		if (q->var == old_var)
			q->var = new_var;
	}
}

Node* del_specific_var(Node* list_head, int del_var) {
	Node* q = list_head;
	Node* temp;
	for (q; q->link != NULL;) {
		if (q->link->var == del_var) {
			temp = q->link->link;
			q->link = temp;
		}
		else
			q = q->link;
	}
	if (list_head->var == del_var)
		list_head = list_head->link;
	return list_head;
}

Node* sort(Node* list_head) {
	Node* p, * q;
	int temp;
	for (p = list_head; p != NULL; p = p->link) {
		for (q = p->link; q != NULL; q = q->link) {
			if (p->var > q->var) {
				temp = p->var;
				p->var = q->var;
				q->var = temp;
			}
		}
	}
	return list_head;
}

bool is_end(Tree_Node* T) {
	if (T->lchild == NULL && T->rchild == NULL)
		return true;
	return false;
}

Tree_Node* insert(Tree_Node* T, int x) {
	if (T == NULL) {
		Tree_Node* tree = new Tree_Node;
		tree->var = x;
		tree->lchild = NULL;
		tree->rchild = NULL;
		return tree;
	}
	if (x == T->var) {
		cout << "Illegal number for the current tree!" << endl;
		return T;
	}
	if (is_end(T)) {
		Tree_Node* temp = new Tree_Node;
		temp->var = x;
		temp->lchild = NULL;
		temp->rchild = NULL;
		if (x < T->var)
			T->lchild = temp;
		else
			T->rchild = temp;
	}
	else {
		if (x < T->var)
			T->lchild = insert(T->lchild, x);
		else
			T->rchild = insert(T->rchild, x);
	}
	return T;
}

void postorder(Tree_Node* T) {
	if (is_end(T))
		cout << T->var;
	else if (T->lchild != NULL) {
		postorder(T->lchild);
		if (T->rchild != NULL) {
			cout << ' ';
			postorder(T->rchild);
		}
		cout << ' ' << T->var;
	}
	else {
		postorder(T->rchild);
		cout << ' ' << T->var;
	}
}