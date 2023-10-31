#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 5

void *Factorial(void *arg)
{
	int nval = atoi(arg);
	int fact = 1;

	while(nval > 1){
		fact = nval*(--nval);
	}

	printf("Factorial: %d", fact);

	pthread_exit(NULL);
}

void *Sum(void *arg)
{
	int nval = atoi(arg);
	int sum = 1;

	while(nval >1){
		sum = nval + (--nval);
	}

	printf("Sum: %d", sum);

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	if(argc != 3)
