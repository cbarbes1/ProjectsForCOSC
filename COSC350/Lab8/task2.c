#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define NUMTHREADS 4
#define NUMINTS 20
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int *arr;
int numscores;

void err_sys(char *, int);
void *thread1(void *arg);
double findMedian();
void *thread2(void *arg);
void *thread3(void *arg);
void *thread4(void *arg);

int main()
{

	pthread_t threads[NUMTHREADS];
	int rc;
	void *tret;
	printf("Creating first Thread\n");
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

	free(arr);
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
	pthread_mutex_lock(&mutex1);
	arr = (int*)calloc(NUMINTS, sizeof(int));
	numscores=0;
	pthread_mutex_unlock(&mutex1);
	int testscore = 0;
	for(int i = 0; i<NUMINTS && testscore!=-1; i++){
		printf("Please enter an integer: ");
		scanf("%d", &testscore);
		if(testscore != -1){
			pthread_mutex_lock(&mutex1);
			arr[i] = testscore;
			numscores++;
			pthread_mutex_unlock(&mutex1);
		}
	}
	pthread_exit(NULL);
}

double findMedian()
{
	pthread_mutex_lock(&mutex1);
	int size = numscores;
	int array[size];
	for(int i = 0; i<size; i++){
		array[i] = arr[i];
	}
	pthread_mutex_unlock(&mutex1);
	for(int i = 1; i<size; i++){
		int key = array[i]; // current elemtent to be inserted
		int j = i-1;

		while(j>=0 &&array[j] > key){
			array[j+1] = array[j];
			j--;
		}
		array[j+1] = key;
	}
	for(int i = 0; i<size; i++)
		printf("%d ", array[i]);
	printf("\n");	
	if(size %2 !=0)
		return array[size/2];
	else
		return ((array[(size/2)-1]+array[(size/2)]) / 2.00);
}
void *thread2(void *arg)
{
	double average = 0;
	double median = 0;
	pthread_mutex_lock(&mutex1);
	for(int i = 0; i<numscores; i++){
		average += arr[i];
	}
	average = average/numscores;
	pthread_mutex_unlock(&mutex1);
	median = findMedian();
	printf("The average is: %.2f The median is: %.2f\n", average, median);
	pthread_exit(NULL);
}

void *thread3(void *arg)
{
	int size = numscores;

	int min = 0, max = 0;
	for(int i = 1; i<size; i++){
		if(arr[max] < arr[i])
			max = i;
		if(arr[min] > arr[i])
			min = i;
	}
	printf("Here are is the minimum: %d Here is the maximum: %d\n", arr[min], arr[max]);
	pthread_exit(NULL);
}

void *thread4(void *arg)
{
	for(int i = 0; i<NUMINTS; i++){
		arr[i] = 0;
		printf("%d ", arr[i]);
	}
	printf("\n");
	pthread_exit(NULL);
}
