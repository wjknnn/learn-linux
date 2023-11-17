#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 512
#define NUM 3

int main() {
	char msg[SIZE];
	int fd1[2], fd2[2];

	pid_t pid[NUM];

	int n;
	int status;

	if(pipe(fd1) == -1) {
		printf("fail to call pipe() 1\n");
		exit(1);
	}
	if(pipe(fd2) == -1) {
		printf("fail to call pipe() 2\n");
		exit(1);
	}

	for(n = 0; n < NUM; n++) {
		pid[n] = fork();
		if(pid[n] == 0)
			break;
	}

	if(n == NUM) {
		for(n = 0; n < NUM; n++) {
			waitpid(pid[n], &status, 0);
			printf("cihld %d - exit(%d)\n", pid[n], status);
		}
	}
	else if(n > NUM) {
		sleep(n);
		exit(n);
	}
}
