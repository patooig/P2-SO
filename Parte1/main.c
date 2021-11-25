#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

pthread_barrier_t mibarrerabonita; // Barrera
int M; // Etapas


void* f(void *id){
    int id_h = *(int*)id; // id de hebra
    int espera;
    for (int i = 0; i < M; i++){

        espera = 1 + rand() % 3;
        printf("M = %d, Hebra %d espera por %d seg\n",i+1,id_h,espera);
        sleep(espera); // "TRABAJO DE LA HEBRA"
        pthread_barrier_wait(&mibarrerabonita); // Hebra espera
    }
    
    printf("Hebra %d termina\n",id_h);

    return NULL;
}

int main(int argc, char **argv){
    srand(time(NULL));
    // Crear variables 
    int N;
    int i;
    N = atoi(argv[1]); //Número de hebras
    M = atoi(argv[2]); //Número de etapas
    int myids[N];      // Arreglo de id's
    pthread_t ids[N];  // Hebras
    

    // Inicializamos barreras
    pthread_barrier_init(&mibarrerabonita, NULL, N+1);

    // Creamos N hebras y asignamos id's
    for ( i=0; i < N; i++) {
        myids[i] = i;
        pthread_create(&ids[i], NULL, f, &myids[i]);
    }

    
    //Hebra main espera
    for ( int j = 0; j < M; j++){
        printf("espero..\n");
        pthread_barrier_wait(&mibarrerabonita);
    }

    //Hebra main espera por las N hebras
    for (int i=0; i < N; i++) {
        pthread_join(ids[i], NULL);
    }

    printf("main() termina\n");
    
    // Destruimos barrera
    pthread_barrier_destroy(&mibarrerabonita);

return 0;

}