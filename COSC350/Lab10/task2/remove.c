#include <stdio.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdlib.h>
#include "header.h"

int main()
{
	key_t key;
	int shmid;
	struct usrData shm;
	key = ftok(".", 'X');
	if((shmid=shmget(key, sizeof(struct usrData), 0))< 0){
		perror("shmget error\n");
		exit(1);
	}
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}
