#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 1000
int saldo;
pthread_mutex_t saldoLock = PTHREAD_MUTEX_INITIALIZER;

//Cada hilo corre una funcion en particular
void * suma100(void *arg){  // al tener un void * , se le puede pasar cualquier tipo de direccion
    //char *c =(char *)arg; 
    //printf("Hola desde un hilo %s \n",c);
    int lsaldo;
    pthread_mutex_lock(&saldoLock); // Se pone candado
    //Region critica
    lsaldo = saldo;
    lsaldo += 100;
    saldo = lsaldo;
    pthread_mutex_unlock(&saldoLock); // Se quita el candado
    pthread_exit(NULL);
}

int main(){
    pthread_t threads[NUM_THREADS]; // arreglo que guarda los ID de los hilos a crear
    saldo = 0;
    char *s = "Soy un argumento";
    for(int i = 0; i < NUM_THREADS; i++){
        pthread_create(&threads[i],NULL,suma100,NULL);
    }
    for(int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i],NULL);
    }
    printf("Saldo final es %d\n",saldo);
    pthread_exit(NULL);
}
