#ifndef ZOMBIE_H_INCLUDED
#define ZOMBIE_H_INCLUDED

typedef struct zombieStr{
    int posX,posY;
    int activated=0;
}zombie;

extern pthread_barrier_t barrera;
void* zombie(void* insZombie);

#endif // ZOMBIE_H_INCLUDED
