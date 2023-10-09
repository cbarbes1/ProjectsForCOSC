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

int main(int argc, char *argv[])
{

	// get the home directory name
	const char *home_dir = getenv("HOME");

	if(chdir(home_dir) == -1)
		err_sys("Move error");

	umask(0000);
	// make the first sub directory	
	if(mkdir("Dir1", 0777) == -1)
		err_sys("mkdir error 1");

	// make the second sub directory
	if(mkdir("Dir2", 0777) == -1)
		err_sys("mkdir error 2");

	// add the sub directory
	if(mkdir("Dir2/Dir21", 0777) == -1)
		err_sys("mkdir error 3");

	char pathtohello[MAXLENGTH];

	snprintf(pathtohello, MAXLENGTH, "%s%s", home_dir, "/ProjectsForCOSC/COSC350/Lab4/hello"); 
	// link the hello file under the dir21
	if(link(pathtohello, "Dir2/Dir21/hello") < 0)
		err_sys("Link error 1");
	
	snprintf(pathtohello, MAXLENGTH, "%s%s", home_dir, "/Dir2/Dir21");
	// symbolic link the todir21 to dir21
	if(symlink(pathtohello, "Dir1/toDir21") < 0)
		err_sys("symbolic link failed 1");

	snprintf(pathtohello, MAXLENGTH, "%s%s", home_dir, "/Dir2/Dir21/hello");

	// symbolic link the tohello to hello
	if(symlink(pathtohello, "Dir1/toHello")<0)
		err_sys("symbolic link failed 2");

	return 0;

}
