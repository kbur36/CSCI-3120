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
pthread_mutex_t doctor_thread;

int patient_count;
int counter; 
int val;

int rand_num();
void *cafeteria(char name[]);
void *waiting_room(char name[]);
void *exam_room(char name[]);
pthread_t doc;
pthread_cond_t cond;
// pthread_id_np_t tid;

int main(int argc, char const *argv[]) {
	patient_count = 5;
	counter = 1;

	// mutexA
	sem_init(&mutA, 0, 1);
	// mutexB
	sem_init(&mutB, 0, 1);
	// semaphore
	sem_init(&sema, 0, 3);
	// 5 patient pthreads
	pthread_t p1;
	pthread_t p2;
	pthread_t p3;
	pthread_t p4;
	pthread_t p5;
	

	// 1 doctor pthread
	pthread_mutex_init(&doctor_thread, NULL);
	pthread_cond_init(&cond, NULL);

	pthread_create(&doc, NULL, (void *)exam_room, " doc");

	pthread_create(&p1, NULL, (void *)cafeteria, "Patient 1");
	pthread_create(&p2, NULL, (void *)cafeteria, "Patient 2");
	pthread_create(&p3, NULL, (void *)cafeteria, "Patient 3");
	pthread_create(&p4, NULL, (void *)cafeteria, "Patient 4");
	pthread_create(&p5, NULL, (void *)cafeteria, "Patient 5");

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_join(p3, NULL);
	pthread_join(p4, NULL);
	pthread_join(p5, NULL);
	pthread_join(doc, NULL);

	sem_destroy(&sema);
	sem_destroy(&mutB);
	sem_destroy(&mutA);

	
	return 0;
}

void *cafeteria(char name[]) {
	// update semaphore
	printf("%s is drinkning coffee\n", name);
	sleep(rand_num()); 
	sem_wait(&sema);
	pthread_cond_signal(&cond);
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
	pthread_t cur = pthread_self();
	int time = 0;

 	if(pthread_equal(cur, doc) > 0){ // doctor thread
 		while (counter != 5) {
 			pthread_mutex_lock(&doctor_thread);
 			sem_getvalue(&sema, &val);
 			if (val == 3) { // if waiting room is empty
 				printf("Doctor is sleeping\n");
 				pthread_cond_wait(&cond, &doctor_thread);

 			} else {
 				//pthread_cond_signal(&cond);
 				// printf("Doctor is working on%s\n", name);
 				counter++;
			}
			pthread_mutex_unlock(&doctor_thread);
 		}
	}else{ // patient thread
		printf("%s is being seen by the doctor\n", name);
		time = rand_num();
		printf("The procedure took %d seconds\n", time);
		sleep(time); 
		// unlock B
		sem_post(&mutB);
	} 
}

int rand_num() {
	int r = rand() % 5;
	return r;
}


// phread_cond_wait(&cond, sema);