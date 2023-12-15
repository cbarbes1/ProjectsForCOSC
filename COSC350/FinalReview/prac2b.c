#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

struct msgbuf{
	int id;
	char data[BUFSIZ];
};

struct integers{
	int num1;
	int num2;
	int status;
};

int main()
{
	key_t key = ftok(".", 'B');
	int msgqid, shmid;
	struct msgbuf buf;
	struct integers *data;
	int num1, num2;
	msgqid=msgget(key, 0);
	while(msgrcv(msgqid, (void *)&buf, sizeof(buf), 0, 0) > 0 && buf.status != 1){
		if(sscanf(buf.data, "%d %d", num1, num2) == 2){
			shmid=shmget(key, sizeof(data), IPC_CREAT | 0666);
			data = (struct integers *)shmat(shmid, NULL, 0);
			data->num1 = num1;
			data->num2 = num2;
			data->status = 1;
		}else{
			printf("Invalid Entry\n");
		}
	}
	exit(0);
}
