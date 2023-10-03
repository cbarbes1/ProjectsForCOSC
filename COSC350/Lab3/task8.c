#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
// define the file privileges
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

// error printer function
void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int main(int argc, char *argv[])
{
	// if arguments are not exactly 3 terminate the program
	if(argc!=3){
		err_sys("Not enough arguments or too many!");
	}

	umask(0); // reset the mask

	int indes, outdes, nread;// vars to hold the file descriptors
	char buffer; // create the buffer

	indes = open(argv[1], O_RDONLY); // open the file for read only
	
	// if the file in the argument already exists then exit
	if(access(argv[2], F_OK) ==0)
		err_sys("Output File already exists");

	outdes = open(argv[2], O_WRONLY | O_CREAT, FILE_MODE);// open the file for write only

	//if the file descriptors have an error exit the program
	if(indes == -1 || outdes == -1)
		err_sys("File Open Error");

	// dup2 change the std out descriptor to outdes so that it will printf to the file
	if(dup2(outdes, STDOUT_FILENO) == -1){ // if fail exit with errors
		err_sys("Failed to redirect stdout");
	}	

	// while the read call has 1 char return continue
	while((nread=read(indes, &buffer, 1)) == 1){
		// if the buffer is an end line printf the endline 
		if(buffer == '\n')
			printf("\n");
		else 
			printf("%d", buffer);
	}

	// if trouble reading return error
	if(nread<0)
		err_sys("read error");

	// reset the descriptor
	dup2(STDOUT_FILENO, outdes);
	//close the file
	close(indes);
	close(outdes);

	exit (0);
}
	
