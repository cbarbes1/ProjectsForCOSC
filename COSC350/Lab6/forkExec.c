#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	int exit_code;

	// convert the strings to integers and save them in the appropriate place
	int n = atoi(argv[2]);
	int t = atoi(argv[4]);


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
			if((exit_code = execle("child", "child.c", "This is the child" , argv[1], argv[3], NULL))<0)
				err_sys("execl ERROR");
			break;
		default:
			message = "This is the parent";
			exit_code = 0;
			break;
	}

	if(pid != 0){
		// print the messages
		for(; n>0; n--) {
			printf("%s PID = %d\n", message, pid);
			sleep(t);
		}

		int stat_val;
		pid_t child_pid;

		child_pid = wait(&stat_val);

		printf("Child has finished: PID = %d\n", child_pid);
		if(WIFEXITED(stat_val))
			printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
		else 
			printf("Child terminated abnormally\n");
	}



	exit(exit_code);
}
