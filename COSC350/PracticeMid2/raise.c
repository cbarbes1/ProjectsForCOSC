#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>

void *thrd1(void *arg){
	int count=0;
	while(1){
		printf("In thread 1: code name: the murderer\n");
		if(count == 10){
			raise(SIGTERM);
		}
		sleep(1);
		count++;
	}
}

void *thrd2(void *arg){
	while(1){
		printf("In thread 2\n");
		sleep(1);
	}
}

int main(){
	pthread_t thread1, thread2;

	pthread_create(&thread1, NULL, thrd1, NULL);
	pthread_create(&thread2, NULL, thrd2, NULL);
	while(1){
		printf("In main\n");
		sleep(1);
	}

	return 0;
}
