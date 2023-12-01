#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR 1024

struct swInfo {
	char argv[4][MAX_STR];
}p[10];

void readFileList();
char *rtrim(const char *s);
char *ltrim(const char *s);
char *trim(const char *s);

int main() {
	readFileList();
}

void readFileList(void) {
	FILE *fp;
	fp = fopen("./SwInfo.txt", "r");
	char swStr[MAX_STR];
	int swno = 0;

	while(fgets(swStr, MAX_STR, fp)) {
		int n = 0;
		char *result;
		swStr[strlen(swStr) - 1] = '\0';
		result = strtok(swStr, ";");
		strcpy(p[swno].argv[0], trim(result));
		printf("\n------%s------\n", p[swno].argv[0]);
		
		while(result != NULL && n < 3) {
			n++;
			char *result;
			result = strtok(NULL, ";");
			if(result != NULL) {
				strcpy(p[swno].argv[n], trim(result));
				printf("p[%d].argv[%d] = %s\n", swno, n, p[swno].argv[n]);
			}
			else break;
		}
		swno++;
	}
	fclose(fp);
}

char *rtrim(const char *s) {
	while(isspace(*s) || !isprint(*s))
		++s;
	return strdup(s);
}

char *ltrim(const char *s) {
	char *r = strdup(s);
	if(r != NULL) {
		char *fr = r + strlen(s) - 1;
		while((isspace(*fr) || !isprint(*fr) || *fr == 0) && fr >= r)
			--fr;
		*++fr = 0;
	}
	return r;
}

char *trim(const char *s) {
	char *r = rtrim(s);
	char *l = ltrim(r);
	free(r);
	return l;
}
