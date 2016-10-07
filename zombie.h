#ifndef ZOMBIE_H_INCLUDED
#define ZOMBIE_H_INCLUDED

void* zombie (void* no_usado){ // Puede ser que se decida usar "no_usado" después. Cambiar el nombre en caso de que así sea.
    pthread_barrier_wait (&barrera);
    // En este punto ya todas las hebras habrán terminado de hacer lo que tenían que hacer durante el turno.
}

#endif // ZOMBIE_H_INCLUDED
