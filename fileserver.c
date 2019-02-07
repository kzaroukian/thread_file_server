#include <pthread.h> 
#include <stdio.h> 
#include <errno.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h>

void* find_file(void* arg);

int main() {

   char fileName[500];
   printf("Enter a file name: ");
   fgets(fileName,500,stdin);
   // malloc for file name
   int status;
   pthread_t child;

   if ((status = pthread_create(&child, NULL, find_file, &fileName)) != 0) {
      fprintf(stderr, "Error creating thread %d: %s\n", status, strerror(status));
      exit(1);
   }

   // otherwise thread was successfully created

   return 0;
}

void* find_file(void* arg) {
   // free file name
   int prob =  rand() % (101 - 1) + 1;

   if (prob <= 20) {
      sleep(1);
   } else {
      int sleep = rand() % ()   
   }
}

