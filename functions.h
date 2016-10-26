#include "zombie.h"

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

extern char** matriz;
extern int ** infoMatrix;
extern int ammoPerGun;
extern int zombies;
extern int people;
int randomPosition();
int whoLives();
void printScreen(int height,int width,char **matrix,clock_t startTime);
void changePosition(int *posX,int *posY,char **matrix,int *gun,int *ammo);
int m(int *posrX,int *posrY,char **matrix);
int positionCheker(int posX,int posY,char **matrix);
int gameOver(int height,int width,char **matrix,int zombies,zombie *zombieArray);
void shoot(int posX,int posY,char **matrix,int **infoMatrix,int *ammo,int *gun);
int dead(int posX,int posY);
void corpses(int height,int width,char **matrix,int **infoMatrix);

#endif
