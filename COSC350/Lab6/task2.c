#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>

// simple function to print error message and exit prog with errors
void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

// simple function to open the utmp file and return the descriptor
int openUtmpFile()
{
	int indes;
	// open the file
       	if((indes = open("/var/run/utmp", O_RDONLY)) == -1)
		err_sys("Could not open the utmp file");		

	// return the descriptor
	return indes;
}

int main(){

	int indes = openUtmpFile(); // grab the descriptor
	// create needed container vars
	char buf;
	int nread, numLog = 0;
	struct utmp entry;

	// loop through the file grabbing exactly what is needed for the struct every time
	while((nread=read(indes, &entry, sizeof(entry))) > 0){
		// print the usernames of all the structs in the file
		printf("Username: %s\n", entry.ut_user);
		// if the entry is a user process then increment num Logged in 
		if(entry.ut_type == USER_PROCESS)
			numLog++;
	}

	// print the total number of users
	printf("Number Of Logged in users: %d\n", numLog);

	// close the file
	close(indes);

	return 0;
}	
