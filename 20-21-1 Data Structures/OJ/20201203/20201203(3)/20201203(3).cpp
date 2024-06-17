#include <iostream>
using namespace std;

class UFSets {	//集合中的各个子集合互不相交
public:
    UFSets(int sz);	//构造函数
    ~UFSets() { delete[]parent; }	    //析构函数
    int Find(int x);				    //查找x的根
    void Union(int Root1, int Root2);   //合并算法
    int CountSets();
    bool* label;
private:
    int* parent;		  //集合元素数组(双亲表示)
    int size;			  //集合元素的数目
};

UFSets::UFSets(int sz) {
    //构造函数：sz 是集合元素个数，双亲数组的范围
    //为parent[0]～parent[size-1]。
    size = sz;			  //集合元素个数
    label = new bool[size];
    parent = new int[size];  //创建双亲数组
    for (int i = 0; i < size; i++) {
        label[i] = false;
        parent[i] = i;
    }
    //每个自成单元素集合
};

int UFSets::Find(int x) {
    //函数搜索并返回包含元素x的树的根。
    while (x != parent[x]) {
        parent[x] = Find(parent[x]);
        x = parent[x];
    }
    return x;
};

void UFSets::Union(int Root1, int Root2) {
    parent[Root2] = Root1;
}

int UFSets::CountSets() {
    int result = 0;
    for (int i = 0; i < size; i++) {
        if (label[i] && parent[i] == i)
            result++;
    }
    return result;
}

int main()
{
    int row, col, temp, addr;
    cin >> row >> col;
    bool** matrix = new bool* [row];
    UFSets stars(row * col);
    for (int i = 0; i < row; i++) {
        matrix[i] = new bool[col];
        for (int j = 0; j < col; j++) {
            cin >> temp;
            matrix[i][j] = temp;
            if (temp) {
                addr = i * col + j;
                stars.label[addr] = true;
                if (i > 0 && matrix[i - 1][j])
                    stars.Union(stars.Find(addr), stars.Find(addr - col));
                if (j > 0 && matrix[i][j - 1])
                    stars.Union(stars.Find(addr), stars.Find(addr - 1));
            }
        }
    }
    cout << stars.CountSets();
    return 0;
}