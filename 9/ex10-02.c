#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	sigset_t set;
	int result;
	
	sigemptyset(&set);
	result = sigismember(&set, SIGALRM);
	printf("SIGALRM is %s a member\n", result ? "" : "not");

	sigaddset(&set, SIGALRM);
	result = sigismember(&set, SIGALRM);
	printf("SIGALRM is %s a member\n", result ? "" : "not");
	
	sigfillset(&set);
	result = sigismember(&set, SIGCHLD);
	printf("SIGCHLD is %s a member\n", result ? "" : "not");
	
	sigdelset(&set, SIGCHLD);
	result = sigismember(&set, SIGCHLD);
	printf("SIGCHLD is %s a member\n", result ? "" : "not");
}
