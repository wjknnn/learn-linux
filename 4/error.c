#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main() {
	int file;
	if((file = open("testFile", O_RDONLY)) < 0) {
		printf("%d\n", errno);
		printf("%s\n", strerror(errno));
	}
}
