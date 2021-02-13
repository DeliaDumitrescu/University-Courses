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
#include <semaphore.h>

pthread_mutex_t mtx;
sem_t sem;

int count;
int nr_threads = 5; //poate fi inlocuit cu alta valoare
pthread_t threads[5];

void init(int n){
  count = n;
  if(pthread_mutex_init(&mtx, NULL)){
     perror(NULL);
     return errno;
  }
}

void barrier_point(){
  pthread_mutex_lock(&mtx);    //ca sa nu facem count-- in ac timp
  count--;
  if(!count){
    pthread_mutex_unlock(&mtx);  //!!!
    sem_post(&sem);
    return;
  }
  pthread_mutex_unlock(&mtx);
  sem_wait(&sem); // -
  sem_post(&sem); // +
}

void *tfun(void *arg){
  int *tid = (int *)arg;

  printf("%d reached the barrier \n", *tid);
  barrier_point();
  printf("%d passed the barrier \n", *tid);

  free(tid);
  return NULL;
}

int main()
{
  int i;

  if(sem_init(&sem,0,0)){
     perror(NULL);
     return errno;
  }

  init(nr_threads);
  printf("NTHRS = %d\n", nr_threads);

  for(i = 0; i < nr_threads; i++){
    int *aux;
    aux = (int*)malloc(sizeof(int));
    *aux = i;

    if(pthread_create(&threads[i], NULL, tfun, aux)){
        perror(NULL);
        return errno;
    }
  }

  for(i = 0; i < nr_threads; i++){
    if(pthread_join(threads[i], NULL)){
        perror(NULL);
        return errno;
    }
  }

  pthread_mutex_destroy(&mtx);
  sem_destroy(&sem);

  return 0;
}