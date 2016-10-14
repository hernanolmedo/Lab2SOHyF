#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "zombie.h"

void* zombieFunc (void* insZombie){ // Puede ser que se decida usar "no_usado" después. Cambiar el nombre en caso de que así sea.
    zombie* zombiePointer=(zombie*)insZombie;
    while(1){
        pthread_barrier_wait (&barrera);
    }
    // En este punto ya todas las hebras habrán terminado de hacer lo que tengan que hacer durante el turno.
}
