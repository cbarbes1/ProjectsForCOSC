#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#define FULL 1
#define EMPTY 5
#define MUTEX 0

struct data{
	int arr[5];
};

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
}

void up(int semid, int index){
	struct sembuf buf = {index, 1, 0};
	semop(semid, &buf, sizeof(buf));
}

void down(int semid, int index){
	struct sembuf buf = {index, -1, 0};
	semop(semid, &buf, sizeof(buf));
}

int main()
{
	key_t key = ftok(".", 'K');
	int semid;
	semid=semget(key, 3, 0666 | IPC_CREAT);

	pid_t pid = fork();
	if(pid == 0){
		int shmid, item, index;
		shmid=shmget(key, sizeof(struct data), 0666);
		struct data *shm = (struct data *)shmat(shmid, NULL, 0);
		while(1){
			down(semid, FULL);
			down(semid, MUTEX);
			index=semctl(semid, FULL, GETVAL);
			printf("Consuming %d \n", shm->arr[index]);
			shm->arr[index] = 0;
			for(int i = 0; i<5; i++){
				printf("%d ", shm->arr[i]);
			}
			printf("\n");
			up(semid, EMPTY);
			up(semid, MUTEX);
			sleep(1);
		}
	}else if(pid >0){
		int shmid, item, index;
		shmid=shmget(key, sizeof(struct data),0666);
	       	struct data *shm = (struct data *)shmat(shmid, NULL, 0);
 		while(1){
			item = rand()%10 +1;
			down(semid, EMPTY);
			down(semid, MUTEX);
			printf("
			index=semctl(semid, FULL, GETVAL);
			
