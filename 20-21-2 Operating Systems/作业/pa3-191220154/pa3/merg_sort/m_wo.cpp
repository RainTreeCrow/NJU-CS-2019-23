#include <stdio.h>
#include <stdlib.h>

int MAX_NUM = 1000000000;

void merge(int*& A, int p, int q, int r) {
	int n1 = q - p + 1;
	int n2 = r - q;
	int* L = new int[n1 + 1];
	int* R = new int[n2 + 1];
	int i, j, k;
	for (i = 0; i < n1; i++)
		L[i] = A[p + i];
	for (j = 0; j < n2; j++)
		R[j] = A[q + j + 1];
	L[n1] = MAX_NUM;
	R[n2] = MAX_NUM;
	i = 0; j = 0;
	for (k = p; k <= r; k++) {
		if (L[i] < R[j]) {
			A[k] = L[i];
			i += 1;
		}
		else {
			A[k] = R[j];
			j += 1;
		}
	}
	delete[] L;
	delete[] R;
}

void merge_sort(int*& A, int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		merge_sort(A, p, q);
		merge_sort(A, q + 1, r);
		merge(A, p, q, r);
	}
}

int main()
{
	int* array = new int[10];
	for (int i = 0; i < 10; i++)
		array[i] = rand() % 100;
	for (int i = 0; i < 10; i++)
		printf("%d ", array[i]);
	printf("\n");
	merge_sort(array, 0, 9);
	for (int i = 0; i < 10; i++)
		printf("%d ", array[i]);
	printf("\n");
	return 0;
}

