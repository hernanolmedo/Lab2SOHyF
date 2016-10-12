void* personFunc (void* insPerson){ // Puede ser que se decida usar "no_usado" despu�s. Cambiar el nombre en caso de que as� sea.
    person* personPointer=(person*)insPerson;
    while(infoMatrix[personPointer->posX][personPointer->posY]==0){ // Mientras la persona esta viva
        move(personPointer->posX,personPointer->posY,matriz);
        shoot(personPointer->posX,personPointer->posY,matriz,infoMatrix,&personPointer->ammo);
        pthread_barrier_wait (&barrera);
    }
    // En este punto ya todas las hebras habr�n terminado de hacer lo que ten�an que hacer durante el turno.
}
