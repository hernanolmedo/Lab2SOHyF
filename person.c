#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "person.h"
#include "functions.h"

void* personFunc (void* insPerson){ // Puede ser que se decida usar "no_usado" despu�s. Cambiar el nombre en caso de que as� sea.
    person* personPointer=(person*)insPerson;
    while(1){ // Mientras la persona esta viva
		if(dead(personPointer->posX,personPointer->posY)){
			pthread_mutex_lock(&mutex);
		    move(personPointer->posX,personPointer->posY,matriz);
		    shoot(personPointer->posX,personPointer->posY,matriz,infoMatrix,&personPointer->ammo);
			pthread_mutex_unlock(&mutex);
		}
	    pthread_barrier_wait (&barrera);
		pthread_barrier_wait(&barrera2);
    }
	threads--;
	return 0;
    // En este punto ya todas las hebras habr�n terminado de hacer lo que ten�an que hacer durante el turno.
}
