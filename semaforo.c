#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t mutex;
sem_t b;
int cont = 0;

int N,M;

void barrera(void *id){
    int id_h = *(int*)id; // id_h = id hebra

    sem_wait(&mutex);
    cont++;
    if(cont < N){
        sem_post(&mutex);
        sem_wait(&b);
    }
    else{
        sem_post(&mutex); //signal
        cont = 0;

        for(int i = 1; i < N; i++){
            sem_post(&b); // signal
        }
    }

}

void barreramalo(){

}


int main(int argc, char **argv){

    N = atoi(argv[1]); //Número de hebras
    M = atoi(argv[2]); //Número de etapas

    sem_init(&mutex, 1, 1);
    sem_init(&b, 1, 0);

    //Crear las N hebras
    int myids[N];
    pthread_t ids[N];
    

    for (int i = 0; i < N; i++){

        pthread_create(&ids[i], NULL, barrera, &myids[i]);
    }

    for (int i=0; i < N; i++) {
        pthread_join(ids[i], NULL);
    }


    for (int i = 0; i < N; i++){
        pthread_create(&ids[i], NULL, barreramalo, &myids[i]);
    }
    

    return 0;
}