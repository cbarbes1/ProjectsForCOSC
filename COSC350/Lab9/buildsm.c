#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <errno.h>
#include "header.h"

int main(int argc, char **argv)
{
	int shmid;
	key_t key;
	struct Memory *shm;
	key = ftok(".", 'x'); // create the key
	if((shmid=shmget(key, sizeof(struct Memory), IPC_CREAT | 0666)) < 0)
	{
		perror("shmget error\n");
		exit(1);
	}
	shm = (struct Memory *)shmat(shmid, NULL, 0);
	if((long)shm == -1){
		perror("shmat error \n");
		exit(1);
	}
	shm->status = NOT_READY;
	shm->gostop = GO;
	return 0;
}
