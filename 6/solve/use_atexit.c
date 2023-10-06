#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int filedes;

void closeFile(){
	close(filedes);
	printf("file is closed!\n");
}

int main(int argc, char *argv[]) {
	char buffer[1024] = {0};
	
	filedes = open(argv[1], O_RDONLY);

	read(filedes, buffer, 1024);

	printf("%s", buffer);

	atexit(closeFile);

	exit(1);
}
