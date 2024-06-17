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
    int getVertexPos(int vertex) {
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
    int getValue(int i) {
        //取顶点 i 的值, i 不合理返回0
        return VerticesList[i];
    }
    int getWeight(int v1, int v2) {  //取边(v1,v2)上权值
        return Edge[v1][v2];
    }
    int getFirstNeighbor(int v);
    //取顶点 v 的第一个邻接顶点
    int getNextNeighbor(int v, int w);
    //取 v 的邻接顶点 w 的下一邻接顶点
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

void printRoute(int i, int* list) {
    if (list[i] == -1)
        cout << i << "->";
    else {
        printRoute(list[i], list);
        cout << i << "->";
    }
}

void ShortestPath(Graphmtx& G, int c, int v, int dest) {
    //Graph是一个带权有向图。dist[j], 0≤j<n, 是当前
    //求到的从顶点v到顶点j的最短路径长度, path[j],
    //0≤j<n, 存放求到的最短路径。
    int n = G.NumberOfVertices();
    bool* S = new bool[n]; 	   //最短路径顶点集
    int* dist = new int[n];
    int* less = new int[n];
    int* more = new int[n];
    int* in = new int[n];
    int* out = new int[n];
    int* path = new int[n];
    int i, j, k;
    int w, min_dist, min_in, min_out;
    for (i = 0; i < n; i++) {
        dist[i] = G.getWeight(v, i);
        S[i] = false;
        int temp = G.getValue(i) - c;
        if (temp >= 0) {
            in[i] = 0;
            less[i] = 0;
            out[i] = temp;
            more[i] = temp;
        }
        else {
            in[i] = -temp;
            less[i] = -temp;
            out[i] = 0;
            more[i] = 0;
        }
        //cout << i << '-' << in[i] << '-' << out[i] << endl;
        if (i != v && dist[i] < maxValue)
            path[i] = v;
        else
            path[i] = -1;
    }
    S[v] = true;  dist[v] = 0;     	//顶点v加入顶点集合
    for (i = 0; i < n; i++) {       //求解各顶点最短路径
        min_dist = maxValue;
        min_in = maxValue;
        min_out = maxValue;
        int u = v; 		//选不在S中具有最短路径的顶点u
        for (j = 0; j < n; j++) {
            if (!S[j]) {
                bool flag = false;
                if (dist[j] < min_dist) flag = true;
                else if (dist[j] == min_dist) {
                    if (in[j] < min_in) flag = true;
                    else if (in[j] == min_in) {
                        if (out[j] < min_out) flag = true;
                    }
                }
                if (flag) {
                    u = j;
                    min_dist = dist[j];
                    min_in = in[j];
                    min_out = out[j];
                }
            }
        }
        S[u] = true;	               	//将顶点u加入集合S
        for (k = 0; k < n; k++) {       	//修改
            w = G.getWeight(u, k);
            if (!S[k] && w < maxValue) {       //顶点k未加入S
                if (dist[u] + w < dist[k]) {
                    dist[k] = dist[u] + w;
                    if (less[k] > 0) {
                        if (out[u] > 0) {
                            int temp = less[k] - out[u];
                            if (temp <= 0) {
                                in[k] = in[u];
                                out[k] = -temp;
                            }
                            else {
                                in[k] = in[u] + temp;
                                out[k] = 0;
                            }
                        }
                    }
                    else {
                        in[k] = in[u];
                        out[k] = more[k] + in[u];
                    }
                    path[k] = u;     		//修改到k的最短路径
                    //cout << u << ' ' << k << '+' << in[k] << '+' << dist[k] << '+' << out[k] << endl;
                }
                else if (dist[u] + w == dist[k]) {
                    int temp_in, temp_out;
                    if (less[k] > 0) {
                        if (out[u] > 0) {
                            int temp = less[k] - out[u];
                            if (temp <= 0) {
                                temp_in = in[u];
                                temp_out = -temp;
                            }
                            else {
                                temp_in = in[u] + temp;
                                temp_out = 0;
                            }
                        }
                    }
                    else {
                        temp_in = in[u];
                        temp_out = more[k] + in[u];
                    }
                    if (temp_in < in[k] || (temp_in == in[k] && temp_out < out[k])) {
                        in[k] = temp_in;
                        out[k] = temp_out;
                        path[k] = u;
                        //cout << u << ' ' << k << '+' << in[k] << '+' << dist[k] << '+' << out[k] << endl;
                    }
                }
            }
        }
    }
    //for (int i = 0; i <= dest; i++) cout << path[i] << ' ';
    cout << in[dest] << ' ';
    printRoute(path[dest], path);
    cout << dest << ' ' << out[dest];
};

int main()
{
    int cmx, n, sp, m;
    cin >> cmx >> n >> sp >> m;
    Graphmtx places(n + 1);
    int bikes;
    places.insertVertex(cmx / 2);
    for (int i = 0; i < n; i++) {
        cin >> bikes;
        places.insertVertex(bikes);
    }
    int x, t, l;
    for (int i = 0; i < m; i++) {
        cin >> x >> t >> l;
        places.insertEdge(x, t, l);
    }
    ShortestPath(places, cmx / 2, 0, sp);
    return 0;
}