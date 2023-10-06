#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	pid_t pid;
	char filename[64];
	int n;

	for(n = 1; n < argc; n++) {
		strcpy(filename, argv[n]);
		printf("run \"wc %s\"\n", filename);
		pid = fork();

		if(pid == 0) {
			execl("/bin/wc", "wc", filename, (char *)0);
			printf("wc %s\n", filename);
			exit(1);
		}
	}
}
