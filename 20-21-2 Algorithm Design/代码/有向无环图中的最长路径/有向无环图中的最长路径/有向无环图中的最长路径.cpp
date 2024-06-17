#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#pragma warning (disable:4996)

enum Color { WHITE, GREY, BLACK };

struct Edge {
    int to;
    int weight;
    Edge(int t, int w) {
        to = t;
        weight = w;
    }
};

vector<vector<Edge>> Graph;
int* Size;
Color* Colour;
int* TopoNum;
int globalNum;
vector<int> Stack;
int* MaxDistance;

void TopoOrder(int v) {
    Colour[v] = GREY;
    for (int i = 0; i < Size[v]; i++) {
        int w = Graph[v][i].to;
        if (Colour[w] == WHITE)
            TopoOrder(w);
    }
    globalNum -= 1;
    TopoNum[globalNum] = v;
    //cout << globalNum << ": " << v << endl;
    Colour[v] = BLACK;
}

void TopoWrapper(int n) {
    globalNum = n;
    for (int i = 0; i < n; i++) {
        if (Colour[i] == WHITE)
            TopoOrder(i);
    }
}

void CalcMaxDist(int n) {
    MaxDistance[0] = 0;
    for (int i = 0; i < n; i++) {
        int v = TopoNum[i];
        //cout << v << " ";
        for (int j = 0; j < Size[v]; j++) {
            int w = Graph[v][j].to;
            MaxDistance[w] = max(MaxDistance[w], MaxDistance[v] + Graph[v][j].weight);
        }
    }
    //cout << endl;
}

int main()
{
    int n = 0;
    cin >> n;
    Colour = new Color[n];
    TopoNum = new int[n];
    MaxDistance = new int[n];
    Size = new int[n];
    for (int i = 0; i < n; i++) {
        Colour[i] = WHITE;
        TopoNum[i] = -1;
        MaxDistance[i] = -1;
        Size[i] = 0;
        vector<Edge> Edges;
        Graph.push_back(Edges);
    }
    int from, to, weight;
    while (scanf("%d %d %d", &from, &to, &weight) != EOF) {
        if (weight == -1)
            break;
        Edge edge(to, weight);
        Graph[from].push_back(edge);
        Size[from] += 1;
    }
    /*for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j = 0; j < Size[i]; j++)
            cout << Graph[i][j].to << "(" << Graph[i][j].weight << ") ";
        cout << endl;
    }*/
    TopoWrapper(n);
    CalcMaxDist(n);
    printf("I have read the rules about plagiarism punishment\n");
    for (int i = 1; i < n - 1; i++)
        printf("%d ", MaxDistance[i]);
    printf("%d", MaxDistance[n - 1]);
    return 0;
}