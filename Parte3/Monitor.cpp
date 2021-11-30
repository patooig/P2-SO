#include <pthread.h>
#include <stdio.h>
#include "Monitor.h"
#include <iostream>

using namespace std;

//En el constructor se guardan el número de hebras
//Se inicializa el contador en 0
Monitor::Monitor(int n_h){
    num_hebras = n_h;
    contador = 0;
}

//Método para que las hebras esperen en la barrera
void Monitor::espera(){
    //Mutex para la variable contador
    pthread_mutex_lock(&lock);
    contador++;

    //Si no es la última hebra
    if(contador<num_hebras){
        //Libera mutex y manda signal
        pthread_cond_wait(&c,&lock);  
    }

    //Si es la última hebra despierta a las demás
    else{
        mandaSignal();
    }

    //Libera el mutex
    pthread_mutex_unlock(&lock);
}

void Monitor::mandaSignal(){
    //No es necesario mutex, ultima hebra entra acá
    contador = 0;
    // Despertar todas las hebras
    pthread_cond_broadcast(&c);
    cout << endl;  
}