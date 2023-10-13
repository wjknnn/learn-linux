#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int NUM = 5;

int main() {
	pid_t pid[NUM];
	int status;

	int n;

	for(n = 0; n < NUM; n++) {
		pid[n] = fork();
		if(pid[n] == 0) {
			break;
		}
	}

	if(n == NUM) {
		for(n = 0; n < NUM; n++) {
			waitpid(pid[n], &status, 0);
			printf("child %d - exit(%d)\n", pid[n], status);
		}
	}
	else if(n > NUM) {
		sleep(n);
		exit(n);
	}
}

