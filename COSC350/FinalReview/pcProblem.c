#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <pthread.h>
#include <sys/shm.h>
#include <sys/types.h>
#define N 5

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array; 
};

struct integers{
	int arr[N];
};

void down(int semid, int index){
	struct sembuf buf = {index, -1, 0};
	semop(semid, &buf, 1);
}

void up(int semid, int index){
	struct sembuf buf = {index, 1, 0};
	semop(semid, &buf, 1);
}

void *thread1(void *threadid);
void *thread2(void *threadid);

int main()
{

	key_t key;
	int semid;
	union semun arg;
	struct integers *shm;

	if((key=ftok(".", 'x'))== -1)
	{
		perror("key error\n");
		exit(1);
	}
	/* create the 3 semaphores */
	if((semid=semget(key, 3, 0666 | IPC_CREAT)) == -1){
		perror("Semget error\n");
		exit(1);
	}

	/*set the value of the MUTEX(0) to 1 */
	arg.val = 1;
	if((semctl(semid, 0, SETVAL, arg)) == -1)
	{
		perror("semctl error\n");
		exit(1);
	}
	
	/* set the value of the FULL(1) to 0 */
	arg.val = 0;
	if((semctl(semid, 1, SETVAL, arg))==-1)
	{
		perror("semctl error\n");
		exit(1);
	}
	/* set the value of the EMPTY(2) to N */
	arg.val = N;
	if((semctl(semid, 2, SETVAL, arg)) == -1)
	{
		perror("semctl error\n");
		exit(1);
	}

	int shmid;
	if((shmid = shmget(key, sizeof(struct integers), IPC_CREAT | 0666)) < 0)
	{
		perror("shmget error");
		exit(1);
	}

	shm = (struct integers *) shmat(shmid, NULL, 0);
	if((long)shm < 0)
	{
		perror("shmat error");
		exit(1);
	}


	/* setup the threads to operate as producer and consumer */

	pthread_t threads[2];
	int rc;

	pthread_create(&threads[0], NULL, thread1, NULL);
	pthread_create(&threads[1], NULL, thread2, NULL);

	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);

	shmctl(shmid, IPC_RMID, NULL);
	semctl(semid, 0, IPC_RMID, arg);

	return 0;
}


// producer
void *thread1(void *threadid)
{
	int semid, shmid;
	key_t key = ftok(".", 'x');
	semid=semget(key, 3, 0);
	shmid=shmget(key, sizeof(struct integers), 0);
	struct integers *shm = (struct integers *)shmat(shmid, NULL, 0);
	int item;
//	sleep(2);
	while(1)
	{
		item = rand()%10+1; // produce
		down(semid, 2); // down the empty 
		down(semid, 0); // down the mutex
		printf("produce: %d\n", item);
		int index = semctl(semid, 1, GETVAL);// grab the index

		shm->arr[index] = item; // set the item into the memory
		for(int i = 0; i<N; i++){
			printf("%d ", shm->arr[i]);
		}

		printf("\n");
		up(semid, 0); // up the mutex
		up(semid, 1); // up the full
		sleep(1);
	}
	shmdt((void*)shm); // detach
}

void *thread2(void *threadid)
{
	int semid, shmid;
	key_t key = ftok(".", 'x');
	semid=semget(key, 3, 0);
	shmid=shmget(key, sizeof(struct integers), 0);
	struct integers *shm = (struct integers *)shmat(shmid, NULL, 0);
	int item;
	sleep(2);
	while(1){
		down(semid, 1);
		down(semid, 0);
		int index = semctl(semid, 1, GETVAL);// grab the index
		printf("consumed: %d\n", shm->arr[index]);
		shm->arr[index] = 0;
		for(int i = 0; i<N; i++){
			printf("%d ", shm->arr[i]);
		}
		printf("\n");
		
		up(semid, 2);
		up(semid, 0);
		sleep(1);
	}
	shmdt((void *)shm);
}
