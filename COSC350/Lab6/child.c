#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int main(int argc, char *argv[])
{
	// make sure there is sufficient arguments
	if(argc !=4)
		err_sys("Insufficient Arguments");
	// convert the strings to integers and save them in the appropriate place
	int nc = atoi(argv[2]);
	int tc = atoi(argv[3]);
	
	// print the messages
	for(; nc>0; nc--) {
		printf("%s  PID = %d\n", argv[1], getpid());
		sleep(tc);
	}

	exit(37);
}
