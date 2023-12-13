#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFER_SIZE 1
int palind(int fd1, fd2);

int main(int argc, char *argv[])
{
	int des1, des2;
	pid_t pid;

	//pid = fork();

	//if(pid==0){
		if((des1 = open(argv[1], O_RDWR | O_CREAT, 0666))<0){
			printf("Open Error\n");
			exit(1);
		}

		int des1dup = dup(des1);

	d	if(palind(des1, des1dup) == 1){
			printf("The file contains a palindrome\n");
		}else{
			printf("The file does not contain a palindrome\n");
		}
	//}
	return 0;
}

int palind(int fd1, int fd2)
{
	int front = 0;
	int back = lseek(fd2, 0, SEEK_END);
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	int result = 0;
	while(back > front && result == 0){
		read(fd2, &buf2, BUFFER_SIZE);
		front = lseek(fd1, front, SEEK_SET);
		read(fd1, &buf1, BUFFER_SIZE);
		back = lseek(fd2, --back, SEEK_SET);
		if(*buf1 == *buf2)
			result = 1;
	}

	return result;
}
