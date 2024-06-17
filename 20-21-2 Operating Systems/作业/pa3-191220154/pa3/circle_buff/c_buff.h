#ifndef CIRCLEBUFFER_H
#define CIRCLEBUFFER_H

#include<pthread.h>
#include<string.h>
#include<iostream>
#include<semaphore.h>

class CircleBuffer {
public:
	CircleBuffer(int size);
	~CircleBuffer();
	bool isFull();
	bool isEmpty();
	int getLength();
	int put_sem(char* buf);
	int get_sem(char* buf);
	int put_mut(char* buf);
	int get_mut(char* buf);
private:
	int put_unsafe(char* buf);
	int get_unsafe(char* buf);
	bool m_bEmpty, m_bFull;
	char * m_pBuf;
	int m_nBufSize;
	int m_nReadPos;
	int m_nWritePos;
	sem_t m_sem;
	pthread_cond_t m_cond;
	pthread_mutex_t m_mutex;
};

#endif // CIRCLEBUFFER_H
