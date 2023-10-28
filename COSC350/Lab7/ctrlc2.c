#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig)
{
	printf("OUCH! - I got signal %d\n", sig);
}

int main()
{
	struct sigaction act;

	act.sa_handler = ouch;
	sigemptyset(&act.sa_mask);
	// a change from 0 to SA_RESETHAND results in the SIGINT still able to kill the process
	act.sa_flags = SA_RESETHAND;

	sigaction(SIGINT, &act, 0);

	while(1){
		printf("Hello World!\n");
		sleep(1);
	}
}
