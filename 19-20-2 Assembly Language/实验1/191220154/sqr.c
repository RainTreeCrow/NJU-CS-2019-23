#include <stdio.h>

int main()
{
    long int i, j;
    i = 40000;
    j = i * i;
    printf("The 40000*40000 is %ld\n", j);
    i = 50000;
    j = i * i;
    printf("The 50000*50000 is %ld\n", j);
    return 0;
}

