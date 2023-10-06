#include <unistd.h>

int main() {
	printf("before executing ls -l\n");
	execl("/bin/ls", "ls", "-l", (char *)0);
	printf("after executing ls -l\n");
}
