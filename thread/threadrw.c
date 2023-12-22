#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int flag = 1;

void *thread_write(void *arg) {
	pthread_t tid;
	FILE *fp;

	tid = pthread_self();

	fp = fopen("./test.txt", "w");
	printf("thread writing...\n");
	if(fprintf(fp, "test content")) {
		flag = 0;
	}
	fclose(fp);
}

int main() {
	pthread_t thread;
	FILE *fp;
	char info[1024];

	pthread_create(&thread, NULL, thread_write, NULL);

	printf("thread waiting...\n");
	while(flag == 1);
	printf("waiting end!\n");

	fp = fopen("./test.txt", "r");

	fgets(info, 1024, fp);

	printf("read data is : %s\n", info);

	fclose(fp);
}
