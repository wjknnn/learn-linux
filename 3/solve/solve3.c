#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
        int filedes;
        ssize_t nread;
        char buffer[1024] = { 0 };
        int chnum = 0;

        filedes = open(argv[1], O_RDWR);

        read(filedes, buffer, 1024);

        printf("content : %s", buffer);

        for(int i = 0; buffer[i] != NULL; i++) {
                char b = buffer[i];
                if(b>='a' && b<='z') {
			buffer[i] = b-32;
		}
        }

        printf("change done. : %s", buffer);

	lseek(filedes, (off_t)0, SEEK_SET);

	write(filedes, buffer, strlen(buffer));

        close(filedes);
}
