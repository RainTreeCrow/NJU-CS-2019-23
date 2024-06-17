#include <iostream>
#include <cmath>
using namespace std;

#define maxDropHeight 10000000

int** Height;
int** maxDrop;

void Find(int i, int j, int row, int col) {
    int tempHeight = Height[i][j];
    //cout << i << ' ' << j << ' ' << tempHeight << endl;
    int tempDrop;
    int updateDrop;
    if (j - 1 >= 0) {
        tempDrop = abs(Height[i][j - 1] - tempHeight);
        updateDrop = maxDrop[i][j];
        if (tempDrop > updateDrop)
            updateDrop = tempDrop;
        if (updateDrop < maxDrop[i][j - 1]) {
            maxDrop[i][j - 1] = updateDrop;
            Find(i, j - 1, row, col);
        }
    }
    if (j + 1 < col) {
        tempDrop = abs(Height[i][j + 1] - tempHeight);
        updateDrop = maxDrop[i][j];
        if (tempDrop > updateDrop)
            updateDrop = tempDrop;
        if (updateDrop < maxDrop[i][j + 1]) {
            maxDrop[i][j + 1] = updateDrop;
            Find(i, j + 1, row, col);
        }
    }
    if (i - 1 >= 0) {
        tempDrop = abs(Height[i - 1][j] - tempHeight);
        updateDrop = maxDrop[i][j];
        if (tempDrop > updateDrop)
            updateDrop = tempDrop;
        if (updateDrop < maxDrop[i - 1][j]) {
            maxDrop[i - 1][j] = updateDrop;
            Find(i - 1, j, row, col);
        }
    }
    if (i + 1 < row) {
        tempDrop = abs(Height[i + 1][j] - tempHeight);
        updateDrop = maxDrop[i][j];
        if (tempDrop > updateDrop)
            updateDrop = tempDrop;
        if (updateDrop < maxDrop[i + 1][j]) {
            maxDrop[i + 1][j] = updateDrop;
            Find(i + 1, j, row, col);
        }
    }
}

int main()
{
    int row, col;
    cin >> row >> col;
    Height = new int* [row];
    maxDrop = new int* [row];
    for (int i = 0; i < row; i++) {
        Height[i] = new int[col];
        maxDrop[i] = new int[col];
        for (int j = 0; j < col; j++) {
            cin >> Height[i][j];
            maxDrop[i][j] = maxDropHeight;
        }
    }
    maxDrop[0][0] = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            Find(i, j, row, col);
        }
    }
    cout << maxDrop[row - 1][col - 1];
    return 0;
}