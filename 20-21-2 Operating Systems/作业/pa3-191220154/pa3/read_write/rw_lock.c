#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_rwlock_t rw_lock;
int count = 0;

void* Write(void* arg) {
	usleep(rand() % 10 * 100000);
	pthread_rwlock_wrlock(&rw_lock);
	count++;
	printf("Write: %d\n", count);
	pthread_rwlock_unlock(&rw_lock);
	usleep(rand() % 10 * 100000);
}

void* Read(void* arg) {
	usleep(rand() % 10 * 100000);
	pthread_rwlock_rdlock(&rw_lock);
	printf("Read: %d\n", count);
	pthread_rwlock_unlock(&rw_lock);
	usleep(rand() % 10 * 100000);
}

void test() {
	const int N = 20;
	pthread_t thread[N];
	pthread_rwlock_init(&rw_lock, NULL);
	for(int i = 0; i < N / 2; i++)
		pthread_create(&thread[i], NULL, Write, NULL);
	for(int i = N / 2; i < N; i++)
		pthread_create(&thread[i], NULL, Read, NULL);
	for(int i = 0; i < N; i++)
		pthread_join(thread[i], NULL);
	pthread_rwlock_destroy(&rw_lock);
}


int main()
{
	test();
	return 0;
}

