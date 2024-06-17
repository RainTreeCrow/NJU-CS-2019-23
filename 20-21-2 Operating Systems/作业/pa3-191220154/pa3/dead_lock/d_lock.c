#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t mutex;
int count = 0;
void* B(void* arg);

void* A(void* arg) {
	usleep(rand() % 10 * 100000);
	printf("Enter process A.\n");
	sem_wait(&mutex);
	count++;
	printf("A: %d\n", count);
	B(NULL);
	sem_post(&mutex);
	usleep(rand() % 10 * 100000);
}

void* B(void* arg) {
	usleep(rand() % 10 * 100000);
	printf("Enter process B.\n");
	sem_wait(&mutex);
	count *= 10;
	printf("B: %d\n", count);
	sem_post(&mutex);
	usleep(rand() % 10 * 100000);
}

void test() {
	sem_init(&mutex, 0, 1);
	pthread_t thread_A;
	pthread_t thread_B;
	pthread_create(&thread_A, NULL, A, NULL);
	pthread_create(&thread_B, NULL, B, NULL);
	pthread_join(thread_A, NULL);
	pthread_join(thread_B, NULL);
	sem_destroy(&mutex);
}

int main()
{
	test();
	return 0;
}	
