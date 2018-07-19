#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sema;
pthread_mutex_t mutA;
pthread_mutex_t mutB;

void cafeteria();
void wating_room();
void exam_room();

int main(int argc, char const *argv[]) {
	// mutexA
	pthread_mutex_init(mutA, NULL);
	// mutexB
	pthread_mutex_init(mutB, NULL);
	// semaphore
	sem_init(sema, 0, 3);
	// 5 patient pthreads
	pthread_t p1;
	pthread_t p2;
	pthread_t p3;
	pthread_t p4;
	pthread_t p5;
	// 1 doctor pthread
	pthread_t doc;

	pthread_create(&p1, NULL, cafeteria(), NULL);
	pthread_create(&p2, NULL, cafeteria(), NULL);
	pthread_create(&p3, NULL, cafeteria(), NULL);
	pthread_create(&p4, NULL, cafeteria(), NULL);
	pthread_create(&p5, NULL, cafeteria(), NULL);
	


	return 0;
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

void cafeteria() {
	update semaphore
	waiting_room()
}

void wating_room() {
	lock mutex B // Lock examination room
	update semaphore
	exam_room()
}

void exam_room() {
	sleep(thread p) // for a random amount of time
	unlock B
}

void be_a_doctor() {
	
}


