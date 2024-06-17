#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int** matrix = new int* [n];
    bool diagonal = 1, upper = 1, lower = 1;
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
            if (diagonal && i != j && matrix[i][j] != 0)
                diagonal = 0;
            if (upper && i > j && matrix[i][j] != 0)
                upper = 0;
            if (lower && i < j && matrix[i][j] != 0)
                lower = 0;
        }
    }
    if (diagonal)
        cout << "diagonal" << endl;
    else if (upper)
        cout << "upper" << endl;
    else if (lower)
        cout << "lower" << endl;
    else
        cout << "none" << endl;
    return 0;
}