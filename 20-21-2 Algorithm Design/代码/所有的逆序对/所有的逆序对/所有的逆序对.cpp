#include <iostream>
#include <string>
using namespace std;

template <class T>
long long int MergeCount(T*& A, int a, T*& B, int b, T*& S) {
    int idxA = 0;
    int idxB = 0;
    long long int num = 0;
    int idxS = 0;
    while (idxA < a && idxB < b) {
        if (B[idxB] < A[idxA]) {
            S[idxS] = B[idxB];
            num += a - idxA;
            idxB++;
        }
        else {
            S[idxS] = A[idxA];
            idxA++;
        }
        idxS++;
    }
    while (idxA < a) {
        S[idxS] = A[idxA];
        idxA++;
        idxS++;
    }
    while (idxB < b) {
        S[idxS] = B[idxB];
        idxB++;
        idxS++;
    }
    return num;
}

template <class T>
long long int CountInversion(T*& S, int n) {
    if (n == 1)
        return 0;
    else {
        int b = n / 2;
        int a = n - b;
        T* A = new T[a];
        for (int i = 0; i < a; i++)
            A[i] = S[i];
        T* B = new T[b];
        for (int j = 0; j < b; j++)
            B[j] = S[a + j];
        long long int IA = CountInversion(A, a);
        long long int IB = CountInversion(B, b);
        long long int IAB = MergeCount(A, a, B, b, S);
        long long int I = IA + IB + IAB;
        delete[] A;
        delete[] B;
        return I;
    }
}

int main()
{
    int n;
    cin >> n;
    string* list = new string[n];
    for (int i = 0; i < n; i++)
        cin >> list[i];
    long long int result = CountInversion<string>(list, n);
    cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
    cout << result;
    return 0;
}