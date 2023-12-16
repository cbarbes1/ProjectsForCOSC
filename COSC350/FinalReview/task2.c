#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFER_SIZE 1
int palind(int fd1, int fd2);

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

		if(palind(des1, des1dup) == 1){
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
<<<<<<< HEAD
	int back = lseek(fd2, -1, SEEK_END);
	char buf1, buf2;
	int result = 1;
	while(back > front){
		front = lseek(fd1, front++, SEEK_SET);
		read(fd1, &buf1, BUFFER_SIZE);
		back = lseek(fd2, back--, SEEK_SET);
		read(fd2, &buf2, BUFFER_SIZE);
		if(buf1 != buf2 && buf1 != '\n' && buf2 != '\n'){
			result = 0;
		}
=======
	int back = lseek(fd2, -2, SEEK_END);
	char buf1, buf2;
	int result = 0;
	while(back > front){
		read(fd2, &buf2, BUFFER_SIZE);
		front = lseek(fd1, ++front, SEEK_SET);
		read(fd1, &buf1, BUFFER_SIZE);
		back = lseek(fd2, --back, SEEK_SET);
		if(buf1 == buf2 && buf1 != '\n' && buf2 != '\n')
			result = 1;
		else if(buf1 != buf2 && buf1 != '\n' && buf2 != '\n')
			result = 0;
>>>>>>> 1f586b516fad5aa5c09cac3b48915445339dd8d3
	}

	return result;
}
