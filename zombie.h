#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#ifndef ZOMBIE_H_INCLUDED
#define ZOMBIE_H_INCLUDED

typedef struct zombieStr{
    int posX;
    int posY;
    int activated;
}zombie;

extern char** matriz;
extern int ** infoMatrix;
extern int threads;
extern pthread_barrier_t barrera;
extern pthread_barrier_t barrera2;
extern pthread_mutex_t mutex;
void* zombieFunc(void* insZombie);

#endif // ZOMBIE_H_INCLUDED
