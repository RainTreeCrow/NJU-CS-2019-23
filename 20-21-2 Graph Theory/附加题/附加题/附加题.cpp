#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

#define MAX_NUM 1000000

int X;
int Y;
vector<int>V;
vector<int>G[MAX_NUM];
int match[MAX_NUM];
int weight[MAX_NUM];
bool checked[MAX_NUM];
int Temp_Weight = 0;

bool DFS_Search(int u) {
    vector<int>::iterator iter;
    for (iter = G[u].begin(); iter != G[u].end(); ++iter) {
        int v = *iter;
        //cout << "Judging " << u << " and " << v << endl;
        if (!checked[v]) {
            checked[v] = true;
            int w = match[v];
            if (w == -1 || DFS_Search(w)) {
                match[v] = u;
                match[u] = v;
                //cout << "Matching " << u << " to " << v << endl;
                return true;
            }
        }
    }
    return false;
}

void Biggest_Match() {
    Temp_Weight = 0;
    memset(match, -1, sizeof(match));
    vector<int>::iterator iter;
    for (iter = V.begin(); iter != V.end(); ++iter) {
        int u = *iter;
        if (match[u] == -1) {
            memset(checked, 0, sizeof(checked));
            if (DFS_Search(u));
        }
    }
    for (int u = 1; u <= X; u++) {
        int v = match[u];
        if (v != -1) {
            Temp_Weight += weight[u];
            Temp_Weight += weight[v];
        }
    }
}

bool compare(int u, int v) {
    return weight[u] > weight[v];
}

int main()
{
    memset(weight, 0, sizeof(weight));
    cin >> X >> Y;
    int edge_num;
    int temp_from, temp_to;
    for (int i = 1; i <= X; i++) {
        V.push_back(i);
        temp_from = i;
        cin >> weight[i];
        cin >> edge_num;
        for (int j = 0; j < edge_num; j++) {
            cin >> temp_to;
            temp_to += X;
            G[temp_from].push_back(temp_to);
            G[temp_to].push_back(temp_from);
        }
    }
    sort(V.begin(), V.end(), compare);
    Biggest_Match();
    cout << Temp_Weight;
    return 0;
}