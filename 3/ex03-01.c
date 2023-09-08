#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int filedes;
	char pathname[] = "temp.txt";

	if((filedes = open(pathname, O_CREAT | O_RDWR | O_EXCL, 0644)) == -1) {
		printf("file open error!\n");
		exit(1);
	}

	if(close(filedes) == -1) {
		printf("file close failed!\n");
	}
}
