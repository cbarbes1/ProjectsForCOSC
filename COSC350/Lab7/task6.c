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
			int i = 1;
			pid_t cppid = getppid();
			while(1){// loop until parent is different which means parent died
				printf("Grandchild Process\n");
				i++;
				//sleep(1);
				if(i==10){
					kill(getppid(), SIGUSR1);
				}
				if(getppid() != cppid)
					abort();
			}
		}else{
			while(1){ // attemp to print forever child process
				printf("Child Process\n");
				//sleep(1);
			}
		}
	}else {
		while(1){// attempt to print forever parent process
			printf("Parent Process\n");
			//sleep(1);
		}
	}

	exit(0);
}
