#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define NUMTHREADS 4
#define NUMINTS 20
int *arr;
int numscores;

void err_sys(char *, int);
void *thread1(void *arg);
int findMedian();
void *thread2(void *arg);
void *thread3(void *arg);
void *thread4(void *arg);

int main()
{

	pthread_t threads[NUMTHREADS];
	int rc;
	void *tret;
	printf("Creating first Thread");
	// create the first thread
	if((rc=pthread_create(&threads[0], NULL, thread1, NULL))!=0)
		err_sys("Error: return code from pthread_create() is", rc);

	// use the join function to wait for the first thread to stop executing
	if((rc=pthread_join(threads[0], tret))!=0)
		err_sys("Error: return code form pthread_join() is", rc);

	// create thread 2
	if((rc=pthread_create(&threads[1], NULL, thread2, NULL))!=0)
		err_sys("Error: return code from pthread_create() is", rc);

	// create thread 3
	if((rc=pthread_create(&threads[2], NULL, thread3, NULL))!=0)
		err_sys("Error: return code from pthread_create() is", rc);

	// wait for the thread 2 to finish
	if((rc=pthread_join(threads[1], NULL)) != 0)
		err_sys("Error: return code form pthread_join() is", rc);

	// wait for the thread 3 to finish 
	if((rc=pthread_join(threads[2], NULL)) != 0)
		err_sys("Error: return code from pthread_join() is", rc);

	if((rc=pthread_create(&threads[3], NULL, thread4, NULL))!=0)
		err_sys("Error: return code from pthread_create() is", rc);

	pthread_join(threads[3], NULL);
	exit(0);
}

// simple error printing function
void err_sys(char *str, int msg)
{
	printf("%s%d\n", str, msg);
	exit(1);
}

void *thread1(void *arg)
{
	//pthread_mutex_lock(&array_mutex);
	numscores=0;
	int testscore = 0;
	for(int i = 0; i<NUMINTS && testscore!=-1; i++){
		printf("Please enter an integer: ");
		scanf("%d", &testscore);
		if(testscore != -1){
			arr[i] = numscores;
			numscores++;
		}

	}
	//pthread_mutex_unlock(&array_mutex);
	pthread_exit(NULL);
}

int findMedian()
{
	int size = numscores;
	int array[size];
	for(int i = 0; i<size; i++){
		array[i] = arr[i];
	}
	for(int i = 1; i<size; i++){
		int key = array[i]; // current elemtent to be inserted
		int j = i-1;

		while(j>=0 &&array[j] > key){
			array[j+1] = array[j];
			j--;
		}
		array[j+1] = key;
	}
	if(size %2 !=0)
		return array[size/2];
	else
		return (array[(size/2)]+array[((size/2)+1)] / 2);
}
void *thread2(void *arg)
{
	int average = 0;
	int median = 0;
	int size = numscores;
	for(int i = 0; i<size; i++){
		average += arr[i];
	}
	average /= size;
	median = findMedian();
	printf("The average is: %d The median is: %d\n", average, median);
	pthread_exit(NULL);
}

void *thread3(void *arg)
{
	int size = numscores;

	int min = 0, max = 0;
	for(int i = 1; i<size; i++){
		if(max < arr[i])
			max = i;
		if(min > arr[i])
			min = i;
	}
	printf("Here are is the minimum: %d Here is the maximum: %d\n", arr[min], arr[max]);
	pthread_exit(NULL);
}

void *thread4(void *arg)
{
	for(int i = 0; i<numscores; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");

	for(int i = 0; i<NUMINTS; i++){
		arr[i] = 0;
		printf("%d ", arr[i]);
	}
	printf("\n");

	pthread_exit(NULL);
}
