#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int palind(int fd1, int fd2)
{
	int offset1 = 0, offset2 = 0;
	int endOfFile = 0;
	char buf1, buf2;

	// read file until read chars are not equal
	if(read(fd1, &buf1, 1) == -1)
		err_sys("Read Error");

	if((offset2=lseek(fd2, -2, SEEK_END)) == -1)
		err_sys("Seek Error");

	endOfFile = offset2;

	if(read(fd2, &buf2, 1) == -1)
		err_sys("Read Error");
	
	// loop through until either the chars dont equal or the offset1 isnt at the end
	while(buf1 == buf2 && offset1 != (endOfFile) ){
		// set the offset to the offset +1 and seek that position
		if(lseek(fd1, ++offset1, SEEK_SET) == -1)
			err_sys("Seek Error1"); 
		// read next char
		if(read(fd1, &buf1, 1) == -1)
			err_sys("Read Error");

		// seek the second offset-1 and seek that position
		if(lseek(fd2, --offset2, SEEK_SET) ==-1)
			err_sys("Seek Error2");

		// read next char
		if(read(fd2, &buf2, 1) == -1)
			err_sys("Read Error");
	}

	// if the chars were not the same return 0
	if(buf1 != buf2){
		return 0;
	}
	else{// if chars were equal return 1
		return 1;
	}
}

int main(int argc, char *argv[])
{
	// check that valid arguments were sent
	if(argc != 2)
		err_sys("No command line arguments passed!");

	int indes, copyDes;
	
	// open the file 
	if((indes=open(argv[1], O_RDONLY)) ==-1)
	       err_sys("Open file error");

	// duplicate the desriptor
	if((copyDes=dup(indes)) == -1)
		err_sys("Duplication error");
	
	// if its a palindrome tell the user is palindrome
	if(palind(indes, copyDes)){
		printf("File containes a palindrome\n");
	}
	else{
		printf("File does not contain a palindrome\n");
	}

	// close the files
	close(indes);
	close(copyDes);

	return 0;
}	
