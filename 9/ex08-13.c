#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main() {
	while(*environ) {
		printf("%s\n", *environ++);
	}
}
