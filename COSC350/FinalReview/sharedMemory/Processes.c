#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <errno.h>
#include "header.h"
#include <unistd.h>
#include <signal.h>

// create a hangler for the a given signal as just an exit command
void handler(int signo)
{
	printf("Have a nice day!");
	exit(0);
}

int main()
{
	//
	//
	// build the shared memory
    	int shmid1;
	key_t keyn;
	struct Memory *shm1;
	keyn = ftok(".", 'x'); // create the key
	// create the shared memrory as the size fo the structure
	if((shmid1=shmget(keyn, sizeof(struct Memory), IPC_CREAT | 0666))<0)
	{
		perror("shmget error \n");
		exit(1);
	}
	// attach the shared memory
	shm1 = (struct Memory *)shmat(shmid1, NULL, 0);
	// if fail then exit
	if((long)shm1 == -1){
		perror("shmat error \n");
		exit(1);
	}
	// set the conditional variables
	shm1->status = -1;
	shm1->gostop = 2;
    
	//
	//
	//
	
	// create a child to become the reader
	pid_t pid;
	pid = fork();
	if(pid == 0){
		int shmid;
		key_t key;
		key = ftok(".", 'x'); // create a key to access shared memory with
		struct Memory *shm;
		int num1, num2;
		// get the already existent shared memory
		if((shmid=shmget(key, sizeof(struct Memory), 0)) < 0)
		{
			perror("shmget error \n");
			exit(1);
		}

		shm = (struct Memory *)shmat(shmid, NULL, 0); // attach the memory
		// if fail then exit 
		if((long)shm==-1)
		{
			perror("shmat error \n");
			exit(1);
		}
		// set the conditional variables
		shm->gostop = 2;
		shm->status = -1;

		// create the buffer
		char buffer[BUFSIZ+1];

		memset(buffer, '\0', sizeof(buffer));

		// ask for 2 integers
		printf("Please enter two integers: \n");
		while(read(0, &buffer, BUFSIZ) > 0){ // read until there is ctrl-d end of input
			if(sscanf(buffer, "%d%d", &num1, &num2) == 2){ // save the two integers to seperate vars
				shm->data.int1 = num1; // save into shared mem
				shm->data.int2 = num2; 
				shm->status = 0; // set status to Filled
				while(shm->status != 1); // wait until status is back to 1
				printf("Enter two integers: \n"); // ask again 
			}
			else { // if invalid
				printf("invalid entry \n");
			}
		}
		shm->gostop = 3; // set the stop to 3 meaning stop
		shmdt((void *)shm);// detach the memory
	}else if(pid != 0){ // parent to recieve integers and print them
		signal(SIGCHLD, handler); // set the signal handler
		int shmid;
		key_t key;
		key = ftok(".", 'x'); // create a key for the shared memory
		struct Memory *shm;
		int num1, num2;
		// get the already existent shared memory
		if((shmid=shmget(key, sizeof(struct Memory), 0))<0) 
		{
			perror("shmget error\n");
			exit(1);
		}
		shm = (struct Memory *)shmat(shmid, NULL, 0); // attach the memory
		if((long)shm == -1)
		{
			perror("shmat error \n");
			exit(1);
		}

		// while gostop is go and not stop
		while(shm->gostop == 2 && shm->gostop != 3)
		{
			// wait until status is FILLED
			while(shm->status == -1 || shm->status == 1);
			while(shm->status != 0)
			{
				if(shm->gostop == 2)
					break;
			}
			// print the sum
			printf("Sum of the two integer: %d\n", shm->data.int1 + shm->data.int2);
			shm->status = 1;
		}
		shmdt((void*)shm);
	}
	
	// get the shared memory
	if((shmid1=shmget(keyn, sizeof(struct Memory), 0))<0)
	{
		perror("shmget error");
		exit(1);
	}
	// destroy the memory
	shmctl(shmid1, IPC_RMID, NULL);
    
	return 0;
}
