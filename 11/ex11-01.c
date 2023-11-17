#include <unistd.h>
#include <systypes.h>
#include <fcntl.h>

#define MSGSIZE 100

int main() {
	pid_t pid1, pid2;
	int filedes, p1[2], p2[2];
	fd_set initset, newset;
	int nread;
	char msg[MSGSIZE];

	pipe(p1);
	pipe(p2);

	pid1 = pid2 = 0;
	pid1 = fork();
	if(pid1 > 0) {
		pid2 = fork();
	}
	if(pid1 > 0 && pid2 > 0) {
		printf("[parent] hello!\n");
		close(p1[1]);
		close(p2[1]);

		FD_ZERO(&initset);
		FD_SET(p1[0], &initset);
		FD_SET(p2[0], &initset);

		newset = initset;
		while(select(p2[0]+1, &newset, NULL, NULL, NULL) > 0) {
			if(FD_ISSET(p1[0], &newset))
				if(read(p1[0], msg, MSGSIZE) > 0)
					printf("[parent] %s\n", msg);
			if(FD_ISSET(p2[0], &newset))
				if(read(p2[0], msg, MSGSIZE) > 0)
					printf("[parent] %s\n", msg);
			newset = initset;
		}
	}
	else if(pid1 == 0 && pid2 ==0) {
		printf("[fork1] hello!\n");
		close(p1[0]);
		close(p2[0]);
		close(p2[1]);

		dup2(p1[1], 1);
		execl("ex11-01c", "ex11-01c", (char *)0);
	}
	else if(pid1 > 0 && pid2 == 0) {
		printf("[fork2] hello!\n");
		close(p1[0]);
		close(p1[1]);
		close(p2[0]);
		write(p2[1], "from fork2 via pipe", MSGSIZE);

		mkfifo("./fifo", 0666);
		filedes = open("./fifo", O_RDWR);
		nread = read(filedes, msg, MSGSIZE);
		printf("%s (%d)\n", msg, nread);
		close(filedes);
		unlink("./fifo");
	}
	else
		exit(1);
}
