#include "lib.h"
#include "types.h"

int data = 0;

int uEntry(void) {
	//printf("Start.\n");
	int ret = fork();
	//printf("Fork.\n");
	int i = 8;
	if (ret == 0) {
		data = 2;
		while(i != 0) {
			i--;
			printf("Child Process: Pong %d, %d;\n", data, i);
			//printf("Child Process %d: Sleep\n", i);
			sleep(128);
			//printf("Child Process %d: Wake\n", i);
		}
		//printf("Child Process %d: Exit\n", i);
		exit();
	}
	else if (ret != -1) {
		data = 1;
		while(i != 0) {
			i--;
			printf("Father Process: Ping %d, %d;\n", data, i);
			//printf("Father Process %d: Sleep\n", i);
			sleep(128);
			//printf("Father Process %d: Wake\n", i);
		}
		//printf("Father Process %d: Exit\n", i);
		exit();
	}
	while(1);
	return 0;
}
