#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "zombie.h"
#include "functions.h"

void* zombieFunc (void* insZombie){ // Puede ser que se decida usar "no_usado" después. Cambiar el nombre en caso de que así sea.
    zombie* zombiePointer=(zombie*)insZombie;
    while(matriz[zombiePointer->posX][zombiePointer->posY]!='z'){ // Mientras la persona esta viva
        move(zombiePointer->posX,zombiePointer->posY,matriz);
        pthread_barrier_wait (&barrera);
    }
	return 0;
    // En este punto ya todas las hebras habrán terminado de hacer lo que tengan que hacer durante el turno.
}
