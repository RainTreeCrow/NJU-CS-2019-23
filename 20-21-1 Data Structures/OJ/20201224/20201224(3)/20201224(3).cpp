#include <iostream>
using namespace std;

#define maxValue 10000000

class Graphmtx {
private:
    int numEdges;			    //当前边数
    int numVertices;		    //当前顶点数
    int* Level;
    int** Cost;				//邻接矩阵
public:
    Graphmtx(int sz);    //构造函数
    ~Graphmtx() {				      //析构函数
        delete[] Level;
        for (int i = 0; i < numVertices; i++)
            delete[] Cost[i];
        delete[] Cost;
    }
    int NumberOfVertices() { return numVertices; }
    int NumberOfEdges() { return numEdges; }
    int getLevel(int v) {
        return Level[v];
    }
    int getCost(int v1, int v2) {  //取边(v1,v2)上权值
        return Cost[v1][v2];
    }
    void insertObject(int v, int level) {
        Level[v] = level;
    }
    void insertTrade(int v1, int v2, int cost) {
        Cost[v1][v2] = cost;
    }
};

Graphmtx::Graphmtx(int sz) {      //构造函数
    numVertices = sz;  numEdges = 0;
    int i, j;
    Level = new int[numVertices];
    Cost = new int* [numVertices];
    for (i = 0; i < numVertices; i++) {
        Cost[i] = new int[numVertices];   //邻接矩阵
        for (j = 0; j < numVertices; j++)
            Cost[i][j] = maxValue;
    }
    for (i = 0; i < numVertices; i++)
        Cost[i][i] = 0;
};

void ShortestPath(Graphmtx& G, int dif, int v, int p, int& minCost) {
    //Graph是一个带权有向图。dist[j], 0≤j<n, 是当前
    //求到的从顶点v到顶点j的最短路径长度, path[j],
    //0≤j<n, 存放求到的最短路径。
    int n = G.NumberOfVertices();
    bool* S = new bool[n]; 	   //最短路径顶点集
    int* dist = new int[n];
    int i, j, k;
    int w, min;
    int maxLevel = G.getLevel(v);
    for (i = 1; i < n; i++) {
        dist[i] = G.getCost(0, i);
        if (G.getLevel(i) > maxLevel || maxLevel - G.getLevel(i) > dif)
            S[i] = true;
        else
            S[i] = false;
    }
    for (i = 1; i < n; i++) {       //求解各顶点最短路径
        min = maxValue;  int u = 0; 		//选不在S中具有最短路径的顶点u
        for (j = 1; j < n; j++) {
            if (!S[j] && dist[j] < min) {
                u = j;
                min = dist[j];
            }
        }
        if (u == 0) break;
        S[u] = true;	               	//将顶点u加入集合S
        for (k = 1; k < n; k++) {       	//修改
            w = G.getCost(u, k);
            if (!S[k] && dist[u] + w < dist[k]) {       //顶点k未加入S                
                dist[k] = dist[u] + w;
            }
        }
    }
    //cout << dist[p] << endl;
    if (dist[p] < minCost)
        minCost = dist[p];
};

int main()
{
    int M, N;
    cin >> M >> N;
    Graphmtx Objects(N + 1);
    int P, L, X, T, V;
    for (int i = 1; i <= N; i++) {
        cin >> P >> L >> X;
        Objects.insertObject(i, L);
        Objects.insertTrade(0, i, P);
        for (int j = 0; j < X; j++) {
            cin >> T >> V;
            Objects.insertTrade(T, i, V);
        }
    }
    int minCost = maxValue;
    for (int i = 1; i <= N; i++) {
        ShortestPath(Objects, M, i, 1, minCost);
    }
    cout << minCost;
    return 0;
}