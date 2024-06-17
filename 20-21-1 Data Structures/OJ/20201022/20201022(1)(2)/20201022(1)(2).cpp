#include <iostream>
using namespace std;

int main()
{
    int n, t, m;
    cin >> n >> t >> m;
    int** A = new int* [n];
    for (int i = 0; i < n; i++) {
        A[i] = new int[t];
        for (int j = 0; j < t; j++)
            cin >> A[i][j];
    }
    int** B = new int* [t];
    for (int i = 0; i < t; i++) {
        B[i] = new int[m];
        for (int j = 0; j < m; j++)
            cin >> B[i][j];
    }
    int** res = new int* [n];
    for (int i = 0; i < n; i++) {
        res[i] = new int[m];
        for (int j = 0; j < m - 1; j++) {
            res[i][j] = 0;
            for (int k = 0; k < t; k++)
                res[i][j] += A[i][k] * B[k][j];
            cout << res[i][j] << ' ';
        }
        res[i][m - 1] = 0;
        for (int k = 0; k < t; k++)
            res[i][m - 1] += A[i][k] * B[k][m - 1];
        cout << res[i][m - 1] << endl;
    }
    return 0;
}