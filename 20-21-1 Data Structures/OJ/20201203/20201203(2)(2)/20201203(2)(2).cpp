#include <iostream>
using namespace std;

class UFSets {	//集合中的各个子集合互不相交
public:
    UFSets(int sz);	//构造函数
    ~UFSets() { 	//析构函数
        delete[]parent;
        delete[]children;
    }
    //UFSets& operator = (UFSets& R);    //集合赋值
    void Union(int Root1, int Root2);	     //子集合并
    int Find(int x);				//查找x的根
    int MaxSet();
    void Merge(int Root1, int Root2);
private:
    int* number;
    int* parent;		  //集合元素数组(双亲表示)
    int* children;
    int size;			  //集合元素的数目
};

UFSets::UFSets(int sz) {
    //构造函数：sz 是集合元素个数，双亲数组的范围
    //为parent[0]～parent[size-1]。
    size = sz;			  //集合元素个数
    number = new int[size];
    parent = new int[size];  //创建双亲数组
    children = new int[size];
    for (int i = 0; i < size; i++) {
        cin >> number[i];
        parent[i] = i;
        children[i] = 1;
    }
    //每个自成单元素集合
};

int UFSets::Find(int Root) {
    //函数搜索并返回包含元素x的树的根。
    while (Root != parent[Root]) {
        parent[Root] = Find(parent[Root]);
        Root = parent[Root];
    }
    return Root;
};

void UFSets::Union(int Root1, int Root2) {
    //求两个不相交集合Root1与Root2的并
    children[Root1] += children[Root2];
    parent[Root2] = Root1;
    //将Root2连接到Root1下面
};

int UFSets::MaxSet() {
    int max = 0;
    for (int i = 0; i < size; i++) {
        //cout << children[i] << ' ';
        if (children[i] > max)
            max = children[i];
    }
    return max;
}

int gcdFriend(int a, int b) {
    if (a >= b) {
        int r = a % b;
        if (r == 0) return b > 1;
        else return gcdFriend(b, r);
    }
    else return gcdFriend(b, a);
}

void UFSets::Merge(int Root1, int Root2) {
    if (Find(Root1) != Find(Root2) && gcdFriend(number[Root1], number[Root2]))
        Union(Find(Root1), Find(Root2));
}

int main()
{
    int n;
    cin >> n;
    UFSets whales(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            whales.Merge(i, j);
        }
    }
    cout << whales.MaxSet();
    return 0;
}