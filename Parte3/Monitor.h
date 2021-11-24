#include <pthread.h>

class Monitor{

    private:
    pthread_mutex_t lock;
    pthread_cond_t c;
    int num_hebras;
    int contador;
    void mandasignal();

    public:
    Monitor(int n_h);
    void espera();
    
};