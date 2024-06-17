#include <stdio.h>
#pragma warning (disable:4996)

int Find(int*& A, int*& B, int a, int b, int k) {
    if (k == 1) {
        if (A[a] <= B[b])
            return A[a];
        else
            return B[b];
    }
    int tempA = A[a + k / 2 - 1];
    int tempB = B[b + k / 2 - 1];
    if (tempA <= tempB)
        a += k / 2;
    else
        b += k / 2;
    k = k - k / 2;
    return Find(A, B, a, b, k);
}

int main()
{
    int n;
    scanf("%d", &n);
    int* A = new int[n];
    int* B = new int[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &B[i]);
    int res = Find(A, B, 0, 0, n);
    printf("%d", res);
    return 0;
}