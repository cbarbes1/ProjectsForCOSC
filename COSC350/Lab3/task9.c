#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

// error printer function
void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int main(int argc, char *argv[])
{
	// if there is less than 3 command line arguments exit with errors
	if(argc!=3){
		err_sys("Not enough arguments or too many!");
	}

	umask(0);// reset the mask

	int indes, outdes, nread;// vars for the file descriptors
	char buffer;// buffer for the chars
	int result = 0;// result var for finding the char value

	// open the files
	indes = open(argv[1], O_RDONLY); 

	// if the file already exists then exit with errors
	if(access(argv[2], F_OK) == 0)
		err_sys("The file already exists");
	// open the file
	outdes = open(argv[2], O_WRONLY | O_CREAT, FILE_MODE);

	// if the descriptor contains an error
	if(indes == -1 || outdes == -1)
		err_sys("File Open Error");
	// dup2 to change the descriptor of stdout to the output file
	if(dup2(outdes, STDOUT_FILENO) == -1){
		err_sys("Failed to redirect stdout");
	}	

	// while 1 char in buffer read in chars
	while((nread=read(indes, &buffer, 1)) == 1){
		if(buffer == '\n'){ // if endline end the line
			printf("\n");
		}
		else if(buffer == '\t'){
			printf("\t");
		}
		else{
			result = result*10 + (buffer - '0');
		}	
		if(result >= 32 && result <= 126){// if the result is a char then print it to the file
			printf("%c", result);
			result = 0;
		}
	}

	// if read fail exit with errors
	if(nread<0)
		err_sys("Read Error");

	// reset the descriptor for standard out
	dup2(STDOUT_FILENO, outdes);

	// close the file
	close(indes);
	close(outdes);

	exit (0);
}
	
