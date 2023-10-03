#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
// define the permissions for the File mode
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP)
// set the buffer size
#define BUFFER_SIZE 1

// error printer
void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int main(int argc, char *argv[])
{
	int indes1, indes2, outdes, nread; // variables to hold descriptors 
	char buffer[BUFFER_SIZE];// create the buffer of size BUFFER_SIZE
	
	umask(0);// reset the mask

	// open the needed files for reading only
	indes1 = open(argv[1], O_RDONLY);
	indes2 = open(argv[2], O_RDONLY);

	if(access(argv[3], F_OK) ==0)
		chmod(argv[3], FILE_MODE);

	// open the file to append
	outdes = open(argv[3], O_WRONLY|O_CREAT, FILE_MODE);

	// if the descriptors are errors exit
	if(indes1 == -1 || indes2 == -1 || outdes == -1)
		err_sys("File Open Error");

	// lseek the end of the file and exit if fail
	if((lseek(outdes, 0, SEEK_END)) == -1)
		err_sys("Seek Error");

	// while 1 char to read write the char to the out descriptor
	while((nread=read(indes1, &buffer, BUFFER_SIZE)) == 1)
		if(write(outdes, &buffer, BUFFER_SIZE) < 0)// if write is less than zero the write failed
			err_sys("Write error");

	// if nread is less than 0 there was an error
	if(nread < 0)
		err_sys("read error");

	// while 1 char to read write the char to the out descriptor
	while((nread=read(indes2, &buffer, BUFFER_SIZE)) == 1)
		if(write(outdes, &buffer, BUFFER_SIZE) <0)// if write is less than zero the write failed
			err_sys("write error");

	// if nread is -1 than there was an error
	if(nread <0)
		err_sys("read error");

	// close the files
	close(indes1);
	close(indes2);
	close(outdes);

	exit (0);
}
	
