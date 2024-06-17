#include <stdio.h>
#pragma warning (disable:4996)

int main()
{
    int number;
    scanf("%d", &number);
    int* column = new int[number];
    int* left = new int[number];
    left[0] = 0;
    int* right = new int[number];
    right[number - 1] = 0;
    int temp, max = 0;
    long long int total = 0;
    for (int i = 0; i < number; i++)
        scanf("%d", &column[i]);
    for (int i = 1; i < number; i++) {
        if (column[i - 1] > left[i - 1])
            left[i] = column[i - 1];
        else
            left[i] = left[i - 1];
    }
    for (int i = number - 2; i >= 0; i--) {
        if (column[i + 1] > right[i + 1])
            right[i] = column[i + 1];
        else
            right[i] = right[i + 1];
    }
    for (int i = 1; i < number - 1; i++) {
        if (left[i] <= right[i])
            max = left[i];
        else
            max = right[i];
        temp = max - column[i];
        if (temp > 0)
            total += temp;
    }
    printf("%lld", total);
    return 0;
}