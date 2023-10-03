#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
// define the file creation umask
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

// create error message printer
void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int main()
{
	// file descriptors and buffer 
	int indes, outdes, nbyte;
	char buffer;

	umask(0);// reset the mask

	indes = open("foo", O_RDONLY);  // open the input file for read only
	
	// check and make sure the file doesn't exist
	if(access("clone1", F_OK) == 0)
		err_sys("File clone1 already exists");

	outdes = open("clone1", O_RDWR | O_CREAT, FILE_MODE);// open output file rw-rw-rw-

	// check if either open functions failed
	if(indes == -1 || outdes == -1)
		err_sys("File Open Error");

	// loop through grabbing each byte and storing it in the output file
	while((nbyte=read(indes, &buffer, 1)) == 1)
		if(write(outdes, &buffer, 1) <1)// if write fails then exit with errors
			err_sys("write error");
	// if the number of bytes is less than zero there was an error reading
	if(nbyte < 0)
		err_sys("read error");

	close(indes); // close the file
	close(outdes); // close the file

	exit (0);
}
	
