#include <iostream>
#include <cmath>
using namespace std;

#define maxValue 10000000000

struct dot{
    int x;
    int y;
    dot() {
        x = -1; y = -1;
    }
    dot(int a, int b) {
        x = a;  y = b;
    }
    bool operator==(dot d) {
        return (x == d.x) && (y == d.y);
    }
};

class Graphmtx {
private:
    int maxVertices;		    //图中最大顶点数
    int numEdges;			    //当前边数
    int numVertices;		    //当前顶点数
    dot* VerticesList; 			//顶点表
    int** Edge;				//邻接矩阵
    int getVertexPos(dot vertex) {
        //给出顶点vertex在图中的位置
        for (int i = 0; i < numVertices; i++)
            if (VerticesList[i] == vertex) return i;
        return -1;
    }
public:
    Graphmtx(int sz);    //构造函数
    ~Graphmtx() {				      //析构函数
        delete[]VerticesList;
        for (int i = 0; i < maxVertices; i++)
            delete[] Edge[i];
        delete[] Edge;
    }
    bool GraphEmpty() const {		//判图空否
        return numEdges == 0;
    }
    int NumberOfVertices() { return numVertices; }
    int NumberOfEdges() { return numEdges; }
    dot getValue(int i) {
        //取顶点 i 的值, i 不合理返回0
        return VerticesList[i];
    }
    int getWeight(int v1, int v2) {  //取边(v1,v2)上权值
        if (Edge[v1][v2] > 0)
            return Edge[v1][v2];
        else
            return abs(VerticesList[v1].x - VerticesList[v2].x)
            + abs(VerticesList[v1].y - VerticesList[v2].y);
    }
    int getFirstNeighbor(int v);
    //取顶点 v 的第一个邻接顶点
    int getNextNeighbor(int v, int w);
    //取 v 的邻接顶点 w 的下一邻接顶点
    int insertVertex(const dot vertex) {
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
    VerticesList = new dot[maxVertices];  //创建顶点表
    Edge = new int* [maxVertices];
    for (i = 0; i < maxVertices; i++)
        Edge[i] = new int[maxVertices];   //邻接矩阵 
    for (i = 0; i < maxVertices; i++)        //矩阵初始化
        for (j = 0; j < maxVertices; j++)
            Edge[i][j] = (i == j) ? 0 : -1;
};

int Graphmtx::getFirstNeighbor(int v) {
    //给出顶点位置为v的第一个邻接顶点的位置, 
    //如果找不到, 则函数返回-1
    if (v != -1) {
        for (int col = 0; col < numVertices; col++)
            if (Edge[v][col] > 0)
                return col;
    }
    return -1;
};

int Graphmtx::getNextNeighbor(int v, int w) {
    //给出顶点 v 的某邻接顶点 w 的下一个邻接顶点 
    if (v != -1 && w != -1) {
        for (int col = w + 1; col < numVertices; col++)
            if (Edge[v][col] > 0)
                return col;
    }
    return -1;
};

void ShortestPath(Graphmtx& G, int v) {
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
        if (i != v && dist[i] < maxValue)
            path[i] = v;
        else
            path[i] = -1;
    }
    S[v] = true;  dist[v] = 0;     	//顶点v加入顶点集合
    for (i = 0; i < n - 1; i++) {       //求解各顶点最短路径
        min = maxValue;
        int u = v; 		//选不在S中具有最短路径的顶点u
        for (j = 0; j < n; j++) {
            if (!S[j] && dist[j] < min) {
                u = j;
                min = dist[j];
            }
        }
        S[u] = true;	               	//将顶点u加入集合S
        for (k = 0; k < n; k++) {       	//修改
            w = G.getWeight(u, k);
            if (!S[k] && w < maxValue && dist[u] + w < dist[k]) {       //顶点k未加入S                
                dist[k] = dist[u] + w;
                path[k] = u;     		//修改到k的最短路径
            }
        }
    }
    cout << dist[1];
};

int main()
{
    int n, xMe, yMe, xHome, yHome;
    cin >> n;
    Graphmtx places(1000);
    cin >> xMe >> yMe >> xHome >> yHome;
    int Me = places.insertVertex(dot(xMe, yMe));
    int Home = places.insertVertex(dot(xHome, yHome));
    int xs, ys, xt, yt, x, t;
    for (int i = 0; i < n; i++) {
        cin >> xs >> ys >> xt >> yt;
        x = places.insertVertex(dot(xs, ys));
        t = places.insertVertex(dot(xt, yt));
        places.insertEdge(x, t, 10);
    }
    ShortestPath(places, 0);
    return 0;
}