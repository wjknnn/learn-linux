#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main() {
	int p[2];
	pid_t pid;
	int fd_read, fd_write;

	char *buffer;
	char *file1 = "a.txt";
	char *file2 = "b.txt";

	int pipe_size, nread;

	pipe_size = fpathconf(p[1], _PC_PIPE_BUF);

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
		fd_read = open(file1, O_RDONLY);
		buffer = (char *)malloc(sizeof(char) * pipe_size);

		while((nread = read(fd_read, buffer, pipe_size)) > 0)
			write(p[1], buffer, nread);
		close(fd_read);
		free(buffer);

		int pipeSize;
		int fileSize;
		pipeSize = fpathconf(p[1], _PC_PIPE_BUF);
		fileSize = sizeof(buffer);
	}
	else {
		printf("[child]\n");
		fd_write = open(file2, O_CREAT | O_RDWR | O_EXCL, 0644);
		buffer = (char *)malloc(sizeof(char) * pipe_size);

		while((nread = read(p[0], buffer, pipe_size)) > 0)
			write(fd_write, buffer, nread);

		close(fd_write);
		free(buffer);
	}
}
