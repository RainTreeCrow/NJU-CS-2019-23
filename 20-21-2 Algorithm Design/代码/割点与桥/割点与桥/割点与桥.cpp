#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

enum Color { white, grey, black };
int globalTime = 0;

class Vertex {
private:
    int repr;
    Color colour;
    int discoverTime;
    int back;
    int parent;
public:
    vector<int> neighbours;
    Vertex() {
        repr = -1;
        colour = white;
        discoverTime = -1;
        back = -1;
        parent = -1;
    }
    Vertex(int v) {
        repr = v;
        colour = white;
        discoverTime = -1;
        back = -1;
        parent = -1;
    }
    void addNeighbour(int w) {
        neighbours.push_back(w);
    }
    bool isWhite() {
        return colour == white;
    }
    void colorGrey() {
        colour = grey;
    }
    void colorBlack() {
        colour = black;
    }
    void setDiscoveTime(int t) {
        discoverTime = t;
    }
    void setBack(int t) {
        back = t;
    }
    int getDiscoverTime() {
        return discoverTime;
    }
    int getBack() {
        return back;
    }
    void setParent(int u) {
        parent = u;
    }
    int getParent() {
        return parent;
    }
};

class Edge{
private:
    int from;
    int to;
public:
    Edge() {
        from = -1;
        to = -1;
    }
    Edge(int v, int w) {
        from = min(v, w);
        to = max(v, w);
    }
    int getFrom() {
        return from;
    }
    int getTo() {
        return to;
    }
};

vector<int> ArticulationPoint;
vector<Edge> Bridge;

void DFS(int v, Vertex*& G) {
    G[v].colorGrey();
    globalTime += 1;
    G[v].setDiscoveTime(globalTime);
    G[v].setBack(globalTime);
    for (int i = 0; i < G[v].neighbours.size(); i++) {
        int w = G[v].neighbours[i];
        if (G[w].isWhite()) {
            G[w].setParent(v);
            DFS(w, G);
            if (G[w].getBack() >= G[v].getDiscoverTime())
                ArticulationPoint.push_back(v);
            if (G[w].getBack() > G[v].getDiscoverTime())
                Bridge.push_back(Edge(v, w));
            G[v].setBack(min(G[v].getBack(), G[w].getBack()));
        }
        else {
            if (G[v].getParent() != w)
                G[v].setBack(min(G[v].getBack(), G[w].getDiscoverTime()));
        }
    }
}

bool cmp(Edge a, Edge b) {
    return a.getFrom() < b.getFrom() ||
        (a.getFrom() == b.getFrom() && a.getTo() < b.getTo());
}

int main()
{
    int numV;
    cin >> numV;
    Vertex* G = new Vertex[numV];
    int tempX, tempY;
    while (cin >> tempX >> tempY) {
        if (tempX == -1)
            break;
        G[tempX].addNeighbour(tempY);
        G[tempY].addNeighbour(tempX);
    }
    DFS(0, G);
    int countSub = 0;
    for (int i = 0; i < G[0].neighbours.size(); i++) {
        if (G[G[0].neighbours[i]].getParent() == 0)
            countSub++;
    }
    sort(ArticulationPoint.begin(), ArticulationPoint.end());
    if (countSub == 1) {
        vector<int>::iterator iter = ArticulationPoint.begin();
        if (*iter == 0)
            ArticulationPoint.erase(iter);
    }
    sort(Bridge.begin(), Bridge.end(), cmp);
    cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
    for (int i = 0; i < ArticulationPoint.size(); i++)
        cout << ArticulationPoint[i] << endl;
    for (int i = 0; i < Bridge.size() - 1; i++)
        cout << Bridge[i].getFrom() << " " << Bridge[i].getTo() << endl;
    cout << Bridge[Bridge.size() - 1].getFrom() << " " << Bridge[Bridge.size() - 1].getTo();
    return 0;
}