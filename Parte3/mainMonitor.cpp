#include <iostream>
#include <pthread.h>
//#include "Objeto.h"
#include "Monitor.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

 // var. global

void* f(void *ptr_m){
    //Objeto * o = new Objeto(N);
    Monitor * m_h = (Monitor*)ptr_m;
    int espera = 1+rand()%3;
    printf("Hebra: %d espera %d s\n",pthread_self(), espera);
    sleep(espera);
    m_h->espera();
    return NULL;
}

int main(int argc, char **argv){
    int N,M;
    
    
    N = atoi(argv[1]); //Número de hebras
    M = atoi(argv[2]); //Número de etapas

    Monitor *  m = new Monitor(N);

    int myids[N];
    pthread_t ids[N];

    for (int i = 0; i < N; i++){
        //myids[i] = i;
        pthread_create(&ids[i], NULL, f, m);  // funcion f, monitor m
    }

    for (int i=0; i < N; i++) {
        pthread_join(ids[i], NULL);
    }

    return 0;
}