#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

enum Color { white, grey, black };

class Vertex {
private:
    int repr;
    Color colour;
    int bipartieColor;
public:
    vector<int> neighbours;
    Vertex() {
        repr = -1;
        colour = white;
        bipartieColor = 0;
    }
    Vertex(int v) {
        repr = v;
        colour = white;
        bipartieColor = 0;
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
    void setBipartieColor(int bc) {
        bipartieColor = bc;
    }
    int getBipartieColor() {
        return bipartieColor;
    }
};

bool BfsBirpartie(Vertex*& G) {
    queue<Vertex> queNode;
    Vertex v = G[0];
    v.colorGrey();
    v.setBipartieColor(1);
    queNode.push(v);
    while (!queNode.empty()) {
        Vertex w = queNode.front();
        for (int i = 0; i < w.neighbours.size(); i++) {
            int x = w.neighbours[i];
            if (G[x].isWhite()) {
                G[x].colorGrey();
                G[x].setBipartieColor(-w.getBipartieColor());
                queNode.push(G[x]);
            }
            else {
                if (G[x].getBipartieColor() == w.getBipartieColor())
                    return false;
            }
        }
        queNode.pop();
        w.colorBlack();
    }
    return true;
}

int main()
{
    string inputLine;
    Vertex* G = new Vertex[1000000];
    vector<int> vIndex;
    while (getline(cin, inputLine)) {
        if (inputLine == "q")
            break;
        stringstream inputStream(inputLine);
        int v;
        inputStream >> v;
        G[v] = Vertex(v);
        vIndex.push_back(v);
        int neighbour;
        while (inputStream >> neighbour)
            G[v].addNeighbour(neighbour);
    }
    BfsBirpartie(G);
    sort(vIndex.begin(), vIndex.end());
    vector<int>result;
    for (int i = 0; i < vIndex.size() - 1; i++) {
        //cout << G[vIndex[i]].getBipartieColor() << " " << vIndex[i] << endl;
        if (G[vIndex[i]].getBipartieColor() == 1)
            result.push_back(vIndex[i]);
    }
    cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
    for (int i = 0; i < result.size() - 1; i++)
        cout << result[i] << endl;
    cout << result[result.size() - 1];
    return 0;
}