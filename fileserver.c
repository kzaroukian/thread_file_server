#include <pthread.h> 
#include <stdio.h> 
#include <errno.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h>
#include <signal.h>

void* serviceFile(void* arg);
void interuptHandler(int sigNum);

int numFile = 0;
//mutex to avoid confliting writes
pthread_mutex_t fileMutex = PTHREAD_MUTEX_INITIALIZER;

int totalTime = 0;
pthread_mutex_t timeMutex = PTHREAD_MUTEX_INITIALIZER;

int main() {

	signal (SIGINT,  interuptHandler); 

	while(1){
		//malloc to create new memory for each thread to avoid race condition
		char* fileName = malloc(sizeof(char) * 50);
		fgets(fileName, 50, stdin);
		pthread_t thread;
		pthread_create(&thread, NULL, serviceFile, fileName);
	}
	return 0;
}

void* serviceFile(void* arg){
	char* fileName = (char*)arg;
	sleep(1);
	printf("processing file %s", fileName);

	//lock the fileMutex before incrementing the numFile variable to avoid race condition
	pthread_mutex_lock(&fileMutex);
	numFile++;
	pthread_mutex_unlock(&fileMutex);

	//do the same for the totalTime
	pthread_mutex_lock(&timeMutex);
	totalTime = totalTime + 2;
	pthread_mutex_unlock(&timeMutex);

	//free the filename
	free(fileName);
	return NULL;
}

void interuptHandler (int sigNum) 
{ 
	printf ("received an interrupt.\n");
	//lock mutex
	pthread_mutex_lock(&timeMutex);
	pthread_mutex_lock(&fileMutex);

	printf("total number of files processed: %d\n", numFile);
	float averageTime = 0.0;
	//avoid / by 0 errors
	if (numFile != 0){
		
		averageTime = totalTime / numFile;


	}
	printf("averge file process time: %f\n", averageTime);

	//unlock mutex
	pthread_mutex_unlock(&fileMutex);
	pthread_mutex_unlock(&timeMutex);
	
	exit(0); 
}
