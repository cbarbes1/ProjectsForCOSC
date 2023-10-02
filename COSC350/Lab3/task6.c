#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP)
#define BUFFER_SIZE 1

void err_sys(char *str)
{
	printf("%s", str);
	exit(1);
}

int main()
{
	int indes, outdes, offset;
	int count = 0;
	char buffer[BUFFER_SIZE];

	indes = open("foo", O_RDONLY);
	outdes = open("foorev", O_RDWR|O_CREAT, FILE_MODE);

	if(indes == -1 || outdes == -1)
		err_sys("File Open Error");

	if((offset=lseek(indes, 0, SEEK_END)) == -1)
		err_sys("Seek Error");

	offset-=2;

	while(offset>-1){

		pread(indes, &buffer, BUFFER_SIZE, offset);

		write(outdes, &buffer, BUFFER_SIZE);
		
		offset--;
	}

	write(outdes, "\n", 2);

	close(indes);
	close(outdes);

	exit (0);
}
	
