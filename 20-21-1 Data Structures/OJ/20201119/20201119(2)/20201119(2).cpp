#include <iostream>
#include <cmath>
using namespace std;

void print(int node, bool leaf, int* tree) {
    if (leaf) {
        print((node - 1) / 2, false, tree);
        cout << tree[node] << endl;
    }
    else if (node == 0)
        cout << tree[node] << ' ';
    else {
        print((node - 1) / 2, false, tree);
        cout << tree[node] << ' ';
    }
}

int main()
{
    int n;
    cin >> n;
    int level = log(n) / log(2);
    int last_row = n + 1 - pow(2, level);
    int last_last = pow(2, level - 1) - (last_row + 1) / 2;
    //cout << last_row << ' ' << last_last << endl;
    int* heap = new int[n];
    bool max = true;
    bool min = true;
    cin >> heap[0];
    for (int i = 1; i < n; i++) {
        cin >> heap[i];
        if (max && heap[i] > heap[(i - 1) / 2])
            max = false;
        if (min && heap[i] < heap[(i - 1) / 2])
            min = false;
    }
    for (int i = 0; i < last_last; i++)
        print(n - 1 - i - last_row, true, heap);
    for (int i = 0; i < last_row; i++)
        print(n - 1 - i, true, heap);
    if (max)
        cout << "Max Heap";
    else if (min)
        cout << "Min Heap";
    else
        cout << "Not Heap";
    return 0;
}