#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <pthread.h>
#define FULL 0
#define MUTEX 1;
#define EMPTY 5;

struct data{
	int arr[5];
};

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};
int main()
{
	key_t key = ftok(".", 'K');
	int shmid;
	shmid = shmget(key, sizeof(struct data), IPC_CREAT | 0666);
	struct data *shm = (struct data *)shmat(shmid, NULL, 0);
	int semid;
	semid=semget(key, 3, 0666 | IPC_CREAT); 
	union semun arg;

	arg.val = FULL;
	semctl(semid, 0, SETVAL, arg);

	arg.val = EMPTY;
	semctl(semid, 1, SETVAL, arg);

	arg.val = MUTEX;
	semctl(semid, 2, SETVAL, arg);
	return 0;
}
