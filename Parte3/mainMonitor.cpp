#include <iostream>
#include <pthread.h>
#include "Monitor.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "Monitor_malo.h"

using namespace std;

int M; //Etapas

/*void* f(void* m){

    Monitor * m_h = (Monitor*)m;

    int espera;
    for (int i = 0; i < M; i++){
        
        espera = 1+rand()%5;
        printf("M = %d, Hebra: %ld espera por %d seg\n",i+1,pthread_self(),espera);
        sleep(espera);
        m_h->espera();
    }
    
    printf("Hebra: %ld termina\n",pthread_self());
    return NULL;
}
*/

void * f_bad(void * m){
    Monitor_malo * m_h = (Monitor_malo*)m;

    int espera;
    for (int i = 0; i < M; i++){
        
        espera = 1+rand()%5;
        printf("M = %d, Hebra: %ld espera por %d seg\n",i+1,pthread_self(),espera);
        sleep(espera);
        m_h->esperar();
    }
    
    printf("Hebra: %ld termina\n",pthread_self());
    return NULL;

}
int main(int argc, char **argv){
    srand(time(NULL));
    int N;
    
    
    N = atoi(argv[1]); //Número de hebras
    M = atoi(argv[2]); //Número de etapas

    Monitor *  moni = new Monitor(N);  //Creamos monitor
    Monitor_malo * mm = new Monitor_malo(N);
 
    int myids[N];           
    pthread_t ids[N];

    for (int i = 0; i < N; i++){
        pthread_create(&ids[i], NULL, f_bad, mm);//moni); 
    }

    for (int i=0; i < N; i++) {
        pthread_join(ids[i], NULL);
    }

    printf("Main termina\n");
    return 0;
}