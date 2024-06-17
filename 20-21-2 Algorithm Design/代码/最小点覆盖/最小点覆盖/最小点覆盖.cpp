#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> Graph;
vector<int> Size;
int** Case;

void BFS(int v, int father) {
    Case[v][0] = 0;
    Case[v][1] = 1;
    for (int i = 0; i < Size[v]; i++) {
        int w = Graph[v][i];
        if (w == father)
            continue;
        else {
            BFS(w, v);
            Case[v][0] += Case[w][1];
            Case[v][1] += min(Case[w][0], Case[w][1]);
        }
    }
}

int BFSWrapper(int n) {
    Case = new int* [n];
    for (int i = 0; i < n; i++) {
        Case[i] = new int[2];
        Case[i][0] = 0;
        Case[i][1] = 0;
    }
    BFS(0, 0);
    return min(Case[0][0], Case[0][1]);
}

int main()
{
    int n = 0;
    string input;
    while (getline(cin, input)) {
        vector<int> Edges;
        int from, to;
        int size = 0;
        stringstream inputStream(input);
        if (inputStream >> from) {
            if (from == -1)
                break;
        }
        while (inputStream >> to) {
            Edges.push_back(to);
            size++;
        }
        Graph.push_back(Edges);
        Size.push_back(size);
        n++;
    }
    int result = BFSWrapper(n);
    cout << "I have read the rules about plagiarism punishment" << endl;
    cout << result;
    return 0;
}