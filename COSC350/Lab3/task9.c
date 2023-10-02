#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

void err_sys(char *str)
{
	printf("%s", str);
	exit(1);
}
int main(int argc, char *argv[])
{
	if(argc!=3){
		printf("%s", "Not enough arguments or too many!");
		exit(-1);
	}

	int indes, outdes;
	char buffer;
	int result = 0;

	indes = open(argv[1], O_RDONLY); 
	outdes = open(argv[2], O_RDWR | O_CREAT, FILE_MODE);

	if(indes == -1 || outdes == -1)
		err_sys("File Open Error");
	if(dup2(outdes, STDOUT_FILENO) == -1){
		printf("%s", "Failed to redirect stdout");
		exit(1);
	}	

	while(read(indes, &buffer, 1) == 1){
		if(result >= 32 && result <= 126){
			printf("%c", result);
			result = 0;
		}
		result = result*10 + (buffer - '0');
	}

	printf("\n");

	dup2(STDOUT_FILENO, outdes);

	close(indes);
	close(outdes);

	exit (0);
}
	
