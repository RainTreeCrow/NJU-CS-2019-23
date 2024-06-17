#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    char* mooncakes = new char[1000000];
    cin >> mooncakes;
    int total = strlen(mooncakes);
    int** saver = new int* [32];
    for (int i = 0; i < 32; i++) {
        saver[i] = new int[2];
        saver[i][0] = -1;
        saver[i][1] = 0;
    }
    bool n = 0, j = 0, u = 0, c = 0, s = 0;
    saver[0][0] = 0;
    for (int i = 1; i <= total; i++) {
        char ch = mooncakes[i - 1];
        switch (ch) {
        case('n'): n = !n; break;
        case('j'): j = !j; break;
        case('u'): u = !u; break;
        case('c'): c = !c; break;
        case('s'): s = !s; break;
        default:;
        }
        int temp = 16 * n + 8 * j + 4 * u + 2 * c + s;
        if (saver[temp][0] == -1)
            saver[temp][0] = i;
        else
            saver[temp][1] = i - saver[temp][0];
    }
    int max = saver[0][1];
    for (int i = 1; i < 32; i++) {
        if (saver[i][1] > max)
            max = saver[i][1];
    }
    cout << max;
    return 0;
}