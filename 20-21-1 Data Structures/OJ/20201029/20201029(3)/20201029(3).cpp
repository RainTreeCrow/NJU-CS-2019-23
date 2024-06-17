#include <iostream>
using namespace std;

int main()
{
    int M;
    cin >> M;
    int** stop = new int*[1000000];
    for (int i = 0; i < 1000000; i++) {
        stop[i] = new int[3];
        stop[i][0] = 0;
        stop[i][1] = 0;
        stop[i][2] = 0;
    }
    int on, off;
    for (int i = 0; i < M; i++) {
        cin >> on >> off;
        stop[on - 1][0]++;
        stop[off - 1][1]++;
    }
    stop[0][2] = stop[0][0];
    for (int i = 1; i < 1000000; i++) {
        stop[i][2] = stop[i - 1][2] + stop[i][0] - stop[i][1];
    }
    int max = 0;
    for (int i = 0; i < 1000000; i++) {
        if (stop[i][2] > max)
            max = stop[i][2];
    }
    cout << max;
    return 0;
}