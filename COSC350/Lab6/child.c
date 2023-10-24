#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int st_to_int(char *str)
{
	int result = 0;
	while(*str!='\0'){
		result = result*10 + (*str-'0');
		str++;
	}
	return result;
}

void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int main(int argc, char *argv[])
{
	// make sure there is sufficient arguments
	if(argc !=4)
		err_sys("Insufficient Arguments");
	// convert the strings to integers and save them in the appropriate place
	int nc = st_to_int(argv[2]);
	int tc = st_to_int(argv[3]);
	
	// print the messages
	for(; nc>0; nc--) {
		printf("%s  PID = %d\n", argv[1], getpid());
		sleep(tc);
	}

	exit(37);
}
