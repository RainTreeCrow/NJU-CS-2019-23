#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

enum colour {
    WHITE,
    GREY,
    BLACK
};

vector<vector<int>> G;
vector<vector<int>> GT;
int numOfVertex;
colour* colourOfVertex;
int* reprOfSCC;
vector<int> stack;
vector<vector<int>> vertexInSCC;
vector<int> influenceOfSCC;
vector<int> result;

void inputGraph() {
    string input;
    while (getline(cin, input)) {
        vector<int> vertex;
        int neighbour;
        stringstream input_stream(input);
        while (input_stream >> neighbour)
            vertex.push_back(neighbour);
        if (neighbour == -1)
            break;
        G.push_back(vertex);
    }
}

void transposeGraph() {
    for (int i = 0; i < numOfVertex; i++) {
        vector<int> vertex;
        GT.push_back(vertex);
    }
    for (int i = 0; i < numOfVertex; i++) {
        for (int j = 0; j < G[i].size(); j++)
            GT[G[i][j]].push_back(i);
    }
}

void resetColor() {
    for (int i = 0; i < numOfVertex; i++)
        colourOfVertex[i] = WHITE;
}

void markEndDFS(int v) {
    colourOfVertex[v] = GREY;
    for (int i = 0; i < G[v].size(); i++) {
        int w = G[v][i];
        if (colourOfVertex[w] == WHITE)
            markEndDFS(w);
    }
    colourOfVertex[v] = BLACK;
    stack.push_back(v);
}

void markSccDFS(int v, int repr) {
    colourOfVertex[v] = GREY;
    for (int i = 0; i < GT[v].size(); i++) {
        int w = GT[v][i];
        if (colourOfVertex[w] == WHITE)
            markSccDFS(w, repr);
    }
    reprOfSCC[v] = repr;
    vertexInSCC[repr].push_back(v);
    colourOfVertex[v] = BLACK;
}

void influenceDFS(int v, int &influence) {
    colourOfVertex[v] = GREY;
    for (int i = 0; i < G[v].size(); i++) {
        int w = G[v][i];
        if (colourOfVertex[w] == WHITE) {
            influenceDFS(w, influence);
            influence++;
        }
    }
    colourOfVertex[v] = BLACK;
}

int SCC() {
    for (int i = 0; i < numOfVertex; i++) {
        if (colourOfVertex[i] == WHITE)
            markEndDFS(i);
    }
    resetColor();
    int repr = 0;
    while (stack.size() != 0) {
        int v = stack.back();
        if (reprOfSCC[v] == -1) {
            vector<int> vertex;
            vertexInSCC.push_back(vertex);
            markSccDFS(v, repr);
            repr++;
        }
        stack.pop_back();
    }
    return repr;
}

int getMaxSCC(int num) {
    int maxInfluence = 0;
    for (int sccI = 0; sccI < num; sccI++) {
        int v = vertexInSCC[sccI][0];
        resetColor();
        int influence = 0;
        influenceDFS(v, influence);
        influenceOfSCC.push_back(influence);
        if (influence > maxInfluence)
            maxInfluence = influence;
    }
    for (int sccI = 0; sccI < num; sccI++) {
        if (influenceOfSCC[sccI] == maxInfluence) {
            for (int i = 0; i < vertexInSCC[sccI].size(); i++)
                result.push_back(vertexInSCC[sccI][i]);
        }
    }
    sort(result.begin(), result.end());
    return maxInfluence;
}

int main()
{
    inputGraph();
    numOfVertex = G.size();
    transposeGraph();
    colourOfVertex = new colour[numOfVertex];
    resetColor();
    reprOfSCC = new int[numOfVertex];
    for (int i = 0; i < numOfVertex; i++)
        reprOfSCC[i] = -1;
    int numOfSCC = SCC();
    int maxInfluence = getMaxSCC(numOfSCC);
    cout << "I have read the rules about plagiarism punishment\n";
    cout << maxInfluence << endl;
    for (int i = 0; i < result.size() - 1; i++)
        cout << result[i] << ' ';
    cout << result[result.size() - 1];
    return 0;
}