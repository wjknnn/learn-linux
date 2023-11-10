#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void int_handle(int);

int main() {
	static struct sigaction act;

	act.sa_handler = int_handle;
	sigfillset(&(act.sa_mask));
	sigaction(SIGINT, &act, NULL);

	sleep(10);
}

void int_handle(int signum) {
	printf("\nexit\n");
	char buf[1024] = "exit";
	int fd;

	fd = open("a.txt", O_CREAT | O_RDWR | O_EXCL, 0644);
	write(fd, buf, sizeof(buf));

	close(fd);
}
