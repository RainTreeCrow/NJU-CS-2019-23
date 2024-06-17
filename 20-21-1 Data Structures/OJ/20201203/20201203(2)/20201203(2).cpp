#include <iostream>
using namespace std;

template <class T>
class Graphmtx {
public:
    int maxVertices;		    //图中最大顶点数
    int numEdges;			    //当前边数
    int numVertices;		    //当前顶点数
    T* VerticesList; 			//顶点表
    bool** Edge;				//邻接矩阵
    int getVertexPos(T vertex) {
        //给出顶点vertex在图中的位置
        for (int i = 0; i < numVertices; i++)
            if (VerticesList[i] == vertex) return i;
        return -1;
    };
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
    T getValue(int i) {
        //取顶点 i 的值, i 不合理返回0
        return i >= 0 && i < numVertices ?
            VerticesList[i] : NULL;
    }
    bool Linked(int v1, int v2) {  //取边(v1,v2)上权值
        return v1 != -1 && v2 != -1 ? Edge[v1][v2] : 0;
    }
    int getFirstNeighbor(int v);
    //取顶点 v 的第一个邻接顶点
    int getNextNeighbor(int v, int w);
    //取 v 的邻接顶点 w 的下一邻接顶点
    bool insertVertex(const T vertex) {
        //if (numVertices >= maxVertices) return false;
        VerticesList[numVertices] = vertex;
        numVertices++;
        return true;
    }
    //插入顶点vertex
    bool insertEdge(int v1, int v2) {
        Edge[v1][v2] = 1;
        Edge[v2][v1] = 1;
        return true;
    }
    //插入边(v1, v2),权值为cost
    bool removeVertex(int v) {
        for (int i = v; i < numVertices - 1; i++) {
            VerticesList[i] = VerticesList[i + 1];
            for (int j = 0; j < numVertices; j++)
                Edge[j][i] = Edge[j][i + 1];
        }
        for (int i = v; i < numVertices - 1; i++) {
            for (int j = 0; j < numVertices; j++)
                Edge[i][j] = Edge[i + 1][j];
        }
        for (int i = 0; i < numVertices; i++) {
            Edge[numVertices - 1][i] = 0;
            Edge[i][numVertices - 1] = 0;
        }
        numVertices--;
    }
    //删去顶点 v 和所有与它相关联的边
    bool removeEdge(int v1, int v2) {
        Edge[v1][v2] = 0;
        Edge[v2][v1] = 0;
    }
    //在图中删去边(v1,v2)
};

template <class T>
Graphmtx<T>::Graphmtx(int sz) {      //构造函数
    maxVertices = sz;
    numVertices = 0;  numEdges = 0;
    int i, j;
    VerticesList = new T[maxVertices];  //创建顶点表
    Edge = new bool* [maxVertices];
    for (i = 0; i < maxVertices; i++)
        Edge[i] = new bool[maxVertices];   //邻接矩阵 
    for (i = 0; i < maxVertices; i++)        //矩阵初始化
        for (j = 0; j < maxVertices; j++)
            Edge[i][j] = (i == j) ? 1 : 0;
};

template <class T>
int Graphmtx<T>::getFirstNeighbor(int v) {
    //给出顶点位置为v的第一个邻接顶点的位置, 
    //如果找不到, 则函数返回-1
    if (v != -1) {
        for (int col = 0; col < numVertices; col++)
            if (Edge[v][col])
                return col;
    }
    return -1;
};

template <class T>
int Graphmtx<T>::getNextNeighbor(int v, int w) {
    //给出顶点 v 的某邻接顶点 w 的下一个邻接顶点 
    if (v != -1 && w != -1) {
        for (int col = w + 1; col < numVertices; col++)
            if (Edge[v][col])
                return col;
    }
    return -1;
};


template<class T>
void DFS_help(Graphmtx<T>& G, int v, bool *& visited, int & temp) {
    //cout << G.getValue(v) << ' ' << temp << endl;        //访问顶点v
    visited[v] = true;	 	         //作访问标记
    int w = G.getFirstNeighbor(v);     //第一个邻接顶点
    temp++;
    while (w != -1) {	//若邻接顶点w存在
        if (!visited[w])
            DFS_help(G, w, visited, temp);
        //若w未访问过, 递归访问顶点w
        w = G.getNextNeighbor(v, w); //下一个邻接顶点
    }
};

template <class T>
int LargestComponent(Graphmtx<T>& G) {
    //通过DFS，找出无向图的所有连通分量
    int i, n = G.NumberOfVertices(); 	//图中顶点个数
    int temp, result = 0;
    bool* visited = new bool[n]; 		//访问标记数组
    for (i = 0; i < n; i++) visited[i] = false;
    for (i = 0; i < n; i++) 			//扫描所有顶点
        if (!visited[i]) {			//若没有访问过
            temp = 0;
            DFS_help(G, i, visited, temp);		//访问
            if (temp > result) result = temp;
            //cout << "--- " << result << " ---" << endl;
        }
    delete[] visited;
    return result;
};

int gcd(int a, int b) {
    if (a >= b) {
        int r = a % b;
        if (r == 0) return b;
        else return gcd(b, r);
    }
    else return gcd(b, a);
}

bool isFriend(int a, int b) {
    //if (gcd(a, b) > 1) cout << a << " & " << b << " are friends" << endl;
    return gcd(a, b) > 1;

}

int main()
{
    int n;
    cin >> n;
    //int* list = new int[n];
    Graphmtx<int> whales(n);
    int whale;
    for (int i = 0; i < n; i++) {
        cin >> whale;
        //list[i] = whale;
        whales.insertVertex(whale);
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (isFriend(whales.getValue(i), whales.getValue(j)))
                whales.insertEdge(i, j);
            //cout << whales.Edge[i][j] << ' ';
        }
        //cout << endl;
    }
    cout << LargestComponent(whales);
    return 0;
}