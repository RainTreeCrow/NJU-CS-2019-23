#include <iostream>
using namespace std;

struct Line {
    int left;
    int right;
    long long int length;
    Line() {
        left = -1; right = -1; length = -1;
    }
    Line(int l, int r, long long int len) {
        left = l; right = r; length = len;
    }
};

void QuickSort(Line* list, int left, int right)
{
    if (left >= right) return;
    int i = left;
    int j = right;
    Line key = list[left];
    while (i < j) {
        while (i < j && key.length <= list[j].length) j--;
        list[i] = list[j];
        while (i < j && key.length >= list[i].length) i++;
        list[j] = list[i];
    }
    list[i] = key;
    QuickSort(list, left, i - 1);
    QuickSort(list, i + 1, right);
}

class UFSets {	//集合中的各个子集合互不相交
public:
    UFSets(int sz);	//构造函数
    ~UFSets() { delete[]parent; }	    //析构函数
    int Find(int x);				    //查找x的根
    void Union(int Root1, int Root2);   //合并算法
private:
    int* parent;		  //集合元素数组(双亲表示)
    int size;			  //集合元素的数目
};

UFSets::UFSets(int sz) {
    //构造函数：sz 是集合元素个数，双亲数组的范围
    //为parent[0]～parent[size-1]。
    size = sz;			  //集合元素个数
    parent = new int[size];  //创建双亲数组
    for (int i = 0; i < size; i++) parent[i] = i;
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

int main()
{
    int n, m;
    int left, right, length;
    cin >> n >> m;
    UFSets dots(1000000);
    Line* lines = new Line[m];
    for (int i = 0; i < m; i++) {
        cin >> left >> right >> length;
        lines[i] = Line(left, right, length);
    }
    QuickSort(lines, 0, m - 1);
    int roads = 0;
    int templ, findl, tempr, findr;
    long long int total = 0;
    for (int i = 0; i < m; i++) {
        templ = lines[i].left;
        tempr = lines[i].right;
        findl = dots.Find(templ);
        findr = dots.Find(tempr);
        if (findl != findr) {
            dots.Union(findl, findr);
            roads++;
            total += lines[i].length;
            //cout << templ << ' ' << tempr << ' ' << total << endl;
        }
        if (roads == n - 1) break;
    }
    cout << total;
    return 0;
}