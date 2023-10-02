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
	int indes1, indes2, outdes, offset;
	char buffer[BUFFER_SIZE];

	indes1 = open("foo", O_RDONLY);
	indes2 = open("foo1", O_RDONLY);
	outdes = open("foo12", O_RDWR|O_APPEND|O_CREAT, FILE_MODE);

	if(indes1 == -1 || indes2 == -1 || outdes == -1)
		err_sys("File Open Error");

	if((lseek(outdes, 0, SEEK_END)) == -1)
		err_sys("Seek Error");

	while(read(indes1, &buffer, BUFFER_SIZE) == 1)
		write(outdes, &buffer, BUFFER_SIZE);

	while(read(indes2, &buffer, BUFFER_SIZE) == 1)
		write(outdes, &buffer, BUFFER_SIZE);

	close(indes1);
	close(indes2);
	close(outdes);

	exit (0);
}
	
