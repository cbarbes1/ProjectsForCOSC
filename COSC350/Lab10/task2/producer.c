#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>
#include "header.h"

int main()
{
	int shmid;
	key_t key;
	struct usrData *shm;
	key=ftok(".", 'X');
	if((shmid=shmget(key, sizeof(struct usrData), 0))<0)
	{
		perror("shmget error \n");
		exit(1);
	}
	shm=(struct usrData *)shmat(shmid, NULL, 0);
	
	if((long)shm == -1)
	{
		perror("shmat error \n");
		exit(1);
	}

	int size = 5;
	shm->data.counter = 0;

	while(1){		
		shm->data.numbers[shm->data.counter] = (rand() % (10+1));
		shm->data.counter++;
		while(shm->data.counter == size){
			sleep(1);
		}
		for(int j=0; j<size; j++){
			printf("%d ", shm->data.numbers[j]);
		}
		printf("\n");
		sleep(1);
	}
	
	shmdt((void *) shm);
	return 0;
}
