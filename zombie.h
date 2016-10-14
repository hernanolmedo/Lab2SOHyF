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
extern pthread_barrier_t barrera;
void* zombieFunc(void* insZombie);

#endif // ZOMBIE_H_INCLUDED
