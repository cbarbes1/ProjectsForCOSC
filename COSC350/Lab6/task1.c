/* Author: Cole Barbes
 * Last Optimized: 10/22/23
 * Purpose: Create a function called mygetenv that does the same thing as getenv function
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;
char* mygetenv(char*);

// easy function to check if 1 string is equivalent to another with path after the equal
int checkEqual(char *str1, char *str2)
{
	// while the chars are equal and neither of strings have a '=' after the char
	while(*str1 == *str2 && *(str1+1) != '=' && *(str2+1) != '='){
		str1++;
		str2++;
	}
	// if not equal then the strings must not be equal
	if(*str1 != *str2)
		return 0;
	return 1;
}

// simple error check function
void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int main(int argc, char *argv[])
{
	// check that acurate args were sent
	if(argc != 2)
		err_sys("Insufficient Arguments");

	// grab the path
	char *str = mygetenv(argv[1]);

	// print the path
	printf("%s \n", str);


	return 0;
}

char* mygetenv(char *argEnv)
{
	// grab the systems environment variable start location
	char **p = environ;
	// while the pointer is not null and the strings are not equal
	while( *p != NULL && checkEqual(*p, argEnv)==0){
		p++;
	}

	// if the string is null exit
	if(*p == NULL)
		err_sys("Invalid Path Name");

	// grab the temporary pointer because it looks ugly with the **p
	char *tmp = *p;

	// while the char is not an equal 
	while(*tmp != '=')
		tmp++;
	tmp++; // iterate past the '='

	return tmp;
}
