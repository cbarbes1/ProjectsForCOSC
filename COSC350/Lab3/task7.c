#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// convert a c-string
int toInteger(char *str){
	while(*str == ' ' || *str == '\t')
		str++;

	int result = 0; 
	int sign = 1;

	// if a negative sign make the sign -1
	if(*str == '-'){
		sign = -1;
		str++;
	}
	else if(*str == '+'){// if not just move the pointer 
		str++;
	}

	// while the char is a number 1 - 9 find the result
	while(*str <='9' && *str >='0'){
		result= result*10 + (*str - '0');
		str++;
	}

	return result*sign;
}

int main(int argc, char *argv[])
{

	// if less than 1 argument exit the program
	if(argc < 1){
		printf("%s", "No arguments given");
		exit(1);
	}

	int sum = 0; // init the sum

	// loop through the arguments converting them to integer
	for(int i = 0; i<argc; i++){
		sum+=toInteger(argv[i]);
	}
	
	// print the sum to the standard out
	printf("%d\n", sum);

	return 0;
}
