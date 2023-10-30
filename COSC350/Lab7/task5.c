#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void reset(int sig)
{
	return;
}

int main()
{
	// create signal set vars
	sigset_t new_set, store;

	// add ^c to the set and ^\ to the set
	sigaddset(&new_set, SIGINT);
	sigaddset(&new_set, SIGQUIT);
	
	// set the process mask
	sigprocmask(SIG_BLOCK, &new_set, &store);

	// loop 1 to 5 printing
	for(int i = 1; i<=5; i++){
		printf("%d \n", i);
		sleep(1);
	}

	signal(SIGQUIT, &reset);
	// set the set to just the ^C signal
	sigdelset(&new_set, SIGINT);
	// set the mask again
	sigprocmask(SIG_UNBLOCK, &new_set, &store);

	signal(SIGQUIT, SIG_DFL);

	// loop through 1 to 5 printing
	for(int i = 1; i<=5; i++){
		printf("%d \n", i);
		sleep(1);
	}

	// reset the mask
	sigprocmask(SIG_SETMASK, &store, NULL);

	return 0;

}
