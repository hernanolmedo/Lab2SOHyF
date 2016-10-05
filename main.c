#include <time.h>
#include <stdlib.h>
#include <stdio.h>
//#include <pthread.h>
#include "readFile.h"
#include "funciones.h"

int main(int argc, char *argv[]){
    FILE *archivo=fopen(argv[0],"r");
    int *parametros=fgetParameters(archivo);
    int ancho=parametros[0];
    int largo=parametros[1];
    char **matriz=fgetMatrix(archivo,largo,ancho);
    printScreen(largo,ancho,matriz);

    return 0;
}
