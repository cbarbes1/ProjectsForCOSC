#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
// define the file mode
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP)
#define BUFFER_SIZE 32 // define a buffer size

// error printing function and exit 
void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int main()
{
	// file descriptors, error check variable, and buffer
	int indes, outdes, nread;
	char buffer[BUFFER_SIZE];

	umask(0);// reset the umask

	indes = open("foo", O_RDONLY); // open the foo file for rd
	
	if(access("clone2", F_OK) == 0)
		err_sys("The file clone2 already exists");

	outdes = open("clone2", O_RDWR | O_CREAT, FILE_MODE);// open the clone2 output file

	//check if the file open failed
	if(indes == -1 || outdes == -1)
		err_sys("File Open Error");
	
	// loop while chars left to read into the buffer
	while((nread=read(indes, &buffer, BUFFER_SIZE)) >= 1)
		if(write(outdes, &buffer, nread) <1)// if write fails exit with errors
			err_sys("Write error");

	// if nread is less than 0 there was an error
	if(nread <0)
		err_sys("read error");

	// close the files
	close(indes);
	close(outdes);

	exit (0);
}
	
