#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1

// create an error printing function
void err_sys(char *str)
{
	printf("%s", str);
	exit(1); // exit
}

int main()
{
	int nbyte; // error check variable
	char buffer[BUFFER_SIZE];// buffer of defined size

	// loop while the read does not become less than 1 
	while((nbyte=read(STDIN_FILENO, buffer, BUFFER_SIZE)) == 1)
		if(write(STDOUT_FILENO, buffer, nbyte) != nbyte)// check for fail
			err_sys("Write Error");

	// check if the read ended in an error
	if(nbyte <0)
		err_sys("read error");

	exit (0); // exit prog
}
