#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct usrData {
	long id;
	char data[256];
};

int main(void)
{
	struct usrData buf;
	int msqid, int1, int2;
	key_t key;

	/*create the key*/
	if((key=ftok("msgQsnd.c", 'B'))==-1){
		perror("ftok error");
		exit(1);
	}
	/* open the message queue */
	if((msqid=msgget(key, 0644))==-1){
		perror("msgget error");
		exit(1);
	}
	
	buf.id = 1;
	
	while(msgrcv(msqid, (struct usrData *)&buf, sizeof(buf), 0, 0) >0 ){
		
		if(sscanf(buf.data, "%d %d", &int1, &int2) == 2){
			printf("The sum is: %d \n", int1+int2);
		}
		else 
		{
			printf("invalid entry\n");
		}
	}
	return 0;
}

