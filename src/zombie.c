#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "zombie.h"
#include "functions.h"

void* zombieFunc (void* insZombie){ // Puede ser que se decida usar "no_usado" después. Cambiar el nombre en caso de que así sea.
	int d=0,r=0;
    zombie* zombiePointer=(zombie*)insZombie;
    while(zombiePointer->numero!=turno){
		pthread_barrier_wait (&barrera);
		pthread_barrier_wait(&barrera2);
	}
		// Mientras la zombie este vivo
		while(r==0){ // r es una flag que guarda el resultado de m, vale 1 cuando el zombie salió de la entrada
				pthread_mutex_lock(&mutex);
	    	r=m(&zombiePointer->posX,&zombiePointer->posY,matriz);
				pthread_mutex_unlock(&mutex);
	    	pthread_barrier_wait (&barrera);
				pthread_barrier_wait(&barrera2);
    }

		// Cuando el zombie ya salió de la entrada
    while(1){
    		zombiePointer->activated=1;
				pthread_mutex_lock(&mutex);
				if(dead(zombiePointer->posX,zombiePointer->posY)&&d==0){
		    		changePosition(&zombiePointer->posX,&zombiePointer->posY,matriz,NULL,NULL);
				}
				else d=1; // Esta flag se activa cuando el zombie ha muerto
				pthread_mutex_unlock(&mutex);
	    	pthread_barrier_wait (&barrera);
				pthread_barrier_wait(&barrera2);
    }
		threads--;
		return 0;
    // En este punto ya todas las hebras habrán terminado de hacer lo que tengan que hacer durante el turno.
}
