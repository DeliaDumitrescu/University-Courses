#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#define THR_NUM 10
#define DOC_NUM 1

struct doctor{
    pthread_mutex_t mutex;
    int id;
};

//The pool of pacients that will wait for a doctor to become available
pthread_t patients_pool[THR_NUM];

//The queue of doctors
struct doctor doctors[DOC_NUM];
int doc_count;

//The mutex to protect the queue from being accesed by multiple threads at the same time
pthread_mutex_t q_mutex;

// Condition variable for pacients to wait for a doctor to become available instead of "infinitely" checking if one is
pthread_cond_t cond_doc;


void finish_consultation(struct doctor d, int p_index, int consultation_time, int waiting_time) {
    printf("Finished consulting patient %d with doctor %d \n", p_index, d.id);
    printf("Consultation time: %d \n", consultation_time);
    printf("Waiting time: %d \n \n", waiting_time);

    //Add doctor back to queue
    pthread_mutex_lock(&q_mutex);
    doctors[doc_count] = d;
    doc_count++;
    pthread_mutex_unlock(&q_mutex);

    //Signal that doctor is available again
    pthread_cond_signal(&cond_doc);
}

void consultation(struct doctor *d, int p_index, int waiting_time) {
    int consultation_time = 1 + rand() % 10;

    pthread_mutex_lock(&d->mutex);
    sleep(consultation_time);
    pthread_mutex_unlock(&d->mutex);

    finish_consultation(*d, p_index, consultation_time, waiting_time);
}

void *start_thread(void* args) {
    int *p_index = (int*)args, start_waiting, stop_waiting;
    struct doctor _doctor;

    pthread_mutex_lock(&q_mutex);

    //While no doctor available, wait
    start_waiting = time(NULL);
    while(doc_count == 0){
        printf("Pacient %d arrived and is waiting for doctor..\n\n", *p_index);
        pthread_cond_wait(&cond_doc, &q_mutex);
    }
    stop_waiting = time(NULL);
    if(stop_waiting - start_waiting == 0){
        printf("Pacient %d arrived and did not wait for doctor\n\n", *p_index);
    }

    //Now doctor is available
    _doctor = doctors[0];

    //Pop doctor off queue
    for (int i = 0; i < doc_count - 1; i++) {
        doctors[i] = doctors[i + 1];
    }
    doc_count--;

    pthread_mutex_unlock(&q_mutex);

    consultation(&_doctor, *p_index, stop_waiting - start_waiting);
}


int main(int argc, char* argv[])
{
    //Initialize mutex for queue
    if(pthread_mutex_init(&q_mutex, NULL)){
      printf("The queue mutex could not be initialized");
      return errno;
    }

    //Initialize condition variable
    if(pthread_cond_init(&cond_doc, NULL)){
      printf("The condition variable could not be initialized");
      return errno;
    }

    //Create doctors and add them to the queue
    for(int i = 0; i < DOC_NUM; i++){
        struct doctor d;
        d.id = i;
        if(pthread_mutex_init(&d.mutex, NULL)){
            printf("The doctor mutex could not be initialized");
            return errno;
        }
        doctors[doc_count] = d;
        doc_count++;
    }

    //Create pacients
    for(int i = 0; i < THR_NUM; i++){
        //Create pacients every randomly, with 1, 2, or 3s between them
        // sleep(1 + rand() % 3);
        sleep(1);

        int *p_index;
        p_index = (int*)malloc(sizeof(int));
        *p_index = i;

        if(pthread_create(&patients_pool[i], NULL, &start_thread, p_index)){
            printf("The pacient thread could not be created");
            return errno;
        }
    }

    //Join threads
    for (int i = 0; i < THR_NUM; i++) {
        if (pthread_join(patients_pool[i], NULL) != 0) {
            printf("Failed to join thread");
            return errno;
        }
    }

    //Clean up
    for(int i = 0; i < DOC_NUM; i++){
        pthread_mutex_destroy(&doctors[i].mutex);
    }
    pthread_mutex_destroy(&q_mutex);
    pthread_cond_destroy(&cond_doc);

    return 0;
}