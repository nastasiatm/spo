#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

sem_t semaphore[2], main_sem;
char alf[] = "abcdefghijklmnopqrstuvwxyz";

int tolower(int);
int toupper(int);
int ( * swap_case[2])(int) = {toupper, tolower};

void * doInversion(void *arg) {
	int i, j;
	
	for (;;) {
		for(j = 0; j < 2; j++) {
			if (sem_wait(&semaphore[0]) == 0) 
				for (i = 0; i < strlen(alf); i++) 
					alf[i] = swap_case[j](alf[i]);
			else {
				perror("Sem_wait");
				exit(1);
			}
			sem_post(&main_sem);
			
		}
	}
}

void * doTurn(void *arg) {
	
	int length, c;
			char *begin, *end, temp;
	length = strlen(alf);
			
	
	for (;;) {
		if (sem_wait(&semaphore[1]) == 0) {
			
			begin  = alf;
			end    = alf;
 
			for (c = 0; c < length - 1; c++)
				end++;
 
			for (c = 0; c < length/2; c++) {        
				temp   = *end;
				*end   = *begin;
				*begin = temp;
 
				begin++;
				end--;
			}
			sem_post(&main_sem);
		}
		else {
				perror("Sem_wait");
				exit(1);
		}
	}
}

int main(int argc, char * argv[]) {
	int id1, id2, result;
	pthread_t thread1, thread2;
	id1 = 0;
	id2 = 1;
	
	
	sem_init(&main_sem, 0, 0);
	sem_init(&semaphore[0], 0, 0);
	sem_init(&semaphore[1], 0, 0);

	result = pthread_create(&thread1, NULL, doInversion, &id1);

	if (result != 0) {
		perror("Creating the first thread");
		return 1;
	}

	result = pthread_create(&thread2, NULL, doTurn, &id2);

	if (result != 0) {
		perror("Creating the second thread");
		return 1;
	}
	
	for (;;) {
		sem_post(&semaphore[0]);
		sem_wait(&main_sem);
		printf("%s\n", alf);
		sleep(1);
		sem_post(&semaphore[1]);
		sem_wait(&main_sem);
		printf("%s\n", alf);
		sleep(1);
	}
	
	return 0;
}
