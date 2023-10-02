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
	printf("%s", str);
	exit(1);
}

int main()
{
	// file descriptors, error check variable, and buffer
	int indes, outdes, nread;
	char buffer[BUFFER_SIZE];
	umask(0);
	indes = open("foo", O_RDONLY); // open the foo file for rd only
	outdes = open("clone2", O_RDWR | O_CREAT, FILE_MODE);// open the clone2 output file

	//check if the file open failed
	if(indes == -1 || outdes == -1)
		err_sys("File Open Error");
	
	// loop while chars left to read into the buffer
	while((nread=read(indes, &buffer, BUFFER_SIZE)) >= 1)
		write(outdes, &buffer, nread);

	// close the files
	close(indes);
	close(outdes);

	exit (0);
}
	
