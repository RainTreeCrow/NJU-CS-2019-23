#include <iostream>
using namespace std;

template <class T>
struct BinTreeNode {
    T data;
    BinTreeNode<T>* leftChild, * rightChild;
    BinTreeNode(T x, BinTreeNode<T>* l = NULL, BinTreeNode<T>* r = NULL) {
        data = x;  leftChild = l;  rightChild = r;
    }
};

template <class T>
class BinaryTree {
public:
    BinaryTree(T ref) : refValue(ref), root(NULL) { }
    ~BinaryTree() { /*destroy(root);*/ }
    void CreateBinTree(T* list, int len) {
        if (len == 0)
            root = NULL;
        else {
            BinTreeNode<T>** stack = new BinTreeNode<T> * [len];
            stack[0] = new BinTreeNode<T>(list[0]);
            int index = 0, count = 1;
            bool left = true;
            for (int i = 1; i < len; i++) {
                if (list[i] == refValue) {
                    if (left) {
                        stack[index]->leftChild = NULL;
                        left = false;
                    }
                    else {
                        stack[index++]->rightChild = NULL;
                        left = true;
                    }
                }
                else {
                    stack[count] = new BinTreeNode<T>(list[i]);
                    if (left) {
                        stack[index]->leftChild = stack[count];
                        left = false;
                    }
                    else {
                        stack[index++]->rightChild = stack[count];
                        left = true;
                    }
                    count++;
                }
            }
            root = stack[0];
        }

    }
    T refValue;
    BinTreeNode<T>* root;
    void destroy(BinTreeNode<T>*& subTree) {
        if (subTree != NULL) {
            destroy(subTree->leftChild);
            destroy(subTree->rightChild);
            delete subTree;
        }
    }
    bool Find(BinTreeNode<T>* subTree, T x) const {
        if (subTree == NULL)
            return false;
        else if (subTree->data == x)
            return true;
        else
            return Find(subTree->leftChild, x) || Find(subTree->rightChild, x);
    }
};

template <class T>
bool isLeaf(BinTreeNode<T>* n) {
    return n->leftChild == NULL && n->rightChild == NULL;
}

template <class T>
bool reverseEqual(BinTreeNode<T>* n1, BinTreeNode<T>* n2) {
    if (n1 == NULL)
        return n2 == NULL;
    else if (n2 == NULL)
        return n1 == NULL;
    else if (isLeaf(n1) && isLeaf(n2))
        return n1->data == n2->data;
    else {
        if (n1->data != n2->data)
            return false;
        else
            return (reverseEqual(n1->leftChild, n2->leftChild) && reverseEqual(n1->rightChild, n2->rightChild))
            || (reverseEqual(n1->leftChild, n2->rightChild) && reverseEqual(n1->rightChild, n2->leftChild));
    }
}

template <class T>
bool reverseEqual(BinaryTree<T> tree1, BinaryTree<T> tree2) {
    return reverseEqual(tree1.root, tree2.root);
}

int main()
{
    BinaryTree<int> tree1(-1);
    BinaryTree<int> tree2(-1);
    int n1, n2;
    cin >> n1;
    int* list1 = new int[n1];
    for (int i = 0; i < n1; i++)
        cin >> list1[i];
    tree1.CreateBinTree(list1, n1);
    cin >> n2;
    int* list2 = new int[n2];
    for (int i = 0; i < n2; i++)
        cin >> list2[i];
    tree2.CreateBinTree(list2, n2);
    if (reverseEqual(tree1, tree2))
        cout << "True";
    else
        cout << "False";
    return 0;
}