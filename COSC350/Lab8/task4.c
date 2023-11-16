#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#define MAXLINE 256

// error return printer
void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int main()
{
	pid_t pid; // fork value
	int filedes[2]; // pipe descriptors
	int size, n, int1, int2; // save variables
	char sline[MAXLINE], rline[MAXLINE]; // string vars

	// if the pipe fails then exit
	if(pipe(filedes) < 0)
		err_sys("pipe failed");
	// if the pid is error exit
	if( (pid = fork()) < 0)
		err_sys("fork error");
	else if(pid > 0){ // parent process
		close(filedes[0]);
		char tmp[256];
		printf("submit two integers\n");
		while(fgets(sline, MAXLINE, stdin)!=NULL)
		{ // run forever until parent exits itself
			printf("submit two integers\n");
			// if error exit but write the line to the descriptor for the child
			if(write(filedes[1], sline, strlen(sline)) != strlen(sline))
				err_sys("Failed to write to child");
		}
	}
	else
	{ // child process
	  // // close the unused end of the pipe
		close(filedes[1]);
		//
		while(read(filedes[0], &rline, MAXLINE) > 0)
		{ // read until the EOF is reached in the file
			if(sscanf(rline, "%d%d", &int1, &int2) ==2)
			{ // scan the string for 2 seperate strings seperated by a space
			  // to int both
				// print result
				sprintf(rline, "Sum: %d\n", int1 + int2);
				// write to the std out and find out if error
				n = strlen(rline);
				if(write(STDOUT_FILENO, rline, n) != n)
					err_sys("write error");
			}else
			{
				// if error in text exit with errors
				if(write(STDOUT_FILENO, "invalid args\n", 13) != 13)
					err_sys("write error");
			}
		}
		_exit(0);
	} 

	return 0;
}
