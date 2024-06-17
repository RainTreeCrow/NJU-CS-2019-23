#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
 
#define MaxThreadNum 1000
#define kSamplePoints 100000

typedef unsigned long long UINT64;

double WallTime() {
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    double currTime = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
    return currTime;
}

void init(UINT64 *ulState) {
    int i = 0;
    UINT64 q = 0;
    UINT64 iSeed = pthread_self();    
    ulState[0] = iSeed;
    ulState[1] = iSeed;
    ulState[2] = iSeed;
    ulState[3] = iSeed;
    for (i = 0; i < 20; i++) {
        q = ulState[0] - ((ulState[1] << 7) | (ulState[1] >> 57));
        ulState[0] = ulState[1] ^ ((ulState[2] << 13) | (ulState[2] >> 51));
        ulState[1] = ulState[2] + ((ulState[3] << 37) | (ulState[3] >> 27));
        ulState[2] = ulState[3] + q;
        ulState[3] = q + ulState[0];
    }
}

UINT64 rand64(UINT64 *ulState) {
    UINT64 q = ulState[0] - ((ulState[1] << 7) | (ulState[1] >> 57));
    ulState[0] = ulState[1] ^ ((ulState[2] << 13) | (ulState[2] >> 51));
    ulState[1] = ulState[2] + ((ulState[3] << 37) | (ulState[3] >> 27));
    ulState[2] = ulState[3] + q;
    ulState[3] = q + ulState[0];
    return ulState[3];
}

void *compute_pi(void * s) {
    int i;
    double rand_no_x, rand_no_y;
    UINT64 ulState[4] = {0UL};
    int *hit_pointer = (int *)s;
    int sample_points_per_thread = *(int *)s;
    init(ulState);    
    *hit_pointer = 0;
    for(i=0; i<sample_points_per_thread; i++) {
        rand_no_x = (double)(rand64(ulState)) / (ULLONG_MAX);
        rand_no_y = (double)(rand64(ulState)) / (ULLONG_MAX);
        if((rand_no_x - 0.5)*(rand_no_x - 0.5) + (rand_no_y - 0.5) * (rand_no_y - 0.5) < 0.25) {
            (*hit_pointer)++;
        }
    }
    printf("thread[%u] hits: [%d]/[%d]\n", pthread_self(), *hit_pointer, sample_points_per_thread);
    pthread_exit(0);
}

int main(int argc, char * argv[])
{
    int i;
    double time_start, time_end;
    int total_hits, hits[MaxThreadNum][1];
    int sample_points_per_thread, num_threads;
    pthread_t p_threads[MaxThreadNum];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    if (3 != argc) {
		printf("please input thread number, ex: -t 4\n");
		return -1;
	}
	if (3 == argc && 0 != strcmp(argv[1], "-t")) {
		printf("please input thread number, ex: -t 4\n");
		return -1;
	}
	num_threads = atoi(argv[2]);
	if (num_threads > MaxThreadNum) {
		printf("the max threadnum is %d\n",MaxThreadNum);
		return -1;
	}	  
    sample_points_per_thread = kSamplePoints / num_threads;
    time_start = WallTime();
    for(i = 0; i < num_threads; i++) {
    	if (i == num_threads-1)
    	  	hits[i][0] = kSamplePoints - sample_points_per_thread*(num_threads - 1);
    	else
            hits[i][0] = sample_points_per_thread;
        pthread_create(&p_threads[i], &attr, compute_pi, (void *)&hits[i]);
    }
    total_hits = 0;
    for(i = 0; i < num_threads; i++) {
        pthread_join(p_threads[i], NULL);
        total_hits += hits[i][0];
    }
    pthread_attr_destroy(&attr);
    time_end = WallTime();
    printf("Total hits: [%d]/[%d]\n", total_hits,kSamplePoints);
    double pi = 4.0 * (double)total_hits / kSamplePoints;
    printf("Pi: [%lf]\n", pi);
    printf("CPU core num: [%d]\n", sysconf(_SC_NPROCESSORS_ONLN));
    printf("Total threads num: [%d]\n", num_threads);
    printf("Elasped time: [%lf] seconds\n", time_end - time_start);
    return 0;
}
