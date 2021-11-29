#include <pthread.h>
#include "Monitor_malo.h"
#include <iostream>
using namespace std;

Monitor_malo:: Monitor_malo(int n_h){
    n_hebras = n_h;
    contador = 0;
}
void Monitor_malo::esperar(){
    pthread_mutex_lock(&lock);
    contador++;
    if(contador<n_hebras){
        pthread_cond_wait(&c,&lock);  // Libera mutex y manda signal
        contador--;
        
    }
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&c);

    //cout << contador <<"  "<< n_hebras << endl;
    
    
    
    
}
void Monitor_malo::mandasignal(){
    
    if(contador!=n_hebras){
        contador--;
        pthread_cond_signal(&c);
        cout << endl;
    }
   
}

