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
    ~BinaryTree() { destroy(root); }
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
    T Ancestor(T a, T b) {
        BinTreeNode<T>* p = root;
        while (1) {
            if (Find(p->leftChild, a) && Find(p->leftChild, b))
                p = p->leftChild;
            else if (Find(p->rightChild, a) && Find(p->rightChild, b))
                p = p->rightChild;
            else
                break;
        }
        return p->data;
    }
protected:
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

int main()
{
    BinaryTree<int> family(-1);
    int a, b;
    cin >> a >> b;
    int len;
    cin >> len;
    int* list = new int[len];
    for (int i = 0; i < len; i++)
        cin >> list[i];
    family.CreateBinTree(list, len);
    int an = family.Ancestor(a, b);
    cout << an;
    return 0;
}