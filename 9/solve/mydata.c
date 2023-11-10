#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	putenv("MYDATA=5");
	printf("%s\n", getenv("MYDATA"));

	execl("show-mydata", "show-mydata", (char *)0);
}
