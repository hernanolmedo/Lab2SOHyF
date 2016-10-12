void* zombie (void* no_usado){ // Puede ser que se decida usar "no_usado" después. Cambiar el nombre en caso de que así sea.
    pthread_barrier_wait (&barrera);
    // En este punto ya todas las hebras habrán terminado de hacer lo que tengan que hacer durante el turno.
}
