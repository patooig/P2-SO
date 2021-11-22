#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define MAX 10 

pthread_barrier_t mybarrier;

void* myf(void *id_ptr) {
  int thread_id = *(int*)id_ptr;
  int wait_sec = 1 + rand() % 5;
  printf("thread %d: espera por %d secs.\n", thread_id, wait_sec);
  sleep(wait_sec);
  printf("thread %d: Lista ...\n", thread_id);

  pthread_barrier_wait(&mybarrier);

  printf("thread %d: puede terminar\n", thread_id);
  return NULL;
}


int main(int argc, char *argv[]) {
  int i;
  pthread_t ids[MAX];
  int myids[MAX];

  if(argc != 2){
	printf("%s Nthreads\n",argv[0]);
	exit(1);
  }

  int nthreads = atoi(argv[1]); 
  srand(time(NULL));
  pthread_barrier_init(&mybarrier, NULL, nthreads + 1);

  for (i=0; i < nthreads; i++) {
    myids[i] = i;
    pthread_create(&ids[i], NULL, myf, &myids[i]);
  }

  printf("main() listo.\n");

  pthread_barrier_wait(&mybarrier);

  printf("main() puede terminar\n");

  for (i=0; i < nthreads; i++) {
    pthread_join(ids[i], NULL);
  }

  printf(" step 2\n");
  for (i=0; i < nthreads; i++) {
    myids[i] = i;
    pthread_create(&ids[i], NULL, myf, &myids[i]);
  }
  printf("main() listo step 2.\n");

  pthread_barrier_wait(&mybarrier);

  printf("main() puede terminar\n");

  for (i=0; i < nthreads; i++) {
    pthread_join(ids[i], NULL);
  }
  pthread_barrier_destroy(&mybarrier);

  return 0;
}
