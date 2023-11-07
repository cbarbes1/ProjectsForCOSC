#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#define NUM_THREADS 2

void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void *Factorial(void *arg)
{
	int nval = atoi(arg);
	int fact = 1;
	int i;
	// while the nvalue is greater than 1 multiply and subtract
	for(i=1; i<=nval; i++)
		fact *= i;

	// print the result
	printf("Factorial: %d\n", fact);

	// exit the thread
	pthread_exit(NULL);
}

void *Sum(void *arg)
{
	int nval = atoi(arg);
	int sum = 0;
	int i;
	// while nvalue is greater than 1 continue
	for(i=1; i<=nval; i++)
		sum += i;

	// print the result
	printf("Sum: %d\n", sum);

	// exit the thread
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	if(argc != 2)
		err_sys("Insufficient Arguments");

	printf(argv[1]);
	// create array of threads
	pthread_t threads[NUM_THREADS];
	// create error var
	int rc, t = 0;

	// tell user which thread is being created 
	printf("In main: Creating thread for sum of 1 to %s\n", argv[1]);
	rc = pthread_create(&threads[t++], NULL, Sum, (void *)argv[1]);
	
	if(rc!=0){// if there is a return code then display and exit
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(1);
	}

	// tell user which thread is being created
	printf("In main: Creating thread for factorial of %s\n", argv[1]);
	rc = pthread_create(&threads[t++], NULL, Factorial, (void *)argv[1]);

	if(rc!=0){ // if there is a return code then display and exit
		printf("ERROR; return code from pthread_create() is %d\n");
		exit(1);
	}

	pthread_exit(NULL);

	return 0;
}
