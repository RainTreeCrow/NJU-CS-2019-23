#include <iostream>
#include <cmath>
using namespace std;

int MAX_BALANCE = 0;

template <class E, class K>
struct BSTNode {
    E data;
    BSTNode<E, K>* left, * right;
    BSTNode() { left = NULL; right = NULL; }
    BSTNode(const E d, BSTNode<E, K>* L = NULL,
        BSTNode<E, K>* R = NULL) {
        data = d; left = L; right = R;
    }
    ~BSTNode() {}
    void setData(E d) { data = d; }
    E getData() { return data; }
    bool operator < (const E& x) {
        return data.key < x.key;
    }
    bool operator > (const E& x) {
        return data.key > x.key;
    }
    bool operator == (const E& x) {
        return data.key == x.key;
    }
};

template <class E, class K>
class BST {
public:
    BST() { root = NULL; RefValue = NULL; }
    BST(K value);
    ~BST() {};	
    bool Search(const K x) const {
        return Search(x, root) != NULL;
    }
    //void PrintTree() const { PrintTree(root); }    //输出
    bool Insert(const E& e1) {               //插入新元素
        return Insert(e1, root);
    }
    bool Remove(const K x) { return Remove(x, root); } 	  //删除含x的结点
    void UpdateMaxBalance() { UpdateMaxBalance(root); }
private:
    BSTNode<E, K>* root;	//根指针
    K RefValue;	 		//输入停止标志
    BSTNode<E, K>* Search(const K x, BSTNode<E, K>* ptr);
    //void PrintTree(BSTNode<E, K>* ptr) const;						//递归：打印
    bool Insert(const E& e1, BSTNode<E, K>*& ptr);					//递归：插入
    bool Remove(const K x, BSTNode<E, K>*& ptr);					//递归：删除
    int Height(BSTNode<E, K>* ptr) {
        if (ptr == NULL) return 0;
        else if (ptr->left == NULL && ptr->right == NULL)
            return 1;
        else
            return max(Height(ptr->left), Height(ptr->right)) + 1;
    }
    int Balance(BSTNode<E, K>* ptr) {
        return abs(Height(ptr->right) - Height(ptr->left));
    }
    void UpdateMaxBalance(BSTNode<E, K>*& ptr) {
        if (ptr == NULL) return;
        else {
            int temp = Balance(ptr);
            if (temp > MAX_BALANCE)
                MAX_BALANCE = temp;
            UpdateMaxBalance(ptr->left);
            UpdateMaxBalance(ptr->right);
        }
    }
};

template<class E, class K>
BSTNode<E, K>* BST<E, K>::
Search(const K x, BSTNode<E, K>* ptr) {
    //私有递归函数：在以ptr为根的二叉搜索树中搜
    //索含x的结点。若找到，则函数返回该结点的
    //地址，否则函数返回NULL值。
    if (ptr == NULL) return NULL;
    else if (x < ptr->data) return Search(x, ptr->left);
    else if (x > ptr->data) return Search(x, ptr->right);
    else return ptr;				//搜索成功
};

/*template<class E, class K>
BSTNode<E, K>* BST<E, K>::
Search(const K x, BSTNode<E, K>* ptr) {
    //非递归函数：作为对比，在当前以ptr为根的二
    //叉搜索树中搜索含x的结点。若找到，则函数返
    //回该结点的地址，否则函数返回NULL值。
    if (ptr == NULL) return NULL;
    BSTNode<E, K>* temp = ptr;
    while (temp != NULL) {
        if (x == temp->data) return temp;
        if (x < temp->data) temp = temp->left;
        else temp = temp->right;
    }
    return NULL;
};*/

template <class E, class K>
bool BST<E, K>::Insert(const E& e1,
    BSTNode<E, K>*& ptr) {
    //私有函数：在以ptr为根的二叉搜索树中插入值为
    //e1的结点。若在树中已有含e1的结点则不插入
    if (ptr == NULL) {	   //新结点作为叶结点插入
        ptr = new BSTNode<E, K>(e1);	  //创建新结点
        if (ptr == NULL) {
            cerr << "Out of space" << endl;  exit(1);
        }
        return true;
    }
    else if (e1 < ptr->data) Insert(e1, ptr->left);	 		//左子树插入
    else if (e1 > ptr->data) Insert(e1, ptr->right);		//右子树插入
    else return false;	      //x已在树中,不再插入
};

template <class E, class K>
BST<E, K>::BST(K value) {
    //输入一个元素序列, 建立一棵二叉搜索树
    E x;
    root = NULL;  RefValue = value;	     //置空树
    cin >> x;					     //输入数据
    while (x.key != RefValue) {				//RefValue是一个输入结束标志
        Insert(x, root);  cin >> x;	   //插入，再输入数据
    }
};

template <class E, class K>
bool BST<E, K>::Remove(const K x,
    BSTNode<E, K>*& ptr) {
    //在以 ptr 为根的二叉搜索树中删除含 x 的结点
    BSTNode<E, K>* temp;
    if (ptr != NULL) {
        if (x < ptr->data) Remove(x, ptr->left);
        //在左子树中执行删除
        else if (x > ptr->data) Remove(x, ptr->right);
        //在右子树中执行删除
        else if (ptr->left != NULL && ptr->right != NULL)
        {       //ptr指示关键码为x的结点，它有两个子女
            temp = ptr->right;
            //到右子树搜寻中序下第一个结点
            while (temp->left != NULL)
                temp = temp->left;
            ptr->data = temp->data;
            //用该结点数据代替根结点数据
            Remove(ptr->data, ptr->right);
        }
        else {	//ptr指示关键码为x的结点有一个子女
            temp = ptr;
            if (ptr->left == NULL) ptr = ptr->right;
            else ptr = ptr->left;
            delete temp;
            return true;
        }
    }
    return false;
};

int main()
{
    int n, temp;
    BST<int, int> tree;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        tree.Insert(temp);
    }
    tree.UpdateMaxBalance();
    cout << MAX_BALANCE;
    return 0;
}