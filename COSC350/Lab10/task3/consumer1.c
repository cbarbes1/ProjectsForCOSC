#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include "header1.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

void down(int semid, int index){
	struct sembuf buf = {index, -1, 0};
	semop(semid, &buf, 1);
}
void up(int semid, int index){
	struct sembuf buf = {index, 1, 0};
	semop(semid, &buf, 1);
}


int main(int argc, char **argv)
{
	key_t key;
	int shmid;
	int semid;
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
	if((semid = semget(key, 3, 0)) == -1){
		perror("semget");
		exit(1);
	}
	int index;
	int size = 5;
	//read from the shared memory
	while (1)
	{
		int i;
		//Decrease item
		down(semid, FULL);
		//Lock mutex
		down(semid, MUTEX);
		index = semctl(semid, FULL, GETVAL);
		shm->numbers[index] = 0;
		for(int i = 0; i<size; i++){
			printf("%d ", shm->numbers[i]);
		}
		//Unlock mutex
		up(semid, MUTEX);
		//Increase empty
		up(semid, EMPTY);
		printf("\n");
		sleep(1);
	}
	shmdt((void*)shm); //detach
	return 0;
}
