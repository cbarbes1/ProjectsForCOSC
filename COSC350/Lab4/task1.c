/*
 * Author: Cole Barbes
 * Creation date: 10/7/23
 * Last edited: 10/7/23
 * Purpose: given 5 file names 1 being the input file divide up the input into each type of char
 */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

// simple error printer
void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int main(int argc, char *argv[])
{
	if(argv[1] == "-h"){
		printf("The structure of the arguments on the command line must be\n");
		printf(" executable inputFile alphaOutput numericOutput copyOutput\n");
	}
	// check to make sure accurate number of arguments to operate the program
	if(argc != 6)
		err_sys("No Arguments on command line");

	// variables for needed values
	int indes, alpha, num, other, copy, nread, nread1, nread2;
	char buf, abuf, nbuf, obuf;

	// open the input file for read only
	if((indes=open(argv[1], O_RDONLY)) == -1)
		err_sys("File Open Error!");

	// open the alphabetic output file
	if((alpha=open(argv[2], O_RDWR | O_CREAT, 0666)) == -1)
		err_sys("File Open Error!");

	// open the numeric output file
	if((num=open(argv[3], O_RDWR | O_CREAT, 0666)) == -1)
		err_sys("File Open Error!");

	// open the other output file
	if((other=open(argv[4], O_RDWR | O_CREAT, 0666)) == -1)
		err_sys("File Open Error!");

	// open the copy file to copy 3 output files 
	if((copy=open(argv[5], O_WRONLY | O_CREAT, 0666)) == -1)
		err_sys("File Open Error!");


	printf("%d\n",  copy);
	// loop through the input file reading needed chars to each file
	while((nread=read(indes, &buf, 1)) >0){
		//each if sets the needed chars into the buffers and places blank space into the other buffers
		if((buf <= 122 && buf >= 97)||(buf <= 90 && buf >= 65)){
			abuf = buf;
			nbuf = obuf = ' ';
		}
		else if(buf <= 57 && buf >= 48){
			nbuf = buf;
			abuf = obuf = ' ';
		}
		else if(buf == '\n' || buf == '\t' || buf == ' '){
			abuf = nbuf = obuf = buf;
		}
		else{
			obuf = buf;
			abuf = nbuf = ' ';
		}
		//
		// write to each file its given buffer
		if(write(alpha, &abuf, nread) == -1)
			err_sys("Write Error");
		if(write(num, &nbuf, nread) == -1)
			err_sys("Write Error");
		if(write(other, &obuf, nread) == -1)
			err_sys("Write Error");
		//
	}

	// check if there was a read error
	if(nread < 0)
		err_sys("Read Error");

	// return the pointer to the front of the files
	lseek(alpha, 0, SEEK_SET);
	lseek(num, 0, SEEK_SET);
	lseek(other, 0, SEEK_SET);

	// loop through the created files and write the needed char to the copy 
	while((nread=read(alpha, &abuf, 1)) > 0){ 
		nread1=read(num, &nbuf, 1); 
		nread2=read(other, &obuf, 1);
		// check if the alphabetic char is a space then write what is there in the other files
		// or write the char in the alphabetic file
		if(abuf == ' '){
			if(nbuf == ' ' && obuf == ' '){
				if(write(copy, &nbuf, nread1) == -1)
					err_sys("Write Error on number");
			}
			else if(nbuf >= 48 && nbuf <= 57){
				if(write(copy, &nbuf, nread1) == -1)
					err_sys("Write Error on number");
			}
			else{
				if(write(copy, &obuf, nread2) == -1)
					err_sys("Write Error on other");
			}
		}
		else {
			if(write(copy, &abuf, nread) == -1)
				err_sys("Write Error on alphabetic char");
		}
	}

	if(nread<0||nread1<0||nread2<0)
		err_sys("read error");

	// close all the files
	close(indes);
	close(alpha);
	close(num);
	close(other);

}
