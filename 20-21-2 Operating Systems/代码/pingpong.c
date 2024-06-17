#include <stdio.h>
#include <unistd.h>

int main(void)
{
    if (fork() == 0)
        while(1){
		    sleep(1);
		    printf("Ping\n");
	}
    else
	while(1){
		    sleep(2);
		    printf("Pong\n");
	}
    return 0;
}

