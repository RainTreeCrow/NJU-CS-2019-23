#include <iostream>
using namespace std;

bool original(int n) {
    int* number = new int[10];
    int length = 0;
    while (n != 0) {
        number[length] = n % 10;
        n = n / 10;
        length++;
    }
    length--;
    for (int i = 0; i <= length / 2; i++) {
        if (number[i] != number[length - i]) {
            delete[] number;
            return false;
        }
    }
    delete[] number;
    return true;
}

bool binary(int n) {
    bool* binary = new bool[100000];
    int length = 0;
    while (n != 0) {
        binary[length] = n % 2;
        n = n / 2;
        length++;
    }
    length--;
    for (int i = 0; i <= length / 2; i++) {
        if (binary[i] != binary[length - i]) {
            delete[] binary;
            return false;
        }
    }
    delete[] binary;
    return true;
}

int main()
{
    int m;
    cin >> m;
    m++;
    while (!original(m) || !binary(m))
        m++;
    cout << m;
    return 0;
}