#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MESSAGE_SIZE 8
int main()
{
	// create a child process
	pid_t pid = fork();
	int childStatus;
	// reset the mask
	umask(0);

	if(pid == 0){ // child process
		// open the file foo
		int outdes = open("foo", O_WRONLY | O_CREAT, 0777);
		// write the message to the file
		write(outdes, "Hi, Mom\n", MESSAGE_SIZE);
		// close the file
		close(outdes);
		// exit the child
		_exit(0);
	}
	else { // parent process
	       // wait for the child to complete
		wait(&childStatus);
		// open the file foo for input
		int indes = open("foo", O_RDONLY);
		// create a buffer of the size of the message
		char buf[MESSAGE_SIZE];
		//read the buffer in
		read(indes, &buf, MESSAGE_SIZE);
		// print the message
		printf("My son said %s", buf);
		// close the file
		close(indes);
	}
	return 0;
}
