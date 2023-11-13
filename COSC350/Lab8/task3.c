#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// prototype 2 cleanup handlers
void bye(void *);
void bye1(void *);

// create 2 thread functions
void thread1(void*);
void thread2(void*);

int main()
{
	pthread_t thread_1, thread_2;
	// create thread 1
	pthread_create(&thread_1, NULL, (void *)thread1, (void *) pthread_self());
	// create thread 2
	pthread_create(&thread_2, NULL, (void *)thread2, (void *) thread_1);

	// push the handler for this thread
	pthread_cleanup_push(bye1, NULL);
	while(1)
	{
		printf("In the original thread\n");
		pthread_testcancel(); /* cancel point */
		sleep(1);
	}
	pthread_cleanup_pop(0); // pop the handler off
	// exit the thread
	pthread_exit(0);
}

void thread1(void *arg)
{
	// push the cleanup handler for this thread
	pthread_cleanup_push(bye, arg);
	while(1)
	{
		printf("In the first thread \n");
		pthread_testcancel();/* cancel point */
		sleep(1);
	}
	// pop the cleanup handler
	pthread_cleanup_pop(0);
	// exit the prog
	pthread_exit(0);
}

void thread2(void *arg)
{
	// loop up to 10 then cancel the given thread arg
	int count = 0;
	while(1)
	{
		printf("In the second thread\n");
		count++;
		if(count <= 10)
		{
			// cancel the arg thread
			pthread_cancel((pthread_t) arg);
			pthread_exit(0);
		}
		sleep(1);
	}
	// exit the prog
	pthread_exit(0);
}

// cleanup handler for thread 1
void bye(void *arg)
{
	printf("Bye\n");
	pthread_cancel((pthread_t)arg);
}

//cleanup handler for thread original
void bye1(void *arg)
{
	printf("End of the program\n");
}

