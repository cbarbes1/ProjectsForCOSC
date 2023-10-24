#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int st_to_int(char *str)
{
	int result = 0;
	while(*str != '\0'){
		result = result*10 + (*str-'0');
		str++;
	}
	return result;
}

void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int main(int argc, char *argv[])
{
	// make sure there is sufficient arguments
	if(argc !=5)
		err_sys("Insufficient Arguments");
	
	pid_t pid;
	char *message;
	int n, ns, exit_code;

	// convert the strings to integers and save them in the appropriate place
	int nc = st_to_int(argv[1]);
	int np = st_to_int(argv[2]);
	int tc = st_to_int(argv[3]);
	int tp = st_to_int(argv[4]);


	// print prompt
	printf("fork program starting\n");
	// fork the process
	pid = fork();
	// check which process this is
	switch(pid)
	{
		case -1:
			perror("fork failed");
			exit(1);
		case 0:
			message = "This is the child";
			n=nc;
			ns=tc;
			exit_code = 2;
			break;
		default:
			message = "This is the parent";
			n = np;
			ns=tp;
			exit_code = 0;
			break;
	}

	if(pid !=0) { // if in the parent perform the wait
		int stat_val;
		pid_t child_pid;

		// wait for the child to complete
		child_pid = wait(&stat_val);

		// print the pid 
		printf("Child has finished: PID = %d\n", child_pid);
		if(WIFEXITED(stat_val))
			printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
		else 
			printf("Child terminated abnormally\n");
	}

	//print the messages
	for(; n>0; n--) {
		puts(message);
		sleep(ns);
	}

	exit(exit_code);
}
