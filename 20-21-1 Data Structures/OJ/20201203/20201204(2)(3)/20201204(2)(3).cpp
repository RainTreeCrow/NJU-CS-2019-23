#include <iostream>
#include <cmath>
using namespace std;

#define max_n 1000000
bool is_prime[max_n + 1];
int prime[max_n / 10];
int count_prime;

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
    //bool* exist;
    int* parent;		  //集合元素数组(双亲表示)
    int* children;
    int size;			  //集合元素的数目
};

UFSets::UFSets(int sz) {
    //构造函数：sz 是集合元素个数，双亲数组的范围
    //为parent[0]～parent[size-1]。
    size = sz;			  //集合元素个数
    parent = new int[size];  //创建双亲数组
    children = new int[size];
    for (int i = 0; i < size; i++) {
        parent[i] = i;
        children[i] = 0;
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

void UFSets::Merge(int Root1, int Root2) {
    if (Find(Root1) != Find(Root2))
        Union(Find(Root1), Find(Root2));
}

int main()
{
    for (int i = 0; i <= max_n; i++)
        is_prime[i] = true;
    is_prime[1] = false;
    count_prime = 0;
    for (int i = 2; i <= max_n; i++) {
        if (is_prime[i]) {
            prime[count_prime++] = i;
            for (int j = i * 2; j <= max_n; j += i)
                is_prime[j] = false;
        }
        //cout << i << ' ' << is_prime[i] << endl;
    }
    //cout << count_prime << endl;
    int n, whale, temp_whale, temp_part, count_part;
    cin >> n;
    UFSets whales(max_n);
    int* list = new int[n];
    int* temp = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> whale;
        list[i] = whale;
        whales.children[whale] = 1;
    }
    for (int i = 0; i < n; i++) {
        whale = list[i];
        temp_whale = whale;
        if (is_prime[whale])
            continue;
        else {
            count_part = 0;
            for (int j = 0; prime[j] <= sqrt(whale); j++) {
                temp_part = prime[j];
                if (whale % temp_part == 0) {
                    temp[count_part++] = prime[j];
                    //cout << temp_whale << " has: " << prime[j] << endl;
                    while (whale % temp_part == 0) {
                        whale /= temp_part;
                    }
                    if (is_prime[whale]) {
                        temp[count_part++] = whale;
                        //cout << temp_whale << " has: " << whale << endl;
                        break;
                    }
                }
            }
            for (int k = 0; k < count_part; k++) {
                //cout << "merge " << temp_whale << " & " << temp[k] << endl;
                whales.Merge(temp[k], temp_whale);
            }
        }
    }
    cout << whales.MaxSet();
}