#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

typedef struct personStr{
    int posX,posY;
    int gun=0;
    int ammo;
}person;

extern pthread_barrier_t barrera;
void* person(void* insPerson);

#endif // PERSON_H_INCLUDED
