#include <iostream>
using namespace std;

class UFSets {	//集合中的各个子集合互不相交
public:
    UFSets(int sz);	//构造函数
    ~UFSets() { delete[]parent; }	//析构函数
    //UFSets& operator = (UFSets& R);    //集合赋值
    void Union(int Root1, int Root2);	     //子集合并
    int Find(int x);				//查找x的根
    void WeightedUnion(int Root1, int Root2);
    void UnionByHeight(int Root1, int Root2);
    //改进例程:压缩高度的合并算法
    int CountSets();
private:
    int* parent;		  //集合元素数组(双亲表示)
    int size;			  //集合元素的数目
};

UFSets::UFSets(int sz) {
    //构造函数：sz 是集合元素个数，双亲数组的范围
    //为parent[0]～parent[size-1]。
    size = sz;			  //集合元素个数
    parent = new int[size];  //创建双亲数组
    for (int i = 0; i < size; i++) parent[i] = -1;
    //每个自成单元素集合
};

int UFSets::Find(int x) {
    //函数搜索并返回包含元素x的树的根。
    if (parent[x] < 0) return x;   //根的parent[]值小于0  
    else return (Find(parent[x]));
};

void UFSets::Union(int Root1, int Root2) {
    //求两个不相交集合Root1与Root2的并
    parent[Root1] += parent[Root2];
    parent[Root2] = Root1;
    //将Root2连接到Root1下面
};

void UFSets::WeightedUnion(int Root1, int Root2) {
    //按Union的加权规则改进的算法
    int temp = parent[Root1] + parent[Root2];
    if (parent[Root2] < parent[Root1]) {
        parent[Root1] = Root2;     //Root2中结点数多
        parent[Root2] = temp;      //Root1指向Root2
    }
    else {
        parent[Root2] = Root1;    //Root1中结点数多
        parent[Root1] = temp;      //Root2指向Root1
    }
};

void UFSets::UnionByHeight(int Root1, int Root2) {
    if (Find(Root1) != Find(Root2)) {
        parent[Root1] += parent[Root2];
        for (int i = 0; i < size; i++) {
            if (Find(i) == Root2)
                parent[i] = Root1;
        }
    }
}

int UFSets::CountSets() {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (parent[i] < 0)
            count++;
    }
    return count;
}

int main()
{
    int buildings, roads;
    cin >> buildings >> roads;
    UFSets HOUSES(buildings);
    int link1, link2;
    for (int i = 0; i < roads; i++) {
        cin >> link1 >> link2;
        HOUSES.UnionByHeight(HOUSES.Find(link1 - 1), HOUSES.Find(link2 - 1));
    }
    cout << HOUSES.CountSets() - 1;
    return 0;
}