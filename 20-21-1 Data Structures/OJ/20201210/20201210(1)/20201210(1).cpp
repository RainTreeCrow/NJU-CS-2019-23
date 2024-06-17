#include <iostream>
using namespace std;

int main()
{
    int m, n, k;
    cin >> m >> n >> k;
    bool** connected = new bool* [m];
    for (int i = 0; i < m; i++) {
        connected[i] = new bool[m];
        for (int j = 0; j < m; j++)
            connected[i][j] = false;
    }
    int x, y;
    for (int i = 0; i < k; i++) {
        cin >> x >> y;
        connected[x][y] = true;
        connected[y][x] = true;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                if (connected[i][k] && connected[k][j]) {
                    connected[i][j] = true;
                    connected[j][i] = true;
                }
            }
        }
    }
    int index, count, max = 0, max_index = 0;
    for (int i = 0; i < n; i++) {
        cin >> index;
        count = 0;
        for (int j = 0; j < m; j++)
            if (connected[index][j]) count++;
        if (count > max) {
            max = count;
            max_index = index;
        }
    }
    cout << max_index;
    return 0;
}