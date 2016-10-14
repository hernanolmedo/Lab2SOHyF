#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

typedef struct personStr{
    int posX,posY;
    int gun;
    int ammo;
}person;

extern char** matriz;
extern int ** infoMatrix;
extern pthread_barrier_t barrera;
void* personFunc(void* insPerson);

#endif // PERSON_H_INCLUDED
