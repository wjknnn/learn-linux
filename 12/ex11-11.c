#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char *msg[3] = {"apple is red\n", "banana is yellow\n", "cherry is red\n"};

	int p[2];
	pid_t pid;
	int cnt;

	if(pipe(p) == -1) {
		printf("fail to call pipe()\n");
		exit(1);
	}

	if((pid = fork()) == -1) {
		printf("fail to call fork()\n");
		exit(1);
	}
	else if(pid > 0) {
		printf("[parent]\n");
		close(p[0]);
		for(cnt = 0; cnt < 3; cnt++)
			write(p[1], msg[cnt], strlen(msg[cnt]) + 1);
	}
	else  {
		printf("[child]\n");
		close(p[1]);
		dup2(p[0], 0);
		execlp("wc", "wc", (char *)0);
		printf("[child] fail to call execlp()\n");
	}
}
