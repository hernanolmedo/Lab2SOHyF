#ifndef ZOMBIE_H_INCLUDED
#define ZOMBIE_H_INCLUDED

extern pthread_barrier_t barrera;

void* zombie (void* no_usado){ // Puede ser que se decida usar "no_usado" despu�s. Cambiar el nombre en caso de que as� sea.
    pthread_barrier_wait (&barrera);
    // En este punto ya todas las hebras habr�n terminado de hacer lo que ten�an que hacer durante el turno.
}

#endif // ZOMBIE_H_INCLUDED
