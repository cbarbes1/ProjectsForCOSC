#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

// parent killer handler for SIGUSR2
void pKiller(int sig){
	printf("Parent go Bye-Bye\n");
	exit(0);
}

// child killer handler for SIGUSR1
void cKiller(int sig){
	printf("Child Die now\n");
	kill(getppid(), SIGUSR2);
	exit(0);
}

int main()
{

	// set the signal for both SIGUSR1 and SIGUSR2
	signal(SIGUSR1, cKiller);
	signal(SIGUSR2, pKiller);

	// create pid vars and fork the first process
	pid_t pid = fork(), gpid;

	if(pid == 0){
		gpid = fork();// create the grandchild

		if(gpid == 0){// if in grandchild then print 10 times
			for(int i = 0; i<10; i++){
				printf("Grandchild Process\n");
				sleep(1);
			}
			kill(getppid(), SIGUSR1);
			if(getppid() == 1)
				exit(0);
		}else{
			while(1){
				printf("Child Process\n");
				sleep(1);
			}
		}
	}else {
		while(1){
			printf("Parent Process\n");
			sleep(1);
		}
	}

	exit(0);
}
