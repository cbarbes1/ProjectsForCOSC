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

	if(*str == '-'){
		sign = -1;
		str++;
	}
	else if(*str == '+'){
		str++;
	}

	while(*str <='9' && *str >='0'){
		result= result*10 + (*str - '0');
		str++;
	}

	return result*sign;
}

int main(int argc, char *argv[])
{

	if(argc < 1){
		printf("%s", "No arguments given");
		exit(1);
	}

	int sum = 0;

	for(int i = 0; i<argc; i++){
		sum+=toInteger(argv[i]);
	}

	printf("%d\n", sum);

	return 0;
}
