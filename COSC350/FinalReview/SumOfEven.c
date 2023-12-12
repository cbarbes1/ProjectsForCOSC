#include <stdio.h>
#include <stdlib.h>
#include <perror.h>
int st_to_int(char *str)
{
	int sign = 1;
	int result = 0;
	while(*str == ' '){
		str++;
	}

	if(*str == '-'){
		sign = -sign;
		str++;
	}else if(*str == '+'){
		str++;
	}

	while(*str != '\0'){
		result = result*10 + *str - '0';
		str++;
	}

	result = result * sign;

	return result;
}

int main(int argc, int argv[])
{
	if(argc != 2){

