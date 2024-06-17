#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t wrt, mutex;
int readcount = 0;
int count = 0;

void* Write(void* arg) {
	usleep(rand() % 10 * 100000);
	sem_wait(&wrt);
	count++;
	printf("Write: %d\n", count);
	sem_post(&wrt);
	usleep(rand() % 10 * 100000);
}

void* Read(void* arg) {
	usleep(rand() % 10 * 100000);
	sem_wait(&mutex);
	readcount++;
	if (readcount == 1)
		sem_wait(&wrt);
	sem_post(&mutex);
	printf("Read: %d\n", count);
	sem_wait(&mutex);
	readcount--;
	if (readcount == 0)
		sem_post(&wrt);
	sem_post(&mutex);
	usleep(rand() % 10 * 100000);
}

void test() {
	sem_init(&mutex, 0, 1);
	sem_init(&wrt, 0, 1);
	const int N = 20;
	pthread_t thread[N];
	for(int i = 0; i < N / 2; i++)
		pthread_create(&thread[i], NULL, Write, NULL);
	for(int i = N / 2; i < N; i++)
		pthread_create(&thread[i], NULL, Read, NULL);
	for(int i = 0; i < N; i++)
		pthread_join(thread[i], NULL);
	sem_destroy(&mutex);
	sem_destroy(&wrt);
}

int main()
{
	test();
	return 0;
}

