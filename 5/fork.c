#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	pid_t pid;
	int i = 1;

	pid = fork();

	if(pid > 0) { //parent proccess
		printf("%d\n", i++);
	}
	else if(pid == 0) { //child proccess
		printf("%d\n", i--);
	}
	else {
		printf("fail to fork!");
	}
}

