#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	pid_t pid;
	int num = 0;
	int result = 1;
	scanf("%d", &num);

	pid = fork();

	if(pid > 0) {
		for(int i = 2; i <= num; i++) {
			result+=i;
		}
		printf("\nparent : %d\n", result);
	}
	else if(pid == 0) {
		for(int i = 1; i <= num; i++) {
			result*=i;
		}
		printf("\nchild : %d\n\n", result);
	}
	else {
		printf("\nfork failed\n");
	}
}

