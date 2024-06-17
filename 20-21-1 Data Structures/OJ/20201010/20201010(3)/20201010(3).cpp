#include <stdio.h>
#pragma warning (disable:4996)

int Area() {
    int number;
    scanf("%d", &number);
    int* column = new int[number];
    int* width = new int[number];
    int* height = new int[number];
    int* size = new int[number];
    for (int i = 0; i < number; i++) {
        scanf("%d", &column[i]);
    }
    int temp1, temp2;
    width[0] = 1;
    height[0] = column[0];
    size[0] = column[0];
    for (int i = 1; i < number; i++) {
        if (column[i] > height[i - 1]) {
            temp1 = height[i - 1] * (width[i - 1] + 1);
            temp2 = column[i];
            if (temp1 > temp2) {
                width[i] = width[i - 1] + 1;
                height[i] = height[i - 1];
                size[i] = temp1;
            }
            else {
                width[i] = 1;
                height[i] = column[i];
                size[i] = temp2;
            }
        }
        else {
            width[i] = width[i - 1] + 1;
            height[i] = column[i];
            size[i] = column[i] * (width[i - 1] + 1);
        }
    }
    int max = 0;
    for (int i = 0; i < number; i++) {
        if (size[i] > max)
            max = size[i];
    }
    delete column;
    delete width;
    delete height;
    delete size;
    return max;
}

int main()
{
    int round;
    scanf("%d", &round);
    int* result = new int[round];
    for (int i = 0; i < round; i++)
        result[i] = Area();
    for (int i = 0; i < round - 1; i++)
        printf("%d\n", result[i]);
    printf("%d", result[round - 1]);
    return 0;
}