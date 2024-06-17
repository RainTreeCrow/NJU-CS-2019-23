#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "c_buff.h"
using namespace std;

CircleBuffer g_circleBuffer(10);

void *thread_write_sem(void *data) {
	char buf[3] = {0};
	for (int i = 0; i < 3; ++ i) {
		sprintf(buf, "%d", i);
		g_circleBuffer.put_sem(buf);
	}
	sleep(1);
}

void *thread_write_mut(void *data) {
	char buf[3] = {0};
	for (int i = 0; i < 3; ++ i) {
		sprintf(buf, "%c", 'A' + i);
		g_circleBuffer.put_mut(buf);;
	}
	sleep(1);
}

void *thread_read_sem(void *data) {
	while (1) {
		char buf[100] = {0};
		g_circleBuffer.get_sem(buf);
		if (0 == strncmp(buf, "q", 1))
			break;
		sleep(1);
	}
}

void *thread_read_mut(void *data) {
	while (1) {
		char buf[100] = {0};
		g_circleBuffer.get_mut(buf);
		if (0 == strncmp(buf, "q", 1))
			break;
		sleep(1);
	}
}

void test_sem() {
	pthread_t p1, p2, p3, p4;
	pthread_create(&p1, NULL, thread_write_sem, NULL);
	pthread_create(&p2, NULL, thread_write_sem, NULL);
	pthread_create(&p3, NULL, thread_read_sem, NULL);
	pthread_create(&p4, NULL, thread_read_sem, NULL);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	char quit[2] = "q";
	g_circleBuffer.put_sem(quit);
	g_circleBuffer.put_sem(quit);
	pthread_join(p3, NULL);
	pthread_join(p4, NULL);
}

void test_mut() {
	pthread_t p1, p2, p3, p4;
	pthread_create(&p1, NULL, thread_write_mut, NULL);
	pthread_create(&p2, NULL, thread_write_mut, NULL);
	pthread_create(&p3, NULL, thread_read_mut, NULL);
	pthread_create(&p4, NULL, thread_read_mut, NULL);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	char quit[2] = "q";
	g_circleBuffer.put_mut(quit);
	g_circleBuffer.put_mut(quit);
	pthread_join(p3, NULL);
	pthread_join(p4, NULL);
}

int main()
{
	test_sem();
	cout << endl;
	test_mut();
	return 0;
}

