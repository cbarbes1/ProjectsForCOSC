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
	umask(0);
	int des = open("foo", O_RDWR | O_CREAT, 0777);
	// create a child process
	pid_t pid = fork();
	int childStatus;
	// reset the mask

	if(pid == 0){ // child process
		// write the message to the file
		write(des, "Hi, Mom\n", MESSAGE_SIZE);
		lseek(des, 0, SEEK_SET);
		// exit the child
		_exit(0);
	}
	else { // parent process
	       // wait for the child to complete
		wait(&childStatus);
		// create a buffer of the size of the message
		char buf[MESSAGE_SIZE];
		//read the buffer in
		read(des, &buf, MESSAGE_SIZE);
		// print the message
		printf("My son said %s", buf);
		close(des);
	}


	return 0;
}
