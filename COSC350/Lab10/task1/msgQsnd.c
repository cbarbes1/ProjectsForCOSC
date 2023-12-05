#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

/* struct to send a line of text*/
struct usrMsg {
	long id;
	char data[256];
};

int main(void)
{
	struct usrMsg buf;

	int msqid;
	key_t key;
	/* create a key for the message queue */
	if((key=ftok("msgQsnd.c", 'B')) == -1){
		perror("ftok error");
		exit(1);
	}
	/* create the message queue */
	if((msqid=msgget(key, 0644 | IPC_CREAT))==-1){
		perror("msgget error");
		exit(1);
	}
	printf("Two integer value ^D to quit:\n");
	buf.id = 1;
	while(fgets(buf.data, sizeof(buf.data),stdin)!=NULL){
		if(msgsnd(msqid, (struct usrMsg *)&buf, sizeof(buf), 0) == -1){
			perror("msgsnd error");
			exit(1);
		}
		printf("Two integer value ^D to quit:\n");
	}
	
	if(msgctl(msqid, IPC_RMID, NULL) == -1){
		perror("msgctl error");
		exit(1);
	}
	
	exit(0);
}
