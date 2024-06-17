#include <iostream>
using namespace std;

#define maxValue 10000000

class Graphmtx {
private:
    int numEdges;			    //当前边数
    int numVertices;		    //当前顶点数
    int** Edge;				//邻接矩阵
public:
    Graphmtx(int sz);    //构造函数
    ~Graphmtx() {				      //析构函数
        for (int i = 0; i < numVertices; i++)
            delete[] Edge[i];
        delete[] Edge;
    }
    bool GraphEmpty() const {		//判图空否
        return numEdges == 0;
    }
    int NumberOfVertices() { return numVertices; }
    int NumberOfEdges() { return numEdges; }
    int getWeight(int v1, int v2) {  //取边(v1,v2)上权值
        return Edge[v1][v2];
    }
    void insertRouteWithDemon(int v1, int v2) {
        Edge[v1][v2] = 1;
    }
    void insertRouteWithoutDemon(int v1, int v2) {
        Edge[v1][v2] = 0;
    }
};

Graphmtx::Graphmtx(int sz) {      //构造函数
    numVertices = sz;  numEdges = 0;
    int i, j;
    Edge = new int* [numVertices];
    for (i = 0; i < numVertices; i++) {
        Edge[i] = new int[numVertices];   //邻接矩阵
        for (j = 0; j < numVertices; j++)
            Edge[i][j] = maxValue;
    }
    for (i = 0; i < numVertices; i++)        //矩阵初始化
        Edge[i][i] = 0;
};

void ShortestPath(Graphmtx& G, int v, int p) {
    //Graph是一个带权有向图。dist[j], 0≤j<n, 是当前
    //求到的从顶点v到顶点j的最短路径长度, path[j],
    //0≤j<n, 存放求到的最短路径。
    int n = G.NumberOfVertices();
    bool* S = new bool[n]; 	   //最短路径顶点集
    int* dist = new int[n];
    int* path = new int[n];
    int i, j, k;
    int w, min;
    for (i = 0; i < n; i++) {
        dist[i] = G.getWeight(v, i);
        S[i] = false;
        if (i != v)
            path[i] = v;
        else
            path[i] = -1;
    }
    S[v] = true;  dist[v] = 0;     	//顶点v加入顶点集合
    for (i = 0; i < n - 1; i++) {       //求解各顶点最短路径
        min = maxValue;  int u = v; 		//选不在S中具有最短路径的顶点u
        for (j = 0; j < n; j++) {
            if (!S[j] && dist[j] < min) {
                u = j;
                min = dist[j];
            }
        }
        S[u] = true;	               	//将顶点u加入集合S
        for (k = 0; k < n; k++) {       	//修改
            w = G.getWeight(u, k);
            if (!S[k] && dist[u] + w < dist[k]) {       //顶点k未加入S                
                dist[k] = dist[u] + w;
                path[k] = u;     		//修改到k的最短路径
            }
        }
    }
    if (dist[p] < maxValue)
        cout << dist[p];
    else
        cout << -1;
};

int main()
{
    int N, A, B;
    cin >> N >> A >> B;
    Graphmtx places(N);
    int count, temp;
    for (int i = 0; i < N; i++) {
        cin >> count;
        if (count >= 1) cin >> temp;
        places.insertRouteWithoutDemon(i, temp - 1);
        for (int j = 1; j < count; j++) {
            cin >> temp;
            places.insertRouteWithDemon(i, temp - 1);
        }
    }
    ShortestPath(places, A - 1, B - 1);
    return 0;
}