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
	pthread_t p1;
	pthread_t p2;
	pthread_t p3;
	pthread_t p4;
	pthread_t p5;
	pthread_t doc;

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


