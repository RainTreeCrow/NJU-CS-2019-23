#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void * ping_thread_function (void *arg)
{

    while (1) {
        printf("Ping\n");
        sleep(1);
    }

    return NULL;
}

void * pong_thread_function (void *arg)
{
    while (1) {
        printf("Pong\n");
        sleep(2);
    }
    
    return NULL;
}

int main (void)
{
    pthread_t pi_thread_ID, po_thread_ID;
    void *pi_exit_status;
    void *po_exit_status;

    pthread_create(&pi_thread_ID, NULL, ping_thread_function, NULL);
    pthread_create(&po_thread_ID, NULL, pong_thread_function, NULL);
    pthread_join(pi_thread_ID, &pi_exit_status);
    pthread_join(po_thread_ID, &po_exit_status);

    return 0;
}
