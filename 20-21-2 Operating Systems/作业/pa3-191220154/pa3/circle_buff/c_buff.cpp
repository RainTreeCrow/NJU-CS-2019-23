#include <assert.h>
#include <memory.h>
#include "c_buff.h"
using namespace std;

CircleBuffer::CircleBuffer(int size) {
	m_nBufSize = size;
	m_nReadPos = 0;
	m_nWritePos = 0;
	m_pBuf = new char[m_nBufSize];
	m_bEmpty = true;
	m_bFull = false;
	sem_init(&m_sem,0,1);
	pthread_mutex_init(&m_mutex,NULL);
	pthread_cond_init(&m_cond,NULL);
}

CircleBuffer::~CircleBuffer() {
	delete[] m_pBuf;
	sem_destroy(&m_sem);
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&m_cond);
}

int CircleBuffer::put_sem(char* buf) {
	int ret = 0;
	sem_wait(&m_sem);
	if (!isFull()) {
		ret = put_unsafe(buf);
      	cout << "Putting(sem)... pthread id: " << pthread_self() << ", value: " << buf
			<< ", length: " << getLength() << ", write pos: " << m_nWritePos << endl;
	}
	sem_post(&m_sem);
	return ret;
}

int CircleBuffer::get_sem(char* buf) {
	int ret = 0;
	sem_wait(&m_sem);
	if (!isEmpty()) {
		ret = get_unsafe(buf);
		cout << " Getting(sem)... pthread id: " << pthread_self() << ", value: " << buf
			<< ", length: " << getLength() << ", read pos: "<< m_nReadPos << endl;
	}
	sem_post(&m_sem);
	return ret;
}

int CircleBuffer::put_mut(char* buf) {
	int ret = 0;
	pthread_mutex_lock(&m_mutex);
	if (!isFull()) {
		ret = put_unsafe(buf);
		cout << "Putting(mut)... pthread id: " << pthread_self() << ", value: " << buf
			<< ", length: " << getLength() << ", write pos: " << m_nWritePos << endl;
	}
	pthread_cond_signal(&m_cond);
	pthread_mutex_unlock(&m_mutex);
	return ret;
}

int CircleBuffer::get_mut(char* buf) {
	int ret = 0;
	pthread_mutex_lock(&m_mutex);
	if(isEmpty())
		pthread_cond_wait(&m_cond,&m_mutex);
	ret = get_unsafe(buf);
	cout << " Getting(mut)... pthread id: " << pthread_self() << ", value: " << buf
		<< ", length: " << getLength() << ", read pos: "<< m_nReadPos << endl;
	pthread_mutex_unlock(&m_mutex);
	return ret;
}

int CircleBuffer::put_unsafe(char* buf) {
	int count = 1;
	if(count <= 0)
		return 0;
	m_bEmpty = false;
	if(m_bFull)
		return 0;
	else if(m_nReadPos == m_nWritePos) {
		int leftcount = m_nBufSize - m_nWritePos;
		if(leftcount > count) {
			memcpy(m_pBuf + m_nWritePos, buf, count);
			m_nWritePos += count;
			m_bFull = (m_nWritePos == m_nReadPos);
			return count;
		}
		else {
			memcpy(m_pBuf + m_nWritePos, buf, leftcount);
			m_nWritePos = (m_nReadPos > count - leftcount) ? count - leftcount : m_nWritePos;
			memcpy(m_pBuf, buf + leftcount, m_nWritePos);
			m_bFull = (m_nWritePos == m_nReadPos);
			return leftcount + m_nWritePos;
		}
	}
	else if(m_nReadPos < m_nWritePos) {
		int leftcount = m_nBufSize - m_nWritePos;
		int test = m_nWritePos;
		if(leftcount > count) {
			memcpy(m_pBuf + m_nWritePos, buf, count);
			m_nWritePos += count;
			m_bFull = (m_nReadPos == m_nWritePos);
			assert(m_nReadPos <= m_nBufSize);
			assert(m_nWritePos <= m_nBufSize);
			return count;
		}  
		else {
			memcpy(m_pBuf + test, buf, leftcount);
			m_nWritePos = (m_nReadPos >= count - leftcount) ? count - leftcount : m_nReadPos;
			memcpy(m_pBuf, buf + leftcount, m_nWritePos);
			m_bFull = (m_nReadPos == m_nWritePos);
			assert(m_nReadPos <= m_nBufSize);
			assert(m_nWritePos <= m_nBufSize);
			return leftcount + m_nWritePos;
		}
	}
	else {
		int leftcount = m_nReadPos - m_nWritePos;
		if(leftcount > count) {
			memcpy(m_pBuf + m_nWritePos, buf, count);
			m_nWritePos += count;
			m_bFull = (m_nReadPos == m_nWritePos);
			assert(m_nReadPos <= m_nBufSize);
			assert(m_nWritePos <= m_nBufSize); 
			return count;
		}
		else {
			memcpy(m_pBuf + m_nWritePos, buf, leftcount);
			m_nWritePos += leftcount;
			m_bFull = (m_nReadPos == m_nWritePos);
			assert(m_bFull);
			assert(m_nReadPos <= m_nBufSize);
			assert(m_nWritePos <= m_nBufSize);
			return leftcount;
		}
	}
}

int CircleBuffer::get_unsafe(char* buf) {
	int count = 1;
	if(count <= 0)
		return 0;
	m_bFull = false;
	if(m_bEmpty)
		return 0;
	else if(m_nReadPos == m_nWritePos) {
		int leftcount = m_nBufSize - m_nReadPos;
		if(leftcount > count) {
			memcpy(buf, m_pBuf + m_nReadPos, count);
			m_nReadPos += count;
			m_bEmpty = (m_nReadPos == m_nWritePos);
			return count;
		}
		else {
			memcpy(buf, m_pBuf + m_nReadPos, leftcount);
			m_nReadPos = (m_nWritePos > count - leftcount) ? count - leftcount : m_nWritePos;
			memcpy(buf + leftcount, m_pBuf, m_nReadPos);
			m_bEmpty = (m_nReadPos == m_nWritePos);
			return leftcount + m_nReadPos;
		}
	}
	else if(m_nReadPos < m_nWritePos) {
		int leftcount = m_nWritePos - m_nReadPos;
		int c = (leftcount > count) ? count : leftcount;
		memcpy(buf, m_pBuf + m_nReadPos, c);
		m_nReadPos += c;
		m_bEmpty = (m_nReadPos == m_nWritePos);
		assert(m_nReadPos <= m_nBufSize);
		assert(m_nWritePos <= m_nBufSize);
		return c;
	}
	else {
		int leftcount = m_nBufSize - m_nReadPos;
		if(leftcount > count) {
			memcpy(buf, m_pBuf + m_nReadPos, count);
			m_nReadPos += count;
			m_bEmpty = (m_nReadPos == m_nWritePos);
			assert(m_nReadPos <= m_nBufSize);
			assert(m_nWritePos <= m_nBufSize);
			return count;
		}
		else {
			memcpy(buf, m_pBuf + m_nReadPos, leftcount);
			m_nReadPos = (m_nWritePos >= count - leftcount) ? count - leftcount : m_nWritePos;
			memcpy(buf + leftcount, m_pBuf, m_nReadPos);
	 		m_bEmpty = (m_nReadPos == m_nWritePos);
			assert(m_nReadPos <= m_nBufSize);
			assert(m_nWritePos <= m_nBufSize);
			return leftcount + m_nReadPos;
		}
	}
}
  
int CircleBuffer::getLength() {  
	if(m_bEmpty) 
		return 0;
	else if(m_bFull)
		return m_nBufSize;
	else if(m_nReadPos < m_nWritePos)
		return m_nWritePos - m_nReadPos;
	else
		return m_nBufSize - m_nReadPos + m_nWritePos;
}

bool CircleBuffer::isEmpty() {
 return m_bEmpty;
}

bool CircleBuffer::isFull() {
 return m_bFull;
}

