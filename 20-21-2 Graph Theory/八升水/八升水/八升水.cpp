#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

enum Operation { ten2six, ten2five, six2ten, six2five, five2ten, five2six, null };

struct Case {
    int ten;
    int six;
    int five;
    Case() {
        ten = -1;
        six = -1;
        five = -1;
    }
    Case(int t, int s, int f) {
        ten = t;
        six = s;
        five = f;
    }
};

struct Edge {
    int next;
    Operation op;
    Edge() {
        next = -1;
        op = null;
    }
    Edge(int n, Operation o) {
        next = n;
        op = o;
    }
};

vector<Case> Cases;
vector<vector<Edge>> Graph;
int numOfCases;
vector<int> End;
int top;
bool* visited;
int* solution;
Operation* method;

void Initialize() {
    int count = 0;
    for (int i = 0; i <= 10; i++) {
        for (int j = min(11 - i, 5); j >= 0 && 11 - i - j <= 6 && 11 - i - j >= 0; j--) {
            Cases.push_back(Case(i, 11 - i - j, j));
            if (i == 8)
                End.push_back(count);
            count++;
        }
    }
    numOfCases = Cases.size();
    visited = new bool[numOfCases];
    solution = new int[numOfCases];
    method = new Operation[numOfCases];
    for (int i = 0; i < numOfCases; i++) {
        visited[i] = false;
        solution[i] = -1;
        method[i] = null;
    }
}

void AddEdges() {
    int ten, six, five;
    int nextT, nextS, nextF;
    for (int i = 0; i < numOfCases; i++) {
        vector<Edge> temp;
        for (int j = 0; j < numOfCases; j++) {
            if (i == j)
                continue;
            ten = Cases[i].ten;
            six = Cases[i].six;
            five = Cases[i].five;
            nextT = Cases[j].ten;
            nextS = Cases[j].six;
            nextF = Cases[j].five;
            if (nextT == ten) {
                if (nextF == 5 || nextS == 0)
                    temp.push_back(Edge(j, six2five));
                else if (nextS == 6 || nextF == 0)
                    temp.push_back(Edge(j, five2six));
            }
            else if (nextS == six) {
                if (nextF == 5 || nextT == 0)
                    temp.push_back(Edge(j, ten2five));
                else if (nextT == 10 || nextF == 0)
                    temp.push_back(Edge(j, five2ten));
            }
            else if (nextF == five) {
                if (nextS == 6 || nextT == 0)
                    temp.push_back(Edge(j, ten2six));
                else if (nextT == 10 || nextS == 0)
                    temp.push_back(Edge(j, six2ten));
            }
        }
        Graph.push_back(temp);
    }
}

void DFS(int pos) {
    visited[pos] = true;
    for (int i = 0; i < Graph[pos].size(); i++) {
        int next = Graph[pos][i].next;
        if (!visited[next]) {
            DFS(next);
            method[next] = Graph[pos][i].op;
            solution[next] = pos;
        }
    }
}

void PrintHelper(int i) {
    if (solution[i] != -1) {
        PrintHelper(solution[i]);
        cout << "*** Pouring from ";
        switch (method[i]) {
        case(ten2five):
            cout << "10 to 5 ***" << endl;
            break;
        case(ten2six):
            cout << "10 to 6 ***" << endl;
            break;
        case(six2ten):
            cout << "6 to 10 ***" << endl;
            break;
        case(six2five):
            cout << "6 to 5 ***" << endl;
            break;
        case(five2ten):
            cout << "5 to 10 ***" << endl;
            break;
        case(five2six):
            cout << "5 to 6 ***" << endl;
            break;
        default:
            break;
        }
        cout << "Case #" << i << ": Ten(" << Cases[i].ten << "), Five(" << Cases[i].five << "), Six(" << Cases[i].six << ")" << endl;
    }
}

void PrintSolution(int end) {
    PrintHelper(end);
}

int main()
{
    Initialize();
    AddEdges();
    for (int i = 0; i < numOfCases; i++) {
        if (!visited[i])
            DFS(i);
    }
    for (int i = 0; i < End.size(); i++) {
        if (visited[End[i]] && solution[End[i]] != -1) {
            PrintSolution(End[i]);
            break;
        }
    }
}