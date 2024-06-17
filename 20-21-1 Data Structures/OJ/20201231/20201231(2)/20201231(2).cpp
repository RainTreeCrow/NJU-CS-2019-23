#include <iostream>
#include <cmath>
using namespace std;

long long int C(long long int total, long long int part) {
    long long int res = 1;
    for (long long int i = total - part + 1; i <= total; i++)
        res *= i;
    for (long long int i = part; i >= 2; i--)
        res /= i;
    return res;
}

template <class E, class K>
struct BSTNode {			    //二叉树结点类
    E data;				    //数据域
    BSTNode<E, K>* left, * right;  //左子女和右子女
    long long int Children;
    BSTNode() { left = NULL; right = NULL; }
    //构造函数
    BSTNode(const E d, BSTNode<E, K>* L = NULL,
        BSTNode<E, K>* R = NULL) {
        data = d; left = L; right = R; Children = -1;
    }
    //构造函数
    ~BSTNode() {}				//析构函数
    void setData(E d) { data = d; }	//修改	
    E getData() { return data; }		//提取
    bool operator < (const E& x) {	//重载：判小于
        return data.key < x.key;
    }
    bool operator > (const E& x) {	//重载：判大于
        return data.key > x.key;
    }
    bool operator == (const E& x) {	//重载：判等于
        return data.key == x.key;
    }
};

template <class E, class K>
class BST {				  //二叉搜索树类定义
public:
    BST() { root = NULL; }	  //构造函数
    ~BST() {};			  //析构函数	
    bool Search(const K x) const {	//搜索 
        return Search(x, root) != NULL;
    }
    void makeEmpty() 			//置空
    {
        makeEmpty(root); root = NULL;
    }
    //void PrintTree() const { PrintTree(root); }    //输出
    bool Insert(const E& e1) {               //插入新元素
        return Insert(e1, root);
    }
    bool Remove(const K x) { return Remove(x, root); } 	  //删除含x的结点
    long long int Possibilities() { return Possibilities(root); }
private:
    BSTNode<E, K>* root;	//根指针
    //void PrintTree(BSTNode<E, K>* ptr) const;						//递归：打印
    bool Insert(const E& e1, BSTNode<E, K>*& ptr);					//递归：插入
    long long int CountChildren(BSTNode<E, K>*& ptr) {
        if (ptr == NULL) return 0;
        else {
            long long int temp = ptr->Children;
            if (temp < 0) {
                temp = CountChildren(ptr->left) + CountChildren(ptr->right) + 1;
                ptr->Children = temp;
            }
            return temp;
        }
    }
    long long int Possibilities(BSTNode<E, K>* ptr) {
        if (ptr == NULL) return 0;
        else if (ptr->left == NULL) {
            if (ptr->right == NULL) return 1;
            else return Possibilities(ptr->right);
        }
        else if (ptr->right == NULL)
            return Possibilities(ptr->left);
        else {
            long long int part = CountChildren(ptr->left);
            long long int total = part + CountChildren(ptr->right);
            return Possibilities(ptr->left) * Possibilities(ptr->right) * C(total, part);
        }
    }
};

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

int main()
{
    int n, temp;
    BST<int, int> tree;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        tree.Insert(temp);
    }
    cout << tree.Possibilities();
    return 0;
}