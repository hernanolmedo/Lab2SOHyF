#include "funciones.h"

int main(int argc, char *argv[]){
    FILE *archivo=fopen(argv[0],"r");
    int *parametros=fgetsParameters(archivo);
    int ancho=parametros[0];
    int largo=parametros[1];
    char **matriz=fgetMatriz(archivo,largo,ancho);
    
    return 0;
}
