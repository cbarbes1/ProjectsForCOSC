#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>
#include "header.h"

int main()
{
	key_t key;
	int shmid;
	struct usrData *shm;
	key = ftok(".", 'X');

	if((shmid=shmget(key, sizeof(struct usrData), 0))<0){
		perror("shmget error \n");
		exit(1);
	}
	shm = (struct usrData *)shmat(shmid, NULL, 0);
	if((long)shm == -1)
	{
		perror("shmat error\n");
		exit(1);
	}
	while(1){
		int i, j;
		int size = 5;
		while(shm->data.counter == 0){
			sleep(1);
		}
		shm->data.counter--;
		shm->data.numbers[shm->data.counter] = 0;
		for(j = 0; j<size; j++){
			printf("%d ", shm->data.numbers[j]);
		}
		printf("\n");
		sleep(1);
	}
	shmdt((void *)shm);
	return 0;
}
