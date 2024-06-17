#include <iostream>
#include <cmath>
#include <string>
using namespace std;
#pragma warning (disable:4996)

#define maxValue 10000000000

class Graphmtx {
private:
    int maxVertices;		    //图中最大顶点数
    int numEdges;			    //当前边数
    int numVertices;		    //当前顶点数
    int* VerticesList; 			//顶点表
    int** Edge;				//邻接矩阵
public:
    Graphmtx(int sz);    //构造函数
    ~Graphmtx() {				      //析构函数
        delete[]VerticesList;
        for (int i = 0; i < maxVertices; i++)
            delete[] Edge[i];
        delete[] Edge;
    }
    int NumberOfVertices() { return numVertices; }
    int NumberOfEdges() { return numEdges; }
    int getValue(int i) {
        //取顶点 i 的值, i 不合理返回0
        return VerticesList[i];
    }
    int getWeight(int v1, int v2) {  //取边(v1,v2)上权值
        return Edge[v1][v2];
    }
    int insertVertex(const int vertex) {
        //if (numVertices >= maxVertices) return false;
        VerticesList[numVertices] = vertex;
        numVertices++;
        return numVertices - 1;
    }
    //插入顶点vertex
    void insertEdge(int v1, int v2, int cost) {
        Edge[v1][v2] = cost;
        Edge[v2][v1] = cost;
    }
    //插入边(v1, v2),权值为cost
};

Graphmtx::Graphmtx(int sz) {      //构造函数
    maxVertices = sz;
    numVertices = 0;  numEdges = 0;
    int i, j;
    VerticesList = new int[maxVertices];  //创建顶点表
    Edge = new int* [maxVertices];
    for (i = 0; i < maxVertices; i++)
        Edge[i] = new int[maxVertices];   //邻接矩阵 
    for (i = 0; i < maxVertices; i++)        //矩阵初始化
        for (j = 0; j < maxVertices; j++)
            Edge[i][j] = (i == j) ? 0 : maxValue;
};

void select(Graphmtx& G, int c, int v, int sp, int take, int back,
    int& min_take, int& min_back, int*& count, int**& path, string process, string& result) {
    int temp;
    if (v != 0)
        temp = back + G.getValue(v) - c / 2;
    else
        temp = back + G.getValue(v);
    if (temp >= 0)
        back = temp;
    else {
        take -= temp;
        back = 0;
    }
    if (v == sp) {
        if (take < min_take) {
            min_take = take;
            min_back = back;
            result = process;
        }
        else if (take == min_take && back < min_back) {
            min_back = back;
            result = process;
        }
        return;
    }
    for (int i = 0; i < count[v]; i++) {
        select(G, c, path[v][i], sp, take, back, min_take, min_back,
            count, path, process + "->" + to_string(path[v][i]), result);
    }
}

void ShortestPath(Graphmtx& G, int c, int v, int sp) {
    //Graph是一个带权有向图。dist[j], 0≤j<n, 是当前
    //求到的从顶点v到顶点j的最短路径长度, path[j],
    //0≤j<n, 存放求到的最短路径。
    int n = G.NumberOfVertices();
    bool* S = new bool[n]; 	   //最短路径顶点集
    int* dist = new int[n];
    int* count = new int[n];
    int** path = new int* [n];
    int i, j, k;
    int w, min_dist, min_take, min_back;
    for (i = 0; i < n; i++) {
        path[i] = new int[n];
        dist[i] = G.getWeight(sp, i);
        S[i] = false;
        path[i][0] = sp;
        if (i != sp && dist[i] < maxValue)
            count[i] = 1;
        else
            count[i] = 0;
    }

    S[sp] = true;  dist[sp] = 0;     	//顶点v加入顶点集合
    for (i = 0; i < n; i++) {       //求解各顶点最短路径
        min_dist = maxValue;
        int u = 0; 		//选不在S中具有最短路径的顶点u
        for (j = 0; j < n; j++) {
            if (!S[j]) {
                if (dist[j] < min_dist) {
                    u = j;
                    min_dist = dist[j];
                }
            }
        }
        S[u] = true;	               	//将顶点u加入集合S
        for (k = 0; k < n; k++) {       	//修改
            w = G.getWeight(u, k);
            int temp = G.getValue(k);
            if (k == u) continue;
            if (w < maxValue) {       //顶点k未加入S
                if (dist[u] + w < dist[k]) {
                    dist[k] = dist[u] + w;
                    path[k][0] = u;
                    count[k] = 1;
                }
                else if (dist[u] + w == dist[k]) {
                    path[k][count[k]] = u;
                    count[k]++;
                }
            }
        }
    }

    min_take = maxValue, min_back = maxValue;
    string result;
    string process = "0";
    select(G, c, v, sp, 0, 0, min_take, min_back, count, path, process, result);
    cout << min_take << ' ' << result << ' ' << min_back;
};

int main()
{
    int cmx, n, sp, m;
    cin >> cmx >> n >> sp >> m;
    Graphmtx places(n + 1);
    int bikes;
    places.insertVertex(0);
    for (int i = 0; i < n; i++) {
        cin >> bikes;
        places.insertVertex(bikes);
    }
    int x, t, l;
    for (int i = 0; i < m; i++) {
        cin >> x >> t >> l;
        places.insertEdge(x, t, l);
    }
    ShortestPath(places, cmx, 0, sp);
    return 0;
}