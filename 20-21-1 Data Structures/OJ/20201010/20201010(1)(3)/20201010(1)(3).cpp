#include <stdio.h>
#pragma warning (disable:4996)

int main()
{
    int start, total;
    scanf("%d%d", &start, &total);
    int address, temp, count = 0;
    int* data = new int[100000];
    int* next = new int[100000];
    int* list = new int[100000];
    for (int i = 0; i < total; i++) {
        scanf("%d", &address);
        scanf("%d%d", &data[address], &next[address]);
    }
    temp = start;
    while (temp != -1) {
        list[count] = temp;
        temp = next[temp];
        count += 1;
    }
    for (int i = count - 1; i > 0; i--)
        printf("%05d %d %05d\n", list[i], data[list[i]], list[i - 1]);
    printf("%05d %d %d", list[0], data[list[0]], -1);
    delete data;
    delete next;
    delete list;
    return 0;
}