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
	int gostop;
};

int main()
{
	key_t key = ftok(".", 'B');
	struct integers *buf;
	int shmid = shmget(key, sizeof(buf), 0);
	buf = (struct integers *)shmat(shmid, NULL, 0);
	while(buf->gostop != 2){
		while(buf->status == 1){
			if(buf->gostop == 2)
				break;
			printf("The sum of the two integers is %d\n", buf->num1+buf->num2);
			buf->status = 2;
		}
	}

	shmdt((void *)buf);
	return 0;

}
