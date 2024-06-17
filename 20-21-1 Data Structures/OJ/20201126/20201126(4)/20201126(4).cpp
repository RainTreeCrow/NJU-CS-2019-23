#include <iostream>
using namespace std;

static int HEIGHT = 0;

template <class T>
struct BinTreeNode {
    T data;
    BinTreeNode<T>* leftChild, * rightChild, *parent;
    BinTreeNode(T x, BinTreeNode<T>* l = NULL, BinTreeNode<T>* r = NULL, BinTreeNode<T>* p = NULL) {
        data = x;  leftChild = l;  rightChild = r;  parent = p;
    }
};

template <class T>
struct LevelNode {
    BinTreeNode<T>* treeNode;
    LevelNode<T>* next;
    LevelNode(BinTreeNode<T>* t, LevelNode<T>* n = NULL) {
        treeNode = t;  next = n;
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
                        stack[count]->parent = stack[index];
                        left = false;
                    }
                    else {
                        stack[index]->rightChild = stack[count];
                        stack[count]->parent = stack[index];
                        index++;
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

LevelNode<int>* level[10000];

template <class T>
void insert(BinTreeNode<T>* t, int curHeight) {
    if (t == NULL) return;
    if (curHeight > HEIGHT) HEIGHT = curHeight;
    //cout << curHeight << ' ' << t->data << endl;
    LevelNode<T>* temp = new LevelNode<T>(t);
    temp->next = level[curHeight];
    level[curHeight] = temp;
    insert(t->leftChild, curHeight + 1);
    insert(t->rightChild, curHeight + 1);
}

int main()
{
    BinaryTree<int> tree(-1);
    int n;
    cin >> n;
    int* list = new int[n];
    for (int i = 0; i < n; i++)
        cin >> list[i];
    tree.CreateBinTree(list, n);
    BinTreeNode<int>* p = tree.root;
    insert(p, 0);
    int temp, distance = 0;
    //cout << HEIGHT;
    for (int i = HEIGHT; i > 0; i--) {
        LevelNode<int>* l = level[i];
        while (l != NULL) {
            //cout << l->treeNode->data << ' ';
            temp = l->treeNode->data - 1;
            if (temp >= 0)
                distance += temp;
            else distance -= temp;
            l->treeNode->parent->data += temp;
            l = l->next;
        }
    }
    cout << distance;
    return 0;
}