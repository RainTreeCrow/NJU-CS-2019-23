#include <iostream>
#include "Function.h"
#include "Function.cpp"
using namespace std;

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
	int n, i;
	cin >> n;
	Tree_Node* tree = NULL;
	int* a = new int[n];
	for (i = 0; i < n; i++)
		cin >> a[i];
	for (i = 0; i < n; i++)
		tree = insert(tree, a[i]);
	postorder(tree);
	return 0;
}