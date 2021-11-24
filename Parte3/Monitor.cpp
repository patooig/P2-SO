#include <pthread.h>
#include <stdio.h>
#include "Monitor.h"

using namespace std;

Monitor::Monitor(int n_h){
    num_hebras = n_h;
    contador = 0;

}

void Monitor::espera(){
    pthread_mutex_lock(&lock);
    contador++;
    if(contador<num_hebras){
        pthread_cond_wait(&c,&lock);  // Libera mutex y manda signal
    }
    else{
        mandasignal();
    }

    pthread_mutex_unlock(&lock);

}

void Monitor::mandasignal(){
    //No es necesario mutex, ultima hebra entra acá

    //if(contador == num_hebras){ // Saco el if???'????????????
    pthread_cond_broadcast(&c); // Despertar todas las hebras
    contador = 0;
    //}

    

}