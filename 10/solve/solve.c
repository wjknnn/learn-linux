#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void handler();

int main() {
	pid_t pid;
	struct sigaction act;

	if((pid = fork()) > 0) {
		act.sa_handler = handler;
		sigfillset(&(act.sa_mask));
		sigaction(SIGINT, &act, NULL);
		sleep(1);
		pause();
	}
	else if(pid == 0) {
		printf("[child] created\n");
		sleep(1);
                kill(getppid(), SIGINT);
        }
        else {
                printf("fail to fork\n");
        }
}

void handler(int signum) {
	printf("[parent] child is killed.\n");
}
