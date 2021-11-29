#include <pthread.h>

using namespace std;

class Monitor_malo{
    private:
    int n_hebras;
    int contador;
    pthread_mutex_t lock;
    pthread_cond_t c;

    public: 
    Monitor_malo(int n_h);
    void esperar();
    void mandasignal();


};