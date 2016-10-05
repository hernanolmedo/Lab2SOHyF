#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib>
#include <pthread.h>
#include "readFile.h"

int posicionRandom(){
  srand(time(NULL));
  int r = rand()%7; 
}

void mostrarPantalla(int largo,int ancho){
    int i,j;
    for(i=0;i<largo;i++){
        for(j=0;j<=ancho;j++) printf("%c",matriz[i][j]);
    }
}

#endif
