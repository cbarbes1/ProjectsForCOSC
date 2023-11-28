#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include "header.h"

int main(int argc, char **argv)
{
	key_t key;
	int shmid;
	struct Memory *shm;
	key = ftok(".",'x'); //get key value
	//Open existing shared memory
	if((shmid = shmget(key, sizeof(struct Memory), 0)) < 0)
	{
		perror("shmget error \n");
		exit (1);
	}
	//a pointer is attach to shared memory
	shm = (struct Memory *) shmat(shmid, NULL, 0);
	if((long) shm == -1)
	{
		perror("shmat error\n");
		exit(1);
	}

	//read from the shared memory
	while (shm->gostop == GO && shm->gostop != STOP)
	{
		while(shm->status != FILLED)
		{
			if(shm->gostop == STOP)
				break;
		}
		printf("Sum of the two integer: %d\n", shm->data.int1 + shm->data.int2);
		shm->status = TAKEN;
	}
	shmdt((void*)shm); //detach
	return 0;
}
