#include <iostream>
#include <pthread.h>
#include "Monitor.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int M; //Cantidad de etapas

//Funcion de la hebra, recibe por argumento monitor.
void* f(void* m){

    Monitor * m_h = (Monitor*)m;

    int espera;
    for (int i = 0; i < M; i++){
        // Espera de valor aleatorio
        espera = 1+rand()%5;
        printf("M = %d, Hebra: %ld espera por %d seg\n",i+1,pthread_self(),espera);
        sleep(espera); //Trabajo de la hebra
        m_h->espera(); // Llama método de monitor
    }
    //Hebra termina
    printf("Hebra: %ld termina\n",pthread_self());
    return NULL;
}

int main(int argc, char **argv){
    
    srand(time(NULL));
    int N; //Cantidad de hebras
    
    N = atoi(argv[1]); //Número de hebras
    M = atoi(argv[2]); //Número de etapas

    Monitor *  moni = new Monitor(N);  //Creamos monitor
    
    //Se crean las N hebras y pasamos funcion f y monitor
    int myids[N];           
    pthread_t ids[N];

    for (int i = 0; i < N; i++){
        pthread_create(&ids[i], NULL, f, moni);
    }

    //Se unen las N hebras y main esperar que terminen.
    for (int i=0; i < N; i++) {
        pthread_join(ids[i], NULL);
    }

    // Se libera memoria de monitor
    delete moni;

    printf("Main termina\n");
    return 0;
}