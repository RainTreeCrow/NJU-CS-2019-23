#include <iostream>
using namespace std;

struct Node {
	int label;
	Node* left;
	Node* right;
};

bool is_end(Node* T) {
	if (T->left == NULL && T->right == NULL)
		return true;
	return false;
}

Node* insert(Node* T, int x) {
	if (T == NULL) {
		Node* tree = new Node;
		tree->label = x;
		tree->left = NULL;
		tree->right = NULL;
		return tree;
	}
	if (x == T->label) {
		cout << "Illegal number for the current tree!" << endl;
		return T;
	}
	if (is_end(T)) {
		Node* temp = new Node;
		temp->label = x;
		temp->left = NULL;
		temp->right = NULL;
		if (x < T->label)
			T->left = temp;
		else
			T->right = temp;
	}
	else {
		if (x < T->label)
			T->left = insert(T->left, x);
		else
			T->right = insert(T->right, x);
	}
	return T;
}

void postorder(Node* T) {
	if (is_end(T))
		cout << T->label;
	else if (T->left != NULL) {
		postorder(T->left);
		if (T->right != NULL) {
			cout << ' ';
			postorder(T->right);
		}
		cout << ' ' << T->label;
	}
	else {
		postorder(T->right);
		cout << ' ' << T->label;
	}
}

int main()
{
	int n, i;
	cin >> n;
	Node* tree = NULL;
	int* a = new int[n];
	for (i = 0; i < n; i++)
		cin >> a[i];
	for (i = 0; i < n; i++)
		tree = insert(tree, a[i]);
	postorder(tree);
	return 0;
}