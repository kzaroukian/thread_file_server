#include <pthread.h> 
#include <stdio.h> 
#include <errno.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h>

void* serviceFile(void* arg);

int numFile = 0;

int main() {
	
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
	numFile++;
	free(fileName);
	return NULL;
}
