#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct integers{
	int num1;
	int num2;
	int status;
};

int main()
{
	key_t key = ftok(".", 'B');
	struct integers *buf;
	int shmid = shmget(key, sizeof(buf), 0666);
	buf = (struct integers *)shmat(shmid, NULL, 0);
	while(buf->status == 1){
		printf("The sum of the two integers is %d\n", buf->num1+buf->num2);

	}


	return 0;

}
