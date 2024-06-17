#include <iostream>
#include <cmath>
using namespace std;

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

void printRoute(int i, int* list) {
    if (list[i] == -1)
        cout << "->" << i;
    else {
        cout << "->" << i;
        printRoute(list[i], list);
    }
}

void ShortestPath(Graphmtx& G, int c, int v, int sp) {
    //Graph是一个带权有向图。dist[j], 0≤j<n, 是当前
    //求到的从顶点v到顶点j的最短路径长度, path[j],
    //0≤j<n, 存放求到的最短路径。
    int n = G.NumberOfVertices();
    bool* S = new bool[n]; 	   //最短路径顶点集
    int* dist = new int[n];
    int* take = new int[n];
    int* back = new int[n];
    int* path = new int[n];
    int i, j, k;
    int take_sp, back_sp;
    int w, min_dist, min_take, min_back;
    if (G.getValue(sp) > 0) {
        take_sp = -c / 2;
        back_sp = c / 2;
    }
    else {
        take_sp = c / 2;
        back_sp = -c / 2;
    }
    for (i = 0; i < n; i++) {
        dist[i] = G.getWeight(sp, i);
        S[i] = false;
        int temp = G.getValue(i);
        take[i] = take_sp - temp;
        back[i] = back_sp + temp;
        if (i != sp && dist[i] < maxValue)
            path[i] = sp;
        else
            path[i] = -1;
    }
    take[sp] = take_sp; back[sp] = back_sp;
    S[sp] = true;  dist[sp] = 0;     	//顶点v加入顶点集合
    for (i = 0; i < n; i++) {       //求解各顶点最短路径
        min_dist = maxValue;
        min_take = maxValue;
        min_back = maxValue;
        int u = 0; 		//选不在S中具有最短路径的顶点u
        for (j = 0; j < n; j++) {
            if (!S[j]) {
                bool flag = false;
                if (dist[j] < min_dist) flag = true;
                else if (dist[j] == min_dist) {
                    if (take[j] < min_take) flag = true;
                    else if (take[j] == min_take) {
                        if (back[j] < min_back) flag = true;
                    }
                }
                if (flag) {
                    u = j;
                    min_dist = dist[j];
                    min_take = take[j];
                    min_back = back[j];
                }
            }
        }
        S[u] = true;	               	//将顶点u加入集合S
        for (k = 0; k < n; k++) {       	//修改
            w = G.getWeight(u, k);
            int temp = G.getValue(k);
            if (!S[k] && w < maxValue) {       //顶点k未加入S
                bool flag = false;
                if (dist[u] + w < dist[k]) flag = true;
                else if (dist[u] + w == dist[k]) {
                    if (take[u] - temp < take[k]) flag = true;
                    else if (take[u] - temp == take[k])
                        if (back[u] + temp < back[k]) flag = true;
                }
                if (flag) {       //顶点k未加入S                
                    dist[k] = dist[u] + w;
                    path[k] = u;
                    take[k] = take[u] - temp;
                    back[k] = back[u] + temp;
                }
                if (take[k] < 0) take[k] = 0;
                if (back[k] < 0) back[k] = 0;
            }
        }
    }
    //for (int i = 0; i <= dest; i++) cout << path[i] << ' ';
    cout << take[v] << ' ' << v;
    printRoute(path[v], path);
    cout << ' ' << back[v];
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
        places.insertVertex(bikes - cmx / 2);
    }
    int x, t, l;
    for (int i = 0; i < m; i++) {
        cin >> x >> t >> l;
        places.insertEdge(x, t, l);
    }
    ShortestPath(places, cmx, 0, sp);
    return 0;
}