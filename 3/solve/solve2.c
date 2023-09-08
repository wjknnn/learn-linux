#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	int filedes;
	ssize_t nread;
	char buffer[1024] = { 0 };
	int chnum = 0;

	filedes = open("some.txt", O_RDONLY);

	read(filedes, buffer, 1024);

	printf("content : %s", buffer);

	for(int i = 0; buffer[i] != NULL; i++) {
		char b = buffer[i];
		if((b>64 && b<91) || (b>96 && b<123)) {
			chnum++;
		}
	}

	printf("alphabet number is %d\n", chnum);

	close(filedes);
}
