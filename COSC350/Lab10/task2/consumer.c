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
	while(shm->gostop = GO){
		int i, j;
		int size = sizeof(shm->data.numbers)/sizeof(shm->data.numbers[0]);
		for(i=0; i<size; i++){
			while(shm->data.counter == 0){
				if(shm->gostop == STOP)
					break;
			}
			shm->data.counter--;
			shm->data.numbers[i] = 0;
			for(j = 0; j<size; j++){
				printf("%d ", shm->data.numbers[j]);
			}
			printf("\n");
			shm->status = TAKEN;
			sleep(1);
		}
	}
	shmdt((void *)shm);
	return 0;
}
