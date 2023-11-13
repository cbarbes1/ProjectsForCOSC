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
		
		while(1)
		{ // run forever until parent exits itself
			printf("submit two integer, enter EOF to end: \n");
			scanf("%s", &sline);
			if(strcmp(sline, "EOF")==0){ // compare the input and see if it is an EOF
				close(filedes[1]); // close the desciptor to cause EOF in child
				exit(0); // exit the parent
			}	
			scanf("%s", &tmp);	
			if(strcmp(tmp, "EOF")==0){ // compare the input and see if it is an EOF
				close(filedes[1]); // close the descriptor to cause EOF
				exit(0);// exit the prog
			}
			// print the 2 vars to the line string
			sprintf(sline, "%s %s", sline, tmp);
			// if error exit but write the line to the descriptor for the child
			if(write(filedes[1], sline, MAXLINE) == -1)
				err_sys("Failed to write to child");
		}
		// close the filedes
		close(filedes[1]);
	}
	else
	{ // child process
	  // // close the unused end of the pipe
		close(filedes[1]);
		//
		char str1[256], str2[256];
		while(read(filedes[0], &rline, MAXLINE) > 0)
		{ // read until the EOF is reached in the file
			if(sscanf(rline, "%s %s", &str1, &str2) ==2)
			{ // scan the string for 2 seperate strings seperated by a space
			  // to int both
				int1 = atoi(str1); 
				int2 = atoi(str2);
				// print result
				sprintf(rline, "%d\n", int1 + int2);
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
