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
extern int threads;
extern pthread_barrier_t barrera;
extern pthread_barrier_t barrera2;
extern pthread_mutex_t mutex;
void* personFunc(void* insPerson);

#endif // PERSON_H_INCLUDED
