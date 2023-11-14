#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 256

int main(int argc, char *argv[])
{
	// create storage vars
	char line[MAXLINE];
	char output[BUFSIZ];
	// create the file variable
	FILE *wfp;
	line[0] = '\0'; // set the first spot to the null terminator

	for(int i = 1; i<argc; i++){ 
		if(i == 1){ //if the first iteration then we must just concatenate
			strcat(line, argv[i]);
		}else{ // if anything else then place a space before
			strcat(line, " ");
			strcat(line, argv[i]);
		}
	}

	wfp = popen(line, "r"); // open the pipe and all subsequent steps
	
	while(fgets(output, BUFSIZ, wfp)){ // get the input from the descriptor
		printf("%s", output); // print the output
	}

	pclose(wfp); // close the pipe
	exit(0); // exit
}
