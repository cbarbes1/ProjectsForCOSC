#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int main(int argc, char *argv[])
{
	if(argc != 6)
		err_sys("Insufficient Arguments");

	int indes1, letter, nums, palin, copy, nread;
	char buf;

	if((indes1=open(argv[1], O_RDONLY)) == -1)
		err_sys("Open error");
	if((letter=open(argv[2], O_RDWR | O_CREAT, 0666))==-1)
		err_sys("Open error");
	if((nums=open(argv[3], O_RDWR | O_CREAT, 0666))==-1)
		err_sys("Open Error");
	if((palin=open(argv[4], O_RDWR | O_CREAT, 0666))==-1)
		err_sys("Open Error");
	if((copy=open(argv[5], O_RDWR | O_CREAT, 0666))==-1)
		err_sys("Open Error");

	char space = ' ';
	while((nread=read(indes1, &buf, 1)) >0){
		if(buf >= '0' && buf <= '9'){
			if(write(nums, &buf, nread)==-1)
				err_sys("Write error");
			if(write(letter, &space, nread)==-1)
				err_sys("Write error");
		}
		else if(buf >= 'a' && buf <='z'){
			if(write(nums, &space, nread)==-1)
				err_sys("Write Error");
			if(write(letter, &buf, nread)==-1)
				err_sys("Write error");
			if(write(palin, &buf, nread)==-1)
				err_sys("Write Error");
		}
		else if(buf == ' ' || buf == '\n'){
			if(write(nums, &buf, nread) == -1)
				err_sys("Write error");
			if(write(letter, &buf, nread)==-1)
				err_sys("Write Error");
			if(buf == '\n')
				if(write(palin, &buf, nread) ==-1)
					err_sys("Write Error");
		}
	}

	// seek the end
	int offset1 = lseek(palin, -1, SEEK_END);
	char buf2;

	// read the last byte
	if(read(palin, &buf, 1)==-1)
		err_sys("Read Error");
	// seek the front
	int offset2 = lseek(palin, 0, SEEK_SET);
	// read the first byte
	if(read(palin, &buf2, 1)==-1)
		err_sys("Read Error");
	// run untile there is a non matching char or you have surpassed the center
	while(buf==buf2 && offset1<offset2){
		lseek(palin, --offset1, SEEK_SET);
		if(read(palin, &buf, 1)==-1)
			err_sys("Read Error");
		lseek(palin, ++offset2, SEEK_SET);
		if(read(palin, &buf2, 1)==-1)
			err_sys("Read Error");
	}

	// check if buffers are in fact the same
	if(buf!=buf2)
		printf("Not a palindrome");
	else 
		printf("is palindrome");

	lseek(nums, 0, SEEK_SET);
	lseek(letter, 0, SEEK_SET);
	while((nread=read(nums, &buf, 1))>0){
		if(read(letter, &buf2, 1)==-1)
			err_sys("Error in read");
		if(buf==' '||buf2=='\n'){
			if(write(copy, &buf2, 1)==-1)
				err_sys("Error in read");
		}
		else if(buf2==' '||buf2=='\n'){
			if(write(copy, &buf, 1)==-1)
				err_sys("Error in read");
		}
	}
	close(letter);
	close(indes1);
	close(nums);
	close(copy);
	close(palin);
	return 0;

}
