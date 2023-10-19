#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

// simple convertion function from string to integer
int myAtoi(char *str)
{
	int sign = 1;
	int result = 0;

	// account for spaces
	while(*str == ' ')
		str++;

	//if - change the sign and increment the pointer
	if(*str == '-'){
		sign = -1;
		str++;
	}
	else if(*str == '+'){
		str++;
	}

	//while the pointer contains a digit
	while(*str <='9' && *str >= '0'){
		result= result*10 + (*str - '0');
		str++;
	}

	//find sign
	result=result*sign;

	// return the finished product
	return result;

}

// convert an integer to a character
char* myitoa(int val, char *strResult)
{
	int sign = 0;
	int temp = val;
	int count = 0;
	// if the number is negative save that it is and make it positive
	if(val<0){
		sign = 1;
		val = -val;
	}

	if(val == 0){
		*strResult = '0';
		strResult++;
		*strResult = '\0';
		return strResult;
	}

	// find the length of the string
	while(temp > 0){
		count++;
		temp/=10;
	}

	// make temp string with null terminator in the beginning
	int i = count + sign;
	strResult[i] = '\0';

	//convert the digits 
	do{
		i--;
		strResult[i] = val % 10 + '0';
		val/=10;
	}while(val>0);

	if(sign ==1){
		strResult[i-1] = '-';
	}

	return strResult;
}



int main(int argc, char *argv[])
{
	//check if there is enough arguments
	if(argc != 2)
		err_sys("Insufficient Arguments!");

	// integer vars for later u
	int indes, nread, result = 0, numAcc = 0;
	// create a buffer and a c string
	char buffer;
	char number[80];

	char number2[80];

	// open the file check for errors
	if((indes=open(argv[1], O_RDONLY, 0666)) ==-1)
		err_sys("File Open Error!");

	
	// loop through the file saving only numerical values
	while((nread=read(indes, &buffer, 1)) >0){
		if(buffer <= '9' && buffer >='0'){
			number[numAcc] = buffer;
			numAcc++;
		}
	}

	
	// exit with errors if there was a read error
	if(nread<0)
		err_sys("Read Error");

	// convert to an integer
	result=myAtoi(number);
	result=result+10;
	//convert back to a string
	myitoa(result, number2);

	// write the string to standard out
	if(write(1, &number2, strlen(number2)) == -1)
		err_sys("Write Error");

	printf(" Result as an integer: %d\n", result);

	return 0;
}
