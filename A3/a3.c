#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <string.h>

sem_t sema;
sem_t mutA;
sem_t mutB;

int rand_num();
void *cafeteria(char name[]);
void *waiting_room(char name[]);
void *exam_room(char name[]);

int main(int argc, char const *argv[]) {
	// mutexA
	// pthread_mutex_init(&mutA, NULL);
	// mutexB
	sem_init(&mutB, 0, 1);
	// semaphore
	sem_init(&mutA, 0, 3);
	// 5 patient pthreads
	pthread_t p1;
	pthread_t p2;
	pthread_t p3;
	pthread_t p4;
	pthread_t p5;

	// 1 doctor pthread
	pthread_t doc;

	pthread_create(&p1, NULL, (void *)cafeteria, " patient 1");
	pthread_create(&p2, NULL, (void *)cafeteria, " patient 2");
	pthread_create(&p3, NULL, (void *)cafeteria, " patient 3");
	pthread_create(&p4, NULL, (void *)cafeteria, " patient 4");
	pthread_create(&p5, NULL, (void *)cafeteria, " patient 5");
	
	return 0;
}

void *cafeteria(char name[]) {
	// update semaphore
	printf("%s is drinkning coffee\n", name);
	sem_post(&sema);
	waiting_room(name);

}

void *waiting_room(char name[]) {
	printf("%s is in the waiting room\n", name);
	// Lock examination room
	sem_wait(&mutB);
	// update semaphore
	sem_post(&sema);
	exam_room(name);
}

void *exam_room(char name[]) {
	printf("%s has a finger in his butt\n", name);
	// Sleep for a random amount of time
	sleep(rand_num()); 
	// unlock B
	sem_post(&mutB);
}

int rand_num() {
	int r = rand() % 5;
	return r;
}

// Instantiate global semaphore and mutex A and B
// semaphore s
// mutex a
// mutex b


// main{
// 	create mutex A // to be used in the semaphore
// 	create mutex B // to be used as the examination room
// 	create semaphore allowing a maximum of 3 threads at any time, using mutex A
// 	create threads passing the cafeteria() function as a parameter
// }