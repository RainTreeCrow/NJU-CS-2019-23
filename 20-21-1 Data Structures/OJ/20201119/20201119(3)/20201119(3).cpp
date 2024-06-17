#include <iostream>
using namespace std;

bool isPair(int a, int b) {
    if (a % 2 == 0)
        return b == a + 1;
    else
        return b == a - 1;
}

int Pair(int i) {
    if (i % 2 == 0)
        return i + 1;
    else
        return i - 1;
}

int main()
{
    int N;
    cin >> N;
    int* pos = new int[N];
    int* index = new int[N];
    for (int i = 0; i < N; i++) {
        cin >> index[i];
        pos[index[i]] = i;
    }
    int count = 0;
    int temp_i, temp_p;
    for (int i = 0; i < N; i += 2) {
        if (!isPair(index[i], index[i + 1])) {
            temp_i = Pair(index[i]);
            temp_p = pos[temp_i];
            pos[index[i + 1]] = temp_p;
            pos[temp_i] = i + 1;
            index[temp_p] = index[i + 1];
            index[i + 1] = temp_i;
            count++;
        }
    }
    cout << count;
    return 0;
}