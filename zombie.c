#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "zombie.h"
#include "functions.h"

void* zombieFunc (void* insZombie){ // Puede ser que se decida usar "no_usado" después. Cambiar el nombre en caso de que así sea.
    zombie* zombiePointer=(zombie*)insZombie;
    while(zombiePointer->numero!=turno){
		pthread_barrier_wait (&barrera);
		pthread_barrier_wait(&barrera2);
	}
	matriz[zombiePointer->posY][zombiePointer->posX]='Z';
	pthread_barrier_wait (&barrera);
	pthread_barrier_wait(&barrera2);
    while(1){ // Mientras la persona esta viva
		if(dead(zombiePointer->posX,zombiePointer->posY)){
			pthread_mutex_lock(&mutex);
		    changePosition(&zombiePointer->posX,&zombiePointer->posY,matriz);
			pthread_mutex_unlock(&mutex);
		}
	    pthread_barrier_wait (&barrera);
		pthread_barrier_wait(&barrera2);
    }
	threads--;
	return 0;
    // En este punto ya todas las hebras habrán terminado de hacer lo que tengan que hacer durante el turno.
}
