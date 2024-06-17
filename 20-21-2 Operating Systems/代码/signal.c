#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void alarm_handle(int);
static void sigint_handle(int);

void main(void)
{
	int p_id, pp_id;
	
	signal(SIGHUP, SIG_IGN);
	
	signal(SIGALRM, alarm_handle);

	signal(SIGINT, sigint_handle);

	alarm(5);

	p_id = getpid();
	pp_id = getppid();

	printf("Process ID: %d, Parent Process ID: %d\n", p_id, pp_id);

	while(1);

	exit(0);
}

static void alarm_handle(int sig_no)
{
	printf("Recieved an alarm!\n");
	return;
}

static void sigint_handle(int sig_no)
{
	printf("\n");
	printf("DEL\n");
	exit(-1);
}