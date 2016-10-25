#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "person.h"
#include "functions.h"

void* personFunc (void* insPerson){ // Puede ser que se decida usar "no_usado" despu�s. Cambiar el nombre en caso de que as� sea.
    person* personPointer=(person*)insPerson;
    int d=0;
    while(1){ // Mientras la persona esta viva
		pthread_mutex_lock(&mutex);
		if(dead(personPointer->posX,personPointer->posY)&&d==0){
		    changePosition(&personPointer->posX,&personPointer->posY,matriz);
		    shoot(personPointer->posX,personPointer->posY,matriz,infoMatrix,&personPointer->ammo);
		}
		else d=1;
		pthread_mutex_unlock(&mutex);
	    pthread_barrier_wait (&barrera);
		pthread_barrier_wait(&barrera2);
    }
	threads--;
	return 0;
    // En este punto ya todas las hebras habr�n terminado de hacer lo que ten�an que hacer durante el turno.
}
