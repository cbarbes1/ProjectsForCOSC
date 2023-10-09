#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
// define the file permissions
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP)
// define the buffer size 1
#define BUFFER_SIZE 1

// error printer
void err_sys(char *str)
{
	printf("%s", str);
	exit(1);
}

int main(int argc, char *argv[])
{
	int indes, outdes, offset; // vars to hold the descriptors and the offset
	char buffer[BUFFER_SIZE]; // create the buffer of size BUFFER_SIZE

	indes = open(argv[1], O_RDONLY); // open the file foo for reading only

	// if the file already exist exit the program since it could be an important file
	if(access(argv[2], F_OK) == 0)
		err_sys("Output File already exists delete the file or change the name");

	// open the file foorev for write only 
	outdes = open(argv[2], O_WRONLY|O_CREAT, FILE_MODE);

	// if the descriptors are errors then exit the program
	if(indes == -1 || outdes == -1)
		err_sys("File Open Error");

	// use lseek to find the end of the file if it fails then exit 
	if((offset=lseek(indes, 0, SEEK_END)) == -1)
		err_sys("Seek Error");

	// move the pointer to just before the end of the file
	offset-=2;

	while(offset>-1){// while offset is positive loop
		// lseek the next char in the file exit if needed
		if(lseek(indes, offset, SEEK_SET) == -1)
			err_sys("Seek Error");

		if(read(indes, &buffer, BUFFER_SIZE)<0)// read the next bit
			err_sys("read error");

		if(write(outdes, &buffer, BUFFER_SIZE)<0)// write the bit to the output
			err_sys("write error");

		offset--;// decrement the offset to shift closer to the beginning of the file
	}

	// end the line in the file since the endline wont exist in this case
	write(outdes, "\n", 2);

	//close the files
	close(indes);
	close(outdes);

	exit (0);
}
	
