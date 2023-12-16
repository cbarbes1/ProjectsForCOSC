#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

struct msgbuf{
	long id;
	char data[256];
};

struct data{
	int int1, int2;
};
struct Memory{
	int status;
	int gostop;
	struct data nums;
};

int main()
{
	key_t key = ftok(".", 'B');
	int msgqid, shmid;
	struct msgbuf buf;
	int int1, int2;
	msgqid=msgget(key,IPC_CREAT | 0666);
	if((shmid=shmget(key, sizeof(struct Memory), IPC_CREAT | 0666))<0){
		perror("shmget error\n");
		exit(1);
	}
	struct Memory *shm=(struct Memory *)shmat(shmid, NULL, 0);
	shm->status = 0;
	shm->gostop = 1;
	buf.id = 1;
	while(msgrcv(msgqid, (struct msgbuf*)&buf, sizeof(buf), 0, 0) > 0){
		if(sscanf(buf.data, "%d %d", &int1, &int2) == 2){
			printf("%d %d \n", int1, int2);
			shm->nums.int1 = int1;
			shm->nums.int2 = int2;	
			shm->status = 1;
			//while(shm->status !=2);
			printf(" %d %d \n", shm->nums.int1, shm->nums.int2);	
		}else{
			printf("Invalid Entry\n");
			continue;
		}
	}
	shm->gostop = 2;
	shmdt((void *)shm);
	shmctl(shmid, IPC_RMID, NULL);
	exit(0);
}
