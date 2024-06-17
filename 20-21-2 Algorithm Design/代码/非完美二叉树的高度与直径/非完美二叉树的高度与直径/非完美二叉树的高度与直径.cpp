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
void print(BinTreeNode<T>* t) {
    if (t != NULL)
        cout << t->data << ' ';
}

template <class T>
class BinaryTree {
public:
    BinaryTree() : root(NULL) { }
    BinaryTree(BinaryTree<T>& s) { root = Copy(s); }
    ~BinaryTree() { destroy(root); }
    bool IsEmpty() { return root == NULL; }
    void CreateBinTree(T* in, T* post, int len) { CreateBinTree(root, in, post, len); }
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
    BinTreeNode<T>* Find(T item) const {
        return Find(root, item);
    }
    int Diameter() {
        int left = Height(root->leftChild);
        int right = Height(root->rightChild);
        return left + right + 2;
    }
protected:
    BinTreeNode<T>* root;
    void CreateBinTree(BinTreeNode<T>*& subTree, T* pre, T* in, int len) {
        if (len == 0)
            subTree = NULL;
        else if (len == 1) {
            subTree = new BinTreeNode<T>(pre[0]);
        }
        else if (len == 2) {
            if (pre[1] == in[1]) {
                BinTreeNode<T>* tempRight = new BinTreeNode<T>(pre[1], NULL, NULL);
                subTree = new BinTreeNode<T>(pre[0], NULL, tempRight);
            }
            else {
                BinTreeNode<T>* tempLeft = new BinTreeNode<T>(pre[0], NULL, NULL);
                subTree = new BinTreeNode<T>(pre[1], tempLeft, NULL);
            }
        }
        else {
            int div = -1;
            for (int i = 0; i < len; i++) {
                if (in[i] == pre[0]) {
                    div = i;
                    break;
                }
            }
            subTree = new BinTreeNode<T>(pre[0]);
            if (subTree == NULL)
                exit(1);
            int* leftPre = new int[div];
            int* leftIn = new int[div];
            for (int i = 0; i < div; i++) {
                leftPre[i] = pre[i + 1];
                leftIn[i] = in[i];
            }
            CreateBinTree(subTree->leftChild, leftPre, leftIn, div);
            int* rightPre = new int[len - div - 1];
            int* rightIn = new int[len - div - 1];
            for (int i = div + 1; i < len; i++) {
                rightPre[i - div - 1] = pre[i];
                rightIn[i - div - 1] = in[i];
            }
            CreateBinTree(subTree->rightChild, rightPre, rightIn, len - div - 1);
            delete[]leftPre;
            delete[]leftIn;
            delete[]rightPre;
            delete[]rightIn;
        }
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
        if (subTree == NULL) return -1;
        //else if (subTree->leftChild == NULL && subTree->rightChild == NULL) return 0;
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
    void preOrder(BinTreeNode<T>* subTree, void (*visit) (BinTreeNode<T>* t)) {
        if (subTree != NULL) {
            visit(subTree);
            preOrder(subTree->leftChild, visit);
            preOrder(subTree->rightChild, visit);
        }
    }
    void inOrder(BinTreeNode<T>* subTree, void (*visit) (BinTreeNode<T>* t)) {
        if (subTree != NULL) {
            inOrder(subTree->leftChild, visit);
            visit(subTree);
            inOrder(subTree->rightChild, visit);
        }
    }
    void postOrder(BinTreeNode<T>* subTree, void (*visit) (BinTreeNode<T>* t)) {
        if (subTree != NULL) {
            postOrder(subTree->leftChild, visit);
            postOrder(subTree->rightChild, visit);
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
    int len;
    cin >> len;
    int* pre = new int[len];
    int* in = new int[len];
    for (int i = 0; i < len; i++)
        cin >> pre[i];
    for (int i = 0; i < len; i++)
        cin >> in[i];
    BinaryTree<int> tree;
    tree.CreateBinTree(pre, in, len);
    /*
    tree.preOrder(print);
    cout << endl;
    tree.inOrder(print);
    cout << endl;
    tree.postOrder(print);
    cout << endl;
    */
    cout << "I have read the rules about plagiarism punishment" << endl;
    cout << tree.Height() << endl;
    cout << tree.Diameter();
    return 0;
}