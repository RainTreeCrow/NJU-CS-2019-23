#include <iostream>
using namespace std;

void Find(int i, int j, int m, int n, int**& cats, int**& max_len, int& max_route) {
    int temp_cat = cats[i][j];
    int temp_len = max_len[i][j] + 1;
    if (j - 1 >= 0 && cats[i][j - 1] > temp_cat && temp_len > max_len[i][j - 1]) {
        max_len[i][j - 1] = temp_len;
        if (temp_len > max_route)
            max_route = temp_len;
        Find(i, j - 1, m, n, cats, max_len, max_route);
    }
    if (j + 1 < n && cats[i][j + 1] > temp_cat && temp_len > max_len[i][j + 1]) {
        max_len[i][j + 1] = temp_len;
        if (temp_len > max_route)
            max_route = temp_len;
        Find(i, j + 1, m, n, cats, max_len, max_route);
    }
    if (i - 1 >= 0 && cats[i - 1][j] > temp_cat && temp_len > max_len[i - 1][j]) {
        max_len[i - 1][j] = temp_len;
        if (temp_len > max_route)
            max_route = temp_len;
        Find(i - 1, j, m, n, cats, max_len, max_route);
    }
    if (i + 1 < m && cats[i + 1][j] > temp_cat && temp_len > max_len[i + 1][j]) {
        max_len[i + 1][j] = temp_len;
        if (temp_len > max_route)
            max_route = temp_len;
        Find(i + 1, j, m, n, cats, max_len, max_route);
    }
}

int main()
{
    int m, n;
    cin >> m >> n;
    int** cats = new int* [m];
    int** max_len = new int* [m];
    int max_route = 0;
    for (int i = 0; i < m; i++) {
        cats[i] = new int[n];
        max_len[i] = new int[n];
        for (int j = 0; j < n; j++) {
            cin >> cats[i][j];
            max_len[i][j] = 1;
        }
    }
    int temp_cat, temp_len;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            Find(i, j, m, n, cats, max_len, max_route);
        }
    }
    cout << max_route;
    return 0;
}