#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

void* person (void* no_usado){ // Puede ser que se decida usar "no_usado" después. Cambiar el nombre en caso de que así sea.
    pthread_barrier_wait (&barrera);
    // En este punto ya todas las hebras habrán terminado de hacer lo que tenían que hacer durante el turno.
}

#endif // PERSON_H_INCLUDED
