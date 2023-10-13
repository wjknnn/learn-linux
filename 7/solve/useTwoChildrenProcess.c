#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>

int main() {
	pid_t pid1, pid2;
	int status;
	double x, y;

	scanf("%lf %lf", &x, &y);

	pid1 = pid2 = -1;

	pid1 = fork();
	if(pid1 > 0) {
		pid2 = fork();
	}
	if(pid1 > 0 && pid2 > 0) {
		double p = pow(x, y);
		int sum, mul;

		printf("1: x^y        = %.0f\n", p);

		waitpid(pid1, &status, 0);
		sum = status>>8;
		printf("2: sum x ~ y  = %d\n", sum);

		waitpid(pid2, &status, 0);
		mul = status>>8;
		printf("3: mul x ~ y  = %d\n\n", mul);

		printf("result: 3-2-1 = %.0f\n", (double)(mul-sum)-p);

	}
	else if(pid1 == 0 && pid2 == -1) {
		int sum = 0;
		for(int i = x; i <= y; i++) {
			sum += i;
		}
		exit(sum);
	}
	else if(pid1 > 0 && pid2 == 0) {
		int mul = 1;
		for(int i = x; i <= y; i++) {
			mul *= i;
		}
		exit(mul);
	}
	else {
		printf("fail to fork\n");
	}

}
