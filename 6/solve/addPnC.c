#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	pid_t pid;
	int status;
	double x, y;
	
	scanf("%lf %lf", &x, &y);

	pid = fork();

	if(pid > 0) {
		double i = pow(x, y);
		wait(&status);
		printf("result is : %.0f\n", i + (double)(status>>8));
	}
	else if(pid == 0) {
		int sum = 0;
		for(int i = x; i <= y; i++) {
			sum += i;
		}
		exit(sum);
	}
}
