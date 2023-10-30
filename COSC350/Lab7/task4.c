#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

static int first_fired = 0;
static int second_fired = 0;

void sig_handler(int sig){
	if(sig == SIGUSR1){
		printf("Hi Honey! Anything Wrong?\n");
		first_fired = 1;
	}else if(sig == SIGUSR2){
		printf("Do you make trouble again?\n");
		second_fired = 1;
	}
}

int main()
{
	// set up the signals to be handled
	signal(SIGUSR1, &sig_handler);
	signal(SIGUSR2, &sig_handler);

	// create the pid vars
	pid_t pid, pidc;

	// fork the process
	pid = fork();

	// if in the parent then fork the second
	if(pid != 0){ // parent process
		pidc = fork();
	}

	if(pid == 0){ // if child send signal to parent and then die
		kill(getppid(), SIGUSR1); // send signal to parent
		exit(0); // exit the prog
	}else if(pidc == 0){
		kill(getppid(), SIGUSR2);
		exit(0);
	}else {
		waitpid(pid, 0, 0); // wait for the child
		waitpid(pidc, 0, 0); // wait for the second child
	}

	return 0;
}
