#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#define MAXLENGTH 2048
void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int main()
{
	// get the home directory name
	const char *home_dir = getenv("HOME");
	char path[MAXLENGTH];
	char HelloPath[MAXLENGTH];

	// get the absolute path to the hello file thats in your current directory
	realpath("hello", HelloPath);

	struct stat tmp;

	if(chdir(home_dir) == -1)
		err_sys("Move error");

	if(stat("Dir1", &tmp) < 0){
		umask(0000);
		// make the first sub directory	
		if(mkdir("Dir1", 0777) == -1)
			err_sys("mkdir error 1");
	}
	if(stat("Dir2", &tmp) < 0){
		// make the second sub directory
		if(mkdir("Dir2", 0777) == -1)
			err_sys("mkdir error 2");
	}
	if(stat("Dir2/Dir21", &tmp) < 0){
		// add the sub directory
		if(mkdir("Dir2/Dir21", 0777) == -1)
			err_sys("mkdir error 3");
	}

	// copy the hello file under the Dir2/Dir21
	if(link(HelloPath, "Dir2/Dir21/hello")<0)
		err_sys("Link Error 1");

	// open the file
	snprintf(path, MAXLENGTH, "%s%s", home_dir, "/Dir2/Dir21");
	// symbolic link the todir21 to dir21
	if(symlink(path, "Dir1/toDir21") < 0)
		err_sys("symbolic link failed 1");

	snprintf(path, MAXLENGTH, "%s%s", home_dir, "/Dir2/Dir21/hello");

	// symbolic link the tohello to hello
	if(symlink(path, "Dir1/toHello")<0)
		err_sys("symbolic link failed 2");

	return 0;

}
