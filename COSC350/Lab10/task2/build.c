#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <errno.h>
#include "header.h"
#define SHSIZE 100

int main()
{
	int shmid;
	key_t key;
	struct usrData *shm;
	key = ftok(".", 'X');

	if((shmid = shmget(key, sizeof(struct usrData), IPC_CREAT | 0666)) < 0 )
	{
		perror("shmget error \n");
		exit(1);
	}
	shm = (struct usrData *)shmat(shmid, NULL, 0);
	if((long)shm == -1){
		perror("Shmat error \n");
		exit(1);
	}

	
	return 0;
}
