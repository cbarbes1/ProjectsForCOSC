#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define BUFFER_SIZE 1

void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

// simple function to check if a character is a digit
int isDigit(char buf)
{
	int result = 0;
	// if char is a number then return true
	if(buf <= '9' && buf >= '0')
		result = 1;
	// if char is not a number then return false
	return result;
}

int main(int argc, char *argv[])
{
	if(argc !=2)
		err_sys("Insufficient Arguments");

	umask(0000);
	// open the file given
	int indes = open(argv[1], O_RDONLY);
	//create buffer var and 2 output descriptors
	char buf;
	int outdes1, outdes2, offset = 0;

	// check that the input file opened correctly
	if(indes == -1)
		err_sys("File open error");

	pid_t pid;

	// fork the process
	pid = fork();

	// if child then open the child file
	if(pid == 0)
		if((outdes2=open("child.txt", O_WRONLY | O_CREAT, 0777)) < 0)
			err_sys("open fail");
	// if parent then open parent file
	if(pid != 0)
		if((outdes1=open("parent.txt", O_WRONLY | O_CREAT, 0777)) < 0)
			err_sys("open fail");

	lseek(indes, offset, SEEK_SET);
	// while a char is read loop through the file and pread the current char to avoid race condition
	while(read(indes, &buf, BUFFER_SIZE)>0){
		if(pid == 0){ // if currently on the child then take in the non numeric chars
			if(!isDigit(buf) || buf == '\n')
				write(outdes2, &buf, 1);
			lseek(indes, offset, SEEK_SET);
		}else { // if parent take in numeric char
			if(isDigit(buf) || buf == '\n')
				write(outdes1, &buf, 1);
			lseek(indes, offset, SEEK_SET);
		}
		offset++;		
	}


	close(indes);
	close(outdes1);
	close(outdes2);

	return 0;
}
