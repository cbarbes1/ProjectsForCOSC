#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <errno.h>

struct msgbuf {
	long id;
	char data[BUFSIZ];
};

int main()
{
	struct msgbuf buf;
	key_t key;
	int msgqid;
	key=ftok(".", 'B');
	msgqid=msgget(key, 0666 | IPC_CREAT);
	buf.id = 1;
	// ask the user for integers
	printf("Please enter an integer ^D to quit\n");
	while(fgets(buf.data, BUFSIZ, stdin) != NULL){
		msgsnd(msgqid, (void *)&buf, sizeof(buf), 0);
		printf("Please enter an integer ^D to quit\n");
	}
	msgctl(msgqid, IPC_RMID, NULL);
	return 0;
}
