#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#define MAX_STR 1024

struct swInfo {
	char argv[3][MAX_STR];
	char name[MAX_STR];
	char time[MAX_STR];
	char *reason;
	int cnt;
}p[10];

int PROCESS_NUM;

void readFileList(FILE *fp);
void SwInit(FILE *fp, struct tm *t);
void countProcess();
char *rtrim(const char *s);
char *ltrim(const char *s);
char *trim(const char *s);

void countProcess() {
	for(int i = 0; i < 10; i++) {
		if(p[i].cnt > 0) PROCESS_NUM++;
		else break;
	}
}

int main() {
	FILE *fp;
	time_t timer;
	struct tm *t;
	timer = time(NULL);
	t = localtime(&timer);

	readFileList(fp);
	SwInit(fp, t);
	countProcess();

	int i;
	int pnum = 0;
	pid_t pid[PROCESS_NUM];

	pid[0] = fork();
	for(i = 1; i < PROCESS_NUM; i++) {
		if(pid[i - 1] > 0) {
			pid[i] = fork();
			if(pid[i] > 0) {
				printf("i'm parent pid[%d]\n", i);
			}
			else {
				printf("i'm child pid[%d]\n", i);
			}
			//sleep(1);
		}
	}
	
	for(i = 0; i < PROCESS_NUM; i++) {
		if(pid[i] > 0) pnum++;
		else break;
	}

	if(pnum == PROCESS_NUM) {
		printf("\n----im parent----\n");
		for(int i = 0; i < PROCESS_NUM; i++) {
			printf("%d번째 : %d\n", i, pid[i]);
		}
		//while(1) {
			
		//}
	}
}

void readFileList(FILE *fp) {
	fp = fopen("./SwInfo.txt", "r");
	char swStr[MAX_STR];
	int swNum = 0;

	while(fgets(swStr, MAX_STR, fp)) { // 한 줄씩 get
		int n = 0;
		char *result;
		swStr[strlen(swStr) - 1] = '\0';	// 개행문자 제거
		result = strtok(swStr, ";");		// 토큰 파싱
		strcpy(p[swNum].name, trim(result));	// name 저장
		printf("\n------%s------\n", p[swNum].name);
		
		while(result != NULL && n < 3) {
			char *result;
			result = strtok(NULL, ";");
			if(result != NULL) {
				strcpy(p[swNum].argv[n], trim(result)); //argv 저장
				printf("p[%d].argv[%d] = %s\n", swNum, n, p[swNum].argv[n]);
			}
			else break;
			n++;
		}
		swNum++;
	}
	fclose(fp);
}

void SwInit(FILE *fp, struct tm *t) {
	fp = fopen("./log/restart.txt", "w");

	for(int i = 0; strlen(p[i].name); i++) {
		sprintf(p[i].time, "%04d.%02d.%02d. %02d:%02d:%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
		p[i].reason = "Init";
		p[i].cnt++;
		fprintf(fp, "%s\t%d\t%s\t%s\n", p[i].name, p[i].cnt, p[i].time, p[i].reason);
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
