#include <iostream>
using namespace std;

int main()
{
    int row, col, temp;
    cin >> row >> col;
    int** matrix = new int* [row + 1];
    matrix[row] = new int[col + 1];
    for (int j = 0; j < col; j++)
        matrix[row][j] = 0;
    for (int i = 0; i < row; i++) {
        matrix[i] = new int[col + 1];
        matrix[i][col] = 0;
        for (int j = 0; j < col; j++) {
            cin >> temp;
            if (matrix[row][j])
                matrix[i][j] = 0;
            else
                matrix[i][j] = temp;
            if (temp == 0) {
                matrix[i][col] = 1;
                matrix[row][j] = 1;
                for (int k = 0; k <= i; k++)
                    matrix[k][j] = 0;
            }

        }
    }
    for (int i = 0; i < row; i++) {
        if (matrix[i][col]) {
            for (int j = 0; j < col - 1; j++)
                cout << 0 << ' ';
            cout << 0 << endl;
        }
        else {
            for (int j = 0; j < col - 1; j++)
                cout << matrix[i][j] << ' ';
            cout << matrix[i][col - 1] << endl;
        }
    }
    return 0;
}