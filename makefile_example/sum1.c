#include<stdio.h>

int sum() {
	int result = 0;
	for(int i = 1; i <= 100; i++) {
		result += i;
	}
	printf("%d\n", result);
	return 0;
}

