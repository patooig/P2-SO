//Compilar agregando "-pthread -lrt"

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t mutex;
sem_t b;
int cont;

int N,M;

void barrera(){

    sem_wait(&mutex);
    cont++;
    if(cont < N){
        sem_post(&mutex);
        sem_wait(&b);
    }
    else{
        sem_post(&mutex); //signal
        cont = 0;

        printf("\n"); //Salto de linea para ver las etapas

        for(int i = 1; i < N; i++){
            sem_post(&b); // signal
        }
    }
}
void barrera_mala(){

    sem_wait(&mutex);
    cont++;
    if(cont == N){
        cont = 0;
        sem_post(&b);
        printf("\n");
        
    }
    sem_post(&mutex);
    sem_wait(&b);
    sem_post(&b);

}

//Función que llaman las hebras
void* f(void *id){

    int id_h = *(int*)id; // id_h = id hebra
    
    for (int i = 0; i < M; i++){

        //Se espera un tiempo aleatorio
        int espera = 1 + rand() % 3;
        printf("M = %d, Hebra: %d espera por %d seg\n",i+1,id_h,espera);
        sleep(espera); // "TRABAJO DE LA HEBRA"
        
        barrera_mala(); //Llama a la barrera
    }
    
    printf("Hebra %d termina\n",id_h);

    return NULL;
}


int main(int argc, char **argv){

    N = atoi(argv[1]); //Número de hebras
    M = atoi(argv[2]); //Número de etapas

    //Se inicializa el semáforo mutex en 1
    sem_init(&mutex, 1, 1);


    //Se inicializa el semáforo b en 0
    sem_init(&b, 1, 0);

    int i;

    //Crear las N hebras
    int myids[N];
    pthread_t ids[N];
    cont = 0;
    
    for (i = 0; i < N; i++){
        myids[i] = i;
        pthread_create(&ids[i], NULL, f, &myids[i]);
    }

    for (i=0; i < N; i++) {
        pthread_join(ids[i], NULL);
    }

    return 0;
}