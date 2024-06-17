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
    //void levelOrder(void (*visit)(BinTreeNode<T>* t));
    //int Insert(const T item);
    BinTreeNode<T>* Find(T item) const {
        return Find(root, item);
    }
    void S(int len) {
        BinTreeNode<T>** odd = new BinTreeNode<T>*[len];
        BinTreeNode<T>** even = new BinTreeNode<T>*[len];
        T* result = new T[len];
        int oddTop = -1;
        int evenTop = -1;
        int count = 0;
        bool isOdd = 1;
        BinTreeNode<T>* p = root;
        if (root != NULL) {
            result[count] = root->data;
            count++;
            oddTop++;
            odd[oddTop] = root;
        }
        while (oddTop != -1 || evenTop != -1) {
            if (isOdd) {
                p = odd[oddTop];
                oddTop--;
                if (p->leftChild != NULL) {
                    result[count] = p->leftChild->data;
                    evenTop++;
                    even[evenTop] = p->leftChild;
                    count++;
                }
                if (p->rightChild != NULL) {
                    result[count] = p->rightChild->data;
                    evenTop++;
                    even[evenTop] = p->rightChild;
                    count++;
                }
                if (oddTop == -1)
                    isOdd = 0;
            }
            else {
                p = even[evenTop];
                evenTop--;
                if (p->rightChild != NULL) {
                    result[count] = p->rightChild->data;
                    oddTop++;
                    odd[oddTop] = p->rightChild;
                    count++;
                }
                if (p->leftChild != NULL) {
                    result[count] = p->leftChild->data;
                    oddTop++;
                    odd[oddTop] = p->leftChild;
                    count++;
                }
                if (evenTop == -1)
                    isOdd = 1;
            }
        }
        for (int i = 0; i < len - 1; i++)
            cout << result[i] << ' ';
        cout << result[len - 1];
    }
protected:
    BinTreeNode<T>* root;
    void CreateBinTree(BinTreeNode<T>*& subTree, T* in, T* post, int len) {
        if (len == 0)
            subTree = NULL;
        else if (len == 1) {
            subTree = new BinTreeNode<T>(in[0]);
        }
        else if (len == 2) {
            if (in[1] == post[1]) {
                BinTreeNode<T>* tempLeft = new BinTreeNode<T> (in[0], NULL, NULL);
                subTree = new BinTreeNode<T>(in[1], tempLeft, NULL);
            }
            else {
                BinTreeNode<T>* tempRight = new BinTreeNode<T> (in[1], NULL, NULL);
                subTree = new BinTreeNode<T>(in[0], NULL, tempRight);
            }
        }
        else {
            int div = -1;
            for (int i = 0; i < len; i++) {
                if (in[i] == post[len - 1]) {
                    div = i;
                    break;
                }
            }
            subTree = new BinTreeNode<T>(post[len - 1]);
            if (subTree == NULL) {
                cerr << "存储分配错!" << endl;  exit(1);
            }
            int* leftIn = new int[div];
            int* leftPost = new int[div];
            for (int i = 0; i < div; i++) {
                leftIn[i] = in[i];
                leftPost[i] = post[i];
            }
            CreateBinTree(subTree->leftChild, leftIn, leftPost, div);
            int* rightIn = new int[len - div - 1];
            int* rightPost = new int[len - div - 1];
            for (int i = div + 1; i < len; i++) {
                rightIn[i - div - 1] = in[i];
                rightPost[i - div - 1] = post[i - 1];
            }
            CreateBinTree(subTree->rightChild, rightIn, rightPost, len - div - 1);
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
    int* in = new int[len];
    int* post = new int[len];
    for (int i = 0; i < len; i++)
        cin >> in[i];
    for (int i = 0; i < len; i++)
        cin >> post[i];
    BinaryTree<int> tree;
    tree.CreateBinTree(in, post, len);
    //tree.preOrder(print);
    //tree.inOrder(print);
    //tree.postOrder(print);
    tree.S(len);
    return 0;
}