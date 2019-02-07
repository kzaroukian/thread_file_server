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
		printf("Enter file name: ");
		fgets(fileName, 50, stdin);
		pthread_t thread;
		pthread_create(&thread, NULL, serviceFile, fileName);
	}
	return 0;
}


void* serviceFile(void* arg){
	char* fileName = (char*)arg;
        int prob = rand() % (101 - 1) + 1;
        printf("%d\n",prob);	
	if (prob <= 20) {
	  int stime = rand() % 4;
          sleep(7+stime);
          printf("File not in cache, processing file %s \n",fileName);	  
	} else {
	  sleep(1);
	  printf("File found in cache, processing file %s\n", fileName);
	}
        numFile++;
	free(fileName);
	
	return NULL;
}
