#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "header1.h"
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int shmid;
	int semid;
	key_t key;
	struct Memory *shm;
	union semun arg;
	key = ftok(".", 'x'); // creates a key value
	if((shmid = shmget(key, sizeof(struct Memory), IPC_CREAT | 0666)) <0)
	{
		perror("shmget error\n");
		exit(1);
	}
	shm = (struct Memory *) shmat(shmid, NULL, 0); //attach to shared memory
	if((long)shm == -1)
	{
		perror("shmat error \n");
		exit(1);
	}
	//Create 3 semaphores
	if((semid = semget(key, 3, 0666 | IPC_CREAT)) == -1){
		perror("semget Error");
		exit(1);
	}
	//Assign MUTEX(0) with value 1
	arg.val = 1;
	if(semctl(semid, MUTEX, SETVAL, arg) == -1){
		perror("semctl Error");
		exit(1);
	}
	//Assign EMPTY(2) with value N(5)
	arg.val = N;
	if(semctl(semid, EMPTY, SETVAL, arg) == -1){
		perror("semctl Error");
		exit(1);
	}
	//Assign FULL(1) with value 0
	arg.val = 0;
	if(semctl(semid, FULL, SETVAL, arg) == -1){
		perror("semctl Error");
		exit(1);
	}	
	return 0;
}
