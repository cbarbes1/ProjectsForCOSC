#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
// define the file mode
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP)
// define the buffer size to 1
#define BUFFER_SIZE 1

// error printer
void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int main()
{
	int indes, outdes, offset; //create vars to hold the file descriptors and the offset
	char buffer[BUFFER_SIZE]; // create the buffer

	indes = open("foo", O_RDONLY); // open the file with read only

	// if the file exists exit
	if(access("foorev", F_OK) == 0)
		err_sys("The file already exists");

	outdes = open("foorev", O_WRONLY|O_CREAT, FILE_MODE);// open the file for write only

	// if the descriptors are error then exit the prog
	if(indes == -1 || outdes == -1)
		err_sys("File Open Error");

	// lseek the end of the file
	if((offset=lseek(indes, 0, SEEK_END)) == -1)
		err_sys("Seek Error");

	// set the offset to just before the end
	offset-=2;

	while(offset>-1){// if the offset reaches below zero done

		if(pread(indes, &buffer, BUFFER_SIZE, offset)<0)// pread does the lseek before reading
			err_sys("read error");

		if(write(outdes, &buffer, BUFFER_SIZE)<0)// write the byte to the file
			err_sys("write error");

		offset--;// decrement the offset
	}

	// write an endline since end is reached
	write(outdes, "\n", 1);

	// close the files
	close(indes);
	close(outdes);

	exit (0);
}
	
