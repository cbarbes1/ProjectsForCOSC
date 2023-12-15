#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

void handler(int signo){
	return;
}

int main()
{
	int fd[2];
	int des;
	umask(0);
	des = open("foo1", O_RDWR | O_CREAT, 0666);

	pipe(fd);
	pid_t pid = fork();

	if(pid == 0){
		char buf[256];
		close(fd[1]);
		write(des, "Hi, Mom", 7);
		kill(getppid(), SIGUSR1);
		int sz= read(fd[0], &buf, 256);
		buf[sz] = '\0';
		printf("My mom said %s\n", buf);

	}else if(pid > 0){
		signal(SIGUSR1, handler);
		char buf[16];
		buf[17] = '\0';
		close(fd[0]);
		int sz = read(des, &buf, 16);
		printf("My son said %s\n", buf);
		write(fd[1], "what do you want", 16);
	
	}
	close(des);
	exit(0);
}
