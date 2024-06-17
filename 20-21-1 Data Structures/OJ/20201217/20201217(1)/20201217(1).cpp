#include <iostream>
using namespace std;

class Graphmtx {
private:
    int numEdges;			    //当前边数
    int numVertices;		    //当前顶点数
    bool** Edge;				//邻接矩阵
    int* Pos;
public:
    Graphmtx(int sz);    //构造函数
    ~Graphmtx() {				      //析构函数
        delete[] Pos;
        for (int i = 0; i < numVertices; i++)
            delete[] Edge[i];
        delete[] Edge;
    }
    bool GraphEmpty() const {		//判图空否
        return numEdges == 0;
    }
    int NumberOfVertices() { return numVertices; }
    int NumberOfEdges() { return numEdges; }
    bool isLinked(int v1, int v2) {  //取边(v1,v2)上权值
        return Edge[v1][v2];
    }
    int getFirstNeighbor(int v);
    //取顶点 v 的第一个邻接顶点
    int getNextNeighbor(int v, int w);
    //取 v 的邻接顶点 w 的下一邻接顶点
    void insertEdge(int v1, int v2) {
        Edge[v1][v2] = true;
        Edge[v2][v1] = true;
    }
    //插入边(v1, v2)
    bool JudgeOK(int v, int pos) {
        Pos[v] = pos;
        int neighbor = getFirstNeighbor(v);
        while (neighbor != -1) {
            if (Pos[neighbor] == pos)
                return false;
            else if (Pos[neighbor] == 0) {
                if (!JudgeOK(neighbor, -pos))
                    return false;
            }
            neighbor = getNextNeighbor(v, neighbor);
        }
        return true;

    }

    void Group() {
        for (int i = 0; i < numVertices; i++) {
            if (Pos[i] == 0 && !JudgeOK(i, 1)) {
                cout << "No";
                return;
            }
        }
        cout << "Yes";
    }
};

Graphmtx::Graphmtx(int sz) {      //构造函数
    numVertices = sz;  numEdges = 0;
    int i, j;
    Pos = new int[numVertices];
    Edge = new bool* [numVertices];
    for (i = 0; i < numVertices; i++) {
        Pos[i] = 0;
        Edge[i] = new bool[numVertices];   //邻接矩阵 
    }
    for (i = 0; i < numVertices; i++)        //矩阵初始化
        for (j = 0; j < numVertices; j++)
            Edge[i][j] = false;
};

int Graphmtx::getFirstNeighbor(int v) {
    //给出顶点位置为v的第一个邻接顶点的位置, 
    //如果找不到, 则函数返回-1
    if (v != -1) {
        for (int col = 0; col < numVertices; col++)
            if (Edge[v][col])
                return col;
    }
    return -1;
};

int Graphmtx::getNextNeighbor(int v, int w) {
    //给出顶点 v 的某邻接顶点 w 的下一个邻接顶点 
    if (v != -1 && w != -1) {
        for (int col = w + 1; col < numVertices; col++)
            if (Edge[v][col])
                return col;
    }
    return -1;
};

int main()
{
    int m, n;
    cin >> n >> m;
    Graphmtx players(n);
    int temp1, temp2;
    for (int i = 0; i < m; i++) {
        cin >> temp1 >> temp2;
        players.insertEdge(temp1, temp2);
    }
    players.Group();
    return 0;
}