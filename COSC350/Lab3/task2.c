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
	printf("%s", str);
	exit(1);
}

int main()
{
	// file descriptors and buffer 
	int indes, outdes;
	char buffer;
	umask(0);
	indes = open("foo", O_RDONLY);  // open the input file for read only
	outdes = open("clone1", O_RDWR | O_CREAT, FILE_MODE);// open output file rw-rw-rw-

	// check if either open functions failed
	if(indes == -1 || outdes == -1)
		err_sys("File Open Error");

	// loop through grabbing each byte and storing it in the output file
	while(read(indes, &buffer, 1) == 1)
		write(outdes, &buffer, 1);

	close(indes); // close the file
	close(outdes); // close the file

	exit (0);
}
	
