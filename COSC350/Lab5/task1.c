#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;
char* mygetenv(char*);

int checkEqual(char *str1, char *str2)
{
	while(str1 && str2 && *str1 == *str2 && *(str1+1) != '=' && *(str2+1) != '='){
		str1++;
		str2++;
	}
	if(*str1 != *str2)
		return 0;
	return 1;
}

void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int main(int argc, char *argv[])
{
	if(argc != 2)
		err_sys("Insufficient Arguments");

	char *str = mygetenv(argv[1]);
	printf("%s \n", str);
	return 0;
}

char* mygetenv(char *argEnv)
{
	char **p = environ;


	while( *p != NULL && checkEqual(*p, argEnv)==0){
		*p++;
	}

	if(*p == NULL)
		err_sys("Invalid Path Name");

	return *p;
}
