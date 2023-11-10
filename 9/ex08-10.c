#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	putenv("APPLE=BANANA");
	printf("%s\n", getenv("APPLE"));

	execl("ex08-11", "ex08-11", (char *)0);
}
