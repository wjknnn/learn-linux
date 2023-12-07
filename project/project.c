#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_STR 1024

struct swInfo {
	char argv[3][MAX_STR];
	char name[MAX_STR];
	char time[MAX_STR];
	char *reason;
	int cnt;
}p[10];

int PROCESS_NUM;
int flag;
int statusNum;

void readFileList(FILE *fp);		// SW Block 정보 가져오기
void SwInit(FILE *fp, struct tm *t);
void SwCheck(int index);
void countProcess();
void handler(int signum);		// signal handler
char *rtrim(const char *s);
char *ltrim(const char *s);
char *trim(const char *s);		// 공백 제거

int main() {
	FILE *fp;
	time_t timer;
	struct tm *t;
	timer = time(NULL);
	t = localtime(&timer);

	readFileList(fp);
	SwInit(fp, t);
	countProcess();

	// signal setting
	struct sigaction act;
	sigset_t set;
	sigfillset(&(act.sa_mask));
	act.sa_handler = handler;
	sigaction(SIGCHLD, &act, NULL);

	int i;
	int pnum = 0;
	pid_t pid[PROCESS_NUM];

	// process 생성
	pid[0] = fork();
	for(i = 1; i < PROCESS_NUM; i++) {
		if(pid[i - 1] > 0) {
			pid[i] = fork();
			sleep(1);
		}
	}
	
	//parent process check
	for(i = 0; i < PROCESS_NUM; i++) {
		if(pid[i] > 0) pnum++;
		else break;
	}

	if(pnum == PROCESS_NUM) {
		while(1) {
			if(flag == 1) {
				sleep(1);
				timer = time(NULL);
				t = localtime(&timer);
				printf("handler is worked [%d:%d:%d]\n", t->tm_hour, t->tm_min, t->tm_sec);
				break;
			}
		}
	}
}

void handler(int signum) {
	int pid;
	int status;
	while(pid = waitpid(-1, &status, WNOHANG) > 0) {
		statusNum = status;
		flag = 1;
	}
}

void readFileList(FILE *fp) {
	fp = fopen("./SwInfo.txt", "r");
	char swStr[MAX_STR];
	int swNum = 0;

	while(fgets(swStr, MAX_STR, fp)) { // 한 줄씩 받아오기
		int n = 0;
		char *result;
		swStr[strlen(swStr) - 1] = '\0';	// 개행문자 제거
		result = strtok(swStr, ";");		// 토큰 파싱
		strcpy(p[swNum].name, trim(result));	// name 저장
		printf("\n┌──────%3s─────┐\n", p[swNum].name);
		
		while(result != NULL && n < 3) {
			char *result;
			result = strtok(NULL, ";");
			if(result != NULL) {
				strcpy(p[swNum].argv[n], trim(result)); //argv 저장
				printf("│%14s│\n", p[swNum].argv[n]);
			}
			else break;
			n++;
		}
		printf("└──────────────┘\n");
		swNum++;
	}
	printf("\n\n");
	fclose(fp);
}

void SwInit(FILE *fp, struct tm *t) {
	fp = fopen("./log/restart.txt", "w");

	for(int i = 0; strlen(p[i].name); i++) {	
		sprintf(p[i].time, "%04d.%02d.%02d. %02d:%02d:%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
		p[i].reason = "Init";
		p[i].cnt++;
		fprintf(fp, "%s\t%d\t%s\t%s\n", p[i].name, p[i].cnt, p[i].time, p[i].reason);
		SwCheck(i);
	}
	fclose(fp);
}

void SwCheck(int index) {
	printf("%s\t%d\t%s\t%s\n", p[index].name, p[index].cnt, p[index].time, p[index].reason);
}

void countProcess() {
	for(int i = 0; i < 10; i++) {
		if(p[i].cnt > 0) PROCESS_NUM++;
		else break;
	}
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
