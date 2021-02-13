#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <pthread.h>
#include <errno.h>

#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;
int nr_threads = 5;
pthread_t threads[5];
pthread_mutex_t mtx;

int v[] = {4, 2, 1, 2, 1}; //pt test, pot fi luate alte valori sau generate cu random

int decrease_count(int count) {
    pthread_mutex_lock(&mtx);        //ocupam mutex

    if (available_resources < count) {      //verificam daca avem destule resurse, daca nu eliberam mutexul
        pthread_mutex_unlock(&mtx);
        return -1;
    }

    available_resources -= count;  //daca avem destule, le luam si eliberam

    printf("GOT %d RESOURCES %d REMAINING\n", count, available_resources);
    pthread_mutex_unlock(&mtx);

    return 0;
}

int increase_count(int count) {
    pthread_mutex_lock(&mtx);     //ocupam mutex

    available_resources += count;  //dam inapoi resurse

    printf("RELEASED %d RESOURCES %d REMAINING\n", count, available_resources);
    pthread_mutex_unlock(&mtx);      //eliberam

    return 0;
}


void* funct(void* arg){
    int *aux = (int*)arg;
    int amount = *aux;

    if(decrease_count(amount) != -1){
       increase_count(amount);
    }

    return NULL;
}

 int main()
 {
    int i;

    if(pthread_mutex_init(&mtx, NULL)){
      perror(NULL);
      return errno;
    }

    for(i = 0; i < nr_threads; i++){
        int *aux;
        aux = (int*)malloc(sizeof(int));
        *aux = v[i];
        pthread_create(&(threads[i]), NULL, funct, aux); //initializam threadul lansat prin apelarea functiei func
    }

    for (i = 0; i < nr_threads; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&mtx);

    return 0;
 }
