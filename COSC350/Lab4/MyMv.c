#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define MAXLENGTH 4096
void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

// simple function to shift a string leftward
char* shiftStr(char *str)
{
	// starting from the left shift each postion so pos 0 becomes pos 1 etc.
	while(*str != '\0'){
		*str = *(str+1);
		str++;
	}
	return str;
}

int main(int argc, char *argv[])
{
	struct stat buf;
	// make sure theres enough arguments
	if(argc < 3)
		err_sys("No Arguments!");

	char *home_dir = getenv("HOME");
	char path[MAXLENGTH];
	char filePath[MAXLENGTH];
	char special[2] = "~/";


	// if there is a ~/ change to the path
	if(*(argv[2]) == '~'){
		shiftStr(argv[2]);
		snprintf(path, MAXLENGTH, "%s%s", home_dir, argv[2]);
		printf("%s\n", path);
	}
	else{
		snprintf(path, MAXLENGTH, "%s", argv[2]);
	}

	// if the file doesnt exist exit send errors
	if(stat(argv[1], &buf)<0)
		err_sys("file does not exist");

	// if the file destination doesnt exist, change the name to the needed location path
	if(stat(path, &buf)<0){
		if(link(argv[1], path) < 0 )
			err_sys("Error in link");
		if(unlink(argv[1])<0)
			err_sys("Error in unlink");
	}
	else{
		if(S_ISDIR(buf.st_mode)){// if directory link up the path
			snprintf(filePath, MAXLENGTH, "%s%s%s", path, "/", argv[1]);
			if(link(argv[1], filePath)<0)
				err_sys("Error on link");
			if(unlink(argv[1])<0)
				err_sys("Error on unlink");
		}
		else if(S_ISREG(buf.st_mode)){// if the file is a text file 
			if(link(argv[1], path)<0)
				err_sys("Error in link");
			if(unlink(argv[1]) < 0)
				err_sys("Error in unlink");
		}
	}

	return 0;
}
