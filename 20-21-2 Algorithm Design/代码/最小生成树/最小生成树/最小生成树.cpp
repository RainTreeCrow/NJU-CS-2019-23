#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
    Edge(int f, int t, int w) {
        from = f;
        to = t;
        weight = w;
    }
    bool operator < (const Edge& e) const {
        return weight < e.weight;
    }
};

class UFSets {
public:
    UFSets(int sz);
    ~UFSets() { delete[]parent; }
    //UFSets& operator = (UFSets& R);
    void Union(int Root1, int Root2);
    int Find(int x);
    void WeightedUnion(int Root1, int Root2);
    void UnionByHeight(int Root1, int Root2);
    int CountSets();
private:
    int* parent;
    int size;
};

UFSets::UFSets(int sz) {
    size = sz;
    parent = new int[size];
    for (int i = 0; i < size; i++) parent[i] = -1;
};

int UFSets::Find(int x) {
    if (parent[x] < 0) return x;
    else return (Find(parent[x]));
};

void UFSets::Union(int Root1, int Root2) {
    parent[Root1] += parent[Root2];
    parent[Root2] = Root1;
};

void UFSets::WeightedUnion(int Root1, int Root2) {
    int temp = parent[Root1] + parent[Root2];
    if (parent[Root2] < parent[Root1]) {
        parent[Root1] = Root2;
        parent[Root2] = temp;
    }
    else {
        parent[Root2] = Root1;
        parent[Root1] = temp;
    }
};

void UFSets::UnionByHeight(int Root1, int Root2) {
    if (Find(Root1) != Find(Root2)) {
        parent[Root1] += parent[Root2];
        for (int i = 0; i < size; i++) {
            if (Find(i) == Root2)
                parent[i] = Root1;
        }
    }
}

int UFSets::CountSets() {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (parent[i] < 0)
            count++;
    }
    return count;
}

int Kruskal(vector<Edge> G, int s, int e) {
    UFSets Vertex(s);
    int tempfrom, tempto;
    int totalweight = 0;
    int count = 0;
    for (int i = 0; i < e; i++) {
        Edge e = G[i];
        tempfrom = Vertex.Find(e.from);
        tempto = Vertex.Find(e.to);
        if (tempfrom != tempto) {
            totalweight += e.weight;
            count++;
            if (count == s - 1)
                break;
            Vertex.WeightedUnion(tempfrom, tempto);
        }
    }
    return totalweight;
}

int main()
{
    int size, edges;
    cin >> size;
    edges = 0;
    vector<Edge> Graph;
    int from, to, weight;
    while (cin >> from >> to >> weight) {
        //if (weight == -1)
            //break;
        Graph.push_back(Edge(from, to, weight));
        edges++;
    }
    sort(Graph.begin(), Graph.end());
    int result = Kruskal(Graph, size, edges);
    cout << result;
    return 0;
}