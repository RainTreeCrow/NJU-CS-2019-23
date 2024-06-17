#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int MAX_NUM = 1000000000;
int A[10];

void merge(int p, int q, int r) {
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

void* merge_sort(void* arg) {
	int* args = (int*)arg;
	int p = args[0];
	int r = args[1];
	if (p < r) {
		int q = (p + r) / 2;
		pthread_t lid;
		pthread_t rid;
		int args1[2];
		int args2[2];
		args1[0] = p;
		args1[1] = q;
		args2[0] = q + 1;
		args2[1] = r;
		pthread_create(&lid, NULL, merge_sort, args1);
		pthread_create(&rid, NULL, merge_sort, args2);
		pthread_join(lid, NULL);
		pthread_join(rid, NULL);
		merge(p, q, r);
	}
}

int main()
{
	for (int i = 0; i < 10; i++)
		A[i] = rand() % 100;
	for (int i = 0; i < 10; i++)
		printf("%d ", A[i]);
	printf("\n");
	pthread_t msid;
	int args[2];
	args[0] = 0;
	args[1] = 9;
	pthread_create(&msid, NULL, merge_sort, args);
	pthread_join(msid, NULL);
	for (int i = 0; i < 10; i++)
		printf("%d ", A[i]);
	printf("\n");
	return 0;
}

