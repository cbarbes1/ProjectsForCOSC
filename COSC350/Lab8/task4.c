#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#define MAXLINE 256

void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void parentKill(int signo)
{
	printf("EOF\n");
	exit(0);
}

int main()
{
	pid_t pid;
	int filedes[2];
	int size, n, int1, int2;
	char sline[MAXLINE], rline[MAXLINE];

	if(pipe(filedes) < 0)
		err_sys("pipe failed");
	if( (pid = fork()) < 0)
		err_sys("fork error");
	else if(pid > 0){
		signal(SIGCHLD, parentKill);
		close(filedes[0]);
		printf("submit two integer\n");
		while((size=read(STDIN_FILENO, sline, MAXLINE))>0)
		{
			write(filedes[1], sline, size);
			printf("submit two integers\n");
		}
	}
	else
	{
		close(filedes[1]);
		while((n=read(filedes[0], rline, MAXLINE))>0)
		{
			if(!strcmp(rline, "EOF\n"))
				_exit(0);
			if(sscanf(rline, "%d%d", &int1, &int2) == 2)
			{
				sprintf(rline, "%d\n", int1 + int2);
				n = strlen(rline);
				if(write(STDOUT_FILENO, rline, n) != n)
					err_sys("write error");
			}else
			{
				if(write(STDOUT_FILENO, "invalid args\n", 13) != 13)
					err_sys("write error");
			}
		}
	} 

	return 0;
}
