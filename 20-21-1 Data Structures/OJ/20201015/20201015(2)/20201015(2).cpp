#include <iostream>
using namespace std;

int main()
{
    int** storage = new int* [1000];
    storage[0] = new int[0];
    storage[1] = new int[1];
    storage[1][0] = 2;
    for (int i = 2; i < 1000; i += 2) {
        int num = i / 2 + 1;
        storage[i] = new int[num];
        storage[i + 1] = new int[num];
        storage[i][0] = num;
        storage[i][1] = storage[i - 1][0] + 1;
        storage[i + 1][1] = num + 1;
        for (int j = 2; j < num; j++) {
            storage[i][j] = storage[i - 1][j - 1] + 1;
            storage[i + 1][j] = storage[i - 1][j - 2] + 2;
        }
        storage[i][num - 1] = storage[i - 1][num - 2] + 1;
        storage[i + 1][0] = storage[i - 1][num - 2] + 2;
    }
    int count;
    cin >> count;
    int* list = new int[count];
    for (int i = 0; i < count; i++)
        cin >> list[i];
    for (int i = 0; i < count; i++) {
        int index = list[i];
        if (index == 1)
            cout << 1 << endl;
        else {
            for (int j = 0; j < index / 2 - 1; j++)
                cout << storage[index - 1][j] << ' ' << j + 1 << ' ';
            cout << storage[index - 1][index / 2 - 1] << ' ' << index / 2;
            if (index % 2 != 0)
                cout << ' ' << storage[index - 1][index / 2];
            cout << endl;
        }
    }
}