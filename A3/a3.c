#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>


sem_t sema;
pthread_mutex_t mutA;
pthread_mutex_t mutB;

int rand_num();
void *cafeteria();
void *waiting_room();
void *exam_room();

int main(int argc, char const *argv[]) {
	// mutexA
	pthread_mutex_init(&mutA, NULL);
	// mutexB
	pthread_mutex_init(&mutB, NULL);
	// semaphore
	sem_init(&sema, 0, 3);
	// 5 patient pthreads
	pthread_t p1;
	pthread_t p2;
	pthread_t p3;
	pthread_t p4;
	pthread_t p5;

	// 1 doctor pthread
	pthread_t doc;

	pthread_create(&p1, NULL, (void *)cafeteria(), NULL);
	pthread_create(&p2, NULL, (void *)cafeteria(), NULL);
	pthread_create(&p3, NULL, (void *)cafeteria(), NULL);
	pthread_create(&p4, NULL, (void *)cafeteria(), NULL);
	pthread_create(&p5, NULL, (void *)cafeteria(), NULL);
	
	return 0;
}

void *cafeteria() {
	// update semaphore
	printf("%s\n", );
	sem_post(&sema);
	waiting_room();

}

void *waiting_room() {
	// Lock examination room
	sem_wait(&sema);
	// update semaphore
	sem_post(&sema);
	exam_room();
}

void *exam_room() {
	// Sleep for a random amount of time
	sleep(rand_num()); 
	// unlock B
	sem_post(&sema);
}

int rand_num() {
	int r = rand() % 20;
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
