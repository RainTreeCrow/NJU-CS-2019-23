#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

#define MAX_NUM 1000000

int X;
int Y;
vector<int>G[MAX_NUM];
int match[MAX_NUM];
bool checked[MAX_NUM];

bool DFS_Search(int u) {
    //cout << "Searching " << u << endl;
    vector<int>::iterator iter;
    for (iter = G[u].begin(); iter != G[u].end(); ++iter) {
        //遍历所有的邻接顶点
        int v = *iter;
        //cout << "Judging " << u << " and " << v << endl;
        if (!checked[v]) {
            checked[v] = true;
            if (match[v] == -1 || DFS_Search(match[v])) {
                //邻接顶点v未匹配或能替换成v以外的其他匹配
                //递归完成替换（增广）并将v和u匹配
                match[v] = u;
                match[u] = v;
                //cout << "Matching " << u << " to " << v << endl;
                return true;
            }
        }
    }
    //寻找增广路失败
    return false;
}

int Biggest_Match() {
    int count = 0;
    memset(match, -1, sizeof(match));
    for (int u = 1; u <= X; u++) {
        //遍历单侧的顶点即可
        if (match[u] == -1) {
            memset(checked, 0, sizeof(checked));
            checked[u] = true;
            if (DFS_Search(u))
                //如果搜索成功则u被匹配
                count++;
        }
    }
    return count;
}

int main()
{
    cin >> X >> Y;
    int edge_num;
    int temp_from, temp_to;
    for (int i = 1; i <= X; i++) {
        temp_from = i;
        cin >> edge_num;
        for (int j = 0; j < edge_num; j++) {
            cin >> temp_to;
            temp_to += X;
            G[temp_from].push_back(temp_to);
            //G[temp_to].push_back(temp_from);
        }
    }
    int res = Biggest_Match();
    cout << res;
    //for (int i = 1; i <= X; i++)
        //cout << "Match: " << i << ' ' << match[i] << endl;
    return 0;
}