#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
 
#define MaxThreadNum 200 /*应用支持最大线程数,可配置*/
#define kSamplePoints 100000 /*总采样样本数*/

typedef unsigned long long UINT64;


/*计算时间,用于统计程序执行时间*/
inline double WallTime()
{
    struct timeval tv;
    struct timezone tz;
 
    gettimeofday(&tv, &tz);
 
    double currTime = (double)tv.tv_sec + (double)tv.tv_usec/1000000.0;
 
    return currTime;
}


/*初始化随机因子*/
void init(UINT64 *ulState)
{
    int i = 0;
    UINT64 q = 0;
    UINT64 iSeed = pthread_self();    

    ulState[0] = iSeed;
    ulState[1] = iSeed;
    ulState[2] = iSeed;
    ulState[3] = iSeed;

    for (i = 0; i < 20; ++ i)
    {
        q = ulState[0] - ((ulState[1] << 7) | (ulState[1] >> 57));
        ulState[0] = ulState[1] ^ ((ulState[2] << 13) | (ulState[2] >> 51));
        ulState[1] = ulState[2] + ((ulState[3] << 37) | (ulState[3] >> 27));
        ulState[2] = ulState[3] + q;
        ulState[3] = q + ulState[0];
    }
}


/*获取随机数*/
UINT64 rand64(UINT64 *ulState)
{
    UINT64 q = ulState[0] - ((ulState[1] << 7) | (ulState[1] >> 57));
    ulState[0] = ulState[1] ^ ((ulState[2] << 13) | (ulState[2] >> 51));
    ulState[1] = ulState[2] + ((ulState[3] << 37) | (ulState[3] >> 27));
    ulState[2] = ulState[3] + q;
    ulState[3] = q + ulState[0];
    return ulState[3];
}


/*计算多少个点在象限内*/
void *compute_pi(void * s)
{
    int i;
    double rand_no_x, rand_no_y;
    UINT64 ulState[4]={0UL}; /*随机因子*/
    int *hit_pointer = (int *)s;  /*传出参数为该线程的命中数*/  
    int sample_points_per_thread = *(int *)s;/*传入参数为该线程需处理的样本数*/ 
    
    /*初始化随机数因子*/
    init(ulState);    
    *hit_pointer = 0;
    
    for(i=0; i<sample_points_per_thread; i++)
    {
    	  /*取随机数*/
        rand_no_x = (double)(rand64(ulState))/(ULLONG_MAX);
        rand_no_y = (double)(rand64(ulState))/(ULLONG_MAX);
        
        /*落在半径为0.5，圆心(0.5,0.5)的圆内*/
        if((rand_no_x - 0.5)*(rand_no_x - 0.5) + (rand_no_y - 0.5) * (rand_no_y - 0.5) < 0.25)
        {
            (*hit_pointer)++;
        }
    }
    printf("thread[%u] hits: [%d]/[%d]\n",pthread_self(), *hit_pointer, sample_points_per_thread );
    pthread_exit(0);
}


/*calc_pi 蒙特卡洛统计方法计算PI值*/
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
    
    /*每个线程处理的样本数*/
    sample_points_per_thread = kSamplePoints / num_threads;
     
    time_start = WallTime();
 
    for(i=0; i<num_threads; i++)
    {
    	if (i == num_threads-1)
    	{
    		/*防止总样本数不能被总线程数整除,最后一个线程处理数为总样本数减去已分配样本数*/
    	  	hits[i][0] = kSamplePoints - sample_points_per_thread*(num_threads-1);
    	}
    	else
    	{	
            hits[i][0] = sample_points_per_thread;
        }
        
        /*创建线程,传入参数为该线程处理的样本数,传出参数为该线程命中数*/
        pthread_create(&p_threads[i], &attr, compute_pi, (void *)&hits[i]);
    }

    total_hits = 0;
    for(i=0; i<num_threads; i++)
    {
        pthread_join(p_threads[i], NULL);
        total_hits += hits[i][0];
    }
    
    pthread_attr_destroy(&attr);
    
    time_end = WallTime();
    
    /*总命中数/样本数*/
    printf("Total hits: [%d]/[%d]\n", total_hits,kSamplePoints); 
    /*PI计算*/
    double pi = 4.0 * (double)total_hits / kSamplePoints;

    printf("Pi: [%lf]\n", pi);
    printf("CPU core num: [%d]\nTotal threads num: [%d]\n", sysconf(_SC_NPROCESSORS_ONLN),num_threads);
    printf("Elasped time: [%lf] seconds\n", time_end - time_start);

    return 0;
}