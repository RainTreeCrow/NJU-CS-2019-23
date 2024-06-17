#include <iostream>
#include <cmath>
using namespace std;

class UFSets {	//集合中的各个子集合互不相交
public:
    UFSets(int sz);	//构造函数
    ~UFSets() { 	//析构函数
        delete[]exits;
        delete[]parent;
        delete[]children;
    }
    void Union(int Root1, int Root2);	     //子集合并
    int Find(int x);				//查找x的根
    void Merge(int Node1, int Node2);
    int* exits;
    int* parent;		  //集合元素数组(双亲表示)
    int* children;
    int size;			  //集合元素的数目
};

UFSets::UFSets(int sz) {
    //构造函数：sz 是集合元素个数，双亲数组的范围
    //为parent[0]～parent[size-1]。
    size = sz;			  //集合元素个数
    exits = new int[size];
    parent = new int[size];  //创建双亲数组
    children = new int[size];
    for (int i = 0; i < size; i++) {
        exits[i] = 0;
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

void UFSets::Merge(int Node1, int Node2) {
    if (Find(Node1) != Find(Node2))
        Union(Find(Node1), Find(Node2));
}

int main()
{
    int m, n, k;
    cin >> m >> n >> k;
    UFSets holes(m);
    int x, y;
    for (int i = 0; i < k; i++) {
        cin >> x >> y;
        holes.Merge(x, y);
    }
    int index, parent, count, max_count = 0, max_index = m;
    int* left = new int[n];
    int* find = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> index;
        left[i] = index;
        parent = holes.Find(index);
        find[i] = parent;
        holes.exits[parent] += 1;
    }
    for (int i = 0; i < n; i++) {
        parent = find[i];
        if (holes.exits[parent] == 1) {
            count = holes.children[parent];
            if (count > max_count) {
                max_count = count;
                max_index = left[i];
            }
            else if (count == max_count && left[i] < max_index)
                max_index = left[i];
        }
    }
    if (max_index == m) {
        for (int i = 0; i < n; i++) {
            if (left[i] < max_index)
                max_index = left[i];
        }
    }
    cout << max_index;
    return 0;
}