#include <iostream>
using namespace std;

template <class T>
struct BinTreeNode {
    T data;
    BinTreeNode<T>* leftChild, * rightChild;
    BinTreeNode() {
        leftChild = NULL;  rightChild = NULL;
    }
    BinTreeNode(T x, BinTreeNode<T>* l = NULL, BinTreeNode<T>* r = NULL) {
        data = x;  leftChild = l;  rightChild = r;
    }
};

template <class T>
class BinaryTree {
public:
    BinaryTree(T value) : RefValue(value), root(NULL) { }
    BinaryTree(BinaryTree<T>& s) { RefValue = s.RefValue; root = Copy(s); }
    ~BinaryTree() { destroy(root); }
    bool IsEmpty() { return root == NULL; }
    void CreateBinTree() { CreateBinTree(root); }
    int Height() { return Height(root); }
    int Size() { return Size(root); }
    BinTreeNode<T>* Parent(BinTreeNode <T>* t) {
        return (root == NULL || root == t) ?
            NULL : Parent(root, t);
    }
    BinTreeNode<T>* LeftChild(BinTreeNode<T>* t) {
        return (t != NULL) ? t->leftChild : NULL;
    }
    BinTreeNode<T>* RightChild(BinTreeNode<T>* t) {
        return (t != NULL) ? t->rightChild : NULL;
    }
    BinTreeNode<T>* getRoot() const { return root; }
    void preOrder(void (*visit) (BinTreeNode<T>* t)) {
        preOrder(root, visit);
    }
    void inOrder(void (*visit) (BinTreeNode<T>* t)) {
        inOrder(root, visit);
    }
    void postOrder(void (*visit) (BinTreeNode<T>* t)) {
        postOrder(root, visit);
    }
    bool FindRoute(T length) {
        return FindRoute(root, length);
    }
    //void levelOrder(void (*visit)(BinTreeNode<T>* t));
    //int Insert(const T item);
    BinTreeNode<T>* Find(T item) const {
        return Find(root, item);
    }
protected:
    BinTreeNode<T>* root;
    T RefValue;
    void CreateBinTree(BinTreeNode<T>*& subTree) {
        T item;
        cin >> item;
        if (item != RefValue) {
            subTree = new BinTreeNode<T>(item);
            if (subTree == NULL) {
                cerr << "存储分配错!" << endl;  exit(1);
            }
            CreateBinTree(subTree->leftChild);
            CreateBinTree(subTree->rightChild);
        }
        else subTree = NULL;
    }
    //bool Insert(BinTreeNode<T>*& subTree, T& x);
    void destroy(BinTreeNode<T>*& subTree) {
        if (subTree != NULL) {
            destroy(subTree->leftChild);
            destroy(subTree->rightChild);
            delete subTree;
        }
    }
    BinTreeNode<T>* Copy(BinTreeNode<T>* r) {
        BinTreeNode<T>* p = new BinTreeNode<T>(r->data);
        p->leftChild = Copy(r->leftChild);
        p->rightChild = Copy(r->rightChild);
        return p;
    }
    int Height(BinTreeNode<T>* subTree) {
        if (subTree == NULL) return 0;
        else {
            int leftHeight = Height(subTree->leftChild);
            int rightHeight = Height(subTree->rightChild);
            return (leftHeight >= rightHeight) ? leftHeight + 1 : rightHeight + 1;
        }
    }
    int Size(BinTreeNode<T>* subTree) {
        if (subTree == NULL) return 0;
        else {
            int leftSize = Size(subTree->leftChild);
            int rightSize = Size(subTree->rightChild);
            return leftSize + rightSize + 1;
        }
    }
    BinTreeNode<T>* Parent(BinTreeNode<T>* subTree, BinTreeNode<T>* t) {
        if (subTree == NULL) return NULL;
        if (subTree->leftChild == t || subTree->rightChild == t)
            return subTree;
        BinTreeNode <T>* p;
        if ((p = Parent(subTree->leftChild, t)) != NULL)
            return p;
        else return Parent(subTree->rightChild, t);
    }
    BinTreeNode<T>* Find(BinTreeNode<T>* subTree, T x) const {
        if (subTree->data == x)
            return subTree;
        BinTreeNode <T>* p;
        if ((p = Find(subTree->leftChild, x) != NULL))
            return p;
        else return Find(subTree->rightChild, x);
    }
    void preOrder(BinTreeNode<T>& subTree, void (*visit) (BinTreeNode<T>* t)) {
        if (subTree != NULL) {
            visit(subTree);
            PreOrder(subTree->leftChild, visit);
            PreOrder(subTree->rightChild, visit);
        }
    }
    void inOrder(BinTreeNode<T>& subTree, void (*visit) (BinTreeNode<T>* t)) {
        if (subTree != NULL) {
            InOrder(subTree->leftChild, visit);
            visit(subTree);
            InOrder(subTree->rightChild, visit);
        }
    }
    void postOrder(BinTreeNode<T>& subTree, void (*visit) (BinTreeNode<T>* t)) {
        if (subTree != NULL) {
            PostOrder(subTree->leftChild, visit);
            PostOrder(subTree->rightChild, visit);
            visit(subTree);
        }
    }
    bool FindRoute(BinTreeNode<T>* subTree, T x) {
        if (subTree == NULL)
            return x == 0;
        else
            return FindRoute(subTree->leftChild, x - subTree->data) ||
                FindRoute(subTree->rightChild, x - subTree->data);
    }
};

int main()
{
    int n;
    cin >> n;
    BinaryTree<int> tree(-1);
    tree.CreateBinTree();
    bool b = tree.FindRoute(n);
    if (b) cout << "yes";
    else cout << "no";
    return 0;
}