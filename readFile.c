#include <stdio.h>
#include <stdlib.h>
#include "readFile.h"
#include "person.h"
#include "zombie.h"


/*
fgetParameters
    Argumentos
        Puntero a un objeto FILE (archivo)
    Devuelve
        Un arreglo con los par�metros de la partida
    Descripci�n
        Se leen los par�metros de la partida desde el objeto FILE que tiene los datos del archivo de entrada (se sabe que son 5),
        para que luego sean almacenados en un arreglo de enteros. Este arreglo es lo que devuelve la funci�n.
*/

int* fgetParameters (FILE* file) {
    int* parameters = (int*)malloc(sizeof(int)*5);
    int i = 0;
    char comodin[10];
    for (i=0;i<5;i++) fscanf(file,"%d",&parameters[i]);
    fgets(comodin,10,file);
    return parameters;
}

/*
fgetParameters
    Argumentos
        Puntero a un objeto FILE (archivo) y dos enteros representativos del largo y ancho de una matriz.
    Devuelve
        Una matriz que contiene el tablero en el cual se desarrolla la partida.
    Descripci�n
        Se leen los caracteres que componen el tablero desde el objeto FILE, haciendo un recorrido de este con la funcion
        fscanf, y al mismo tiempo escribiendo los caracteres encontrados en una matriz de dimensiones height por width.
        La matriz con todo el tablero guardado es lo que devuelve esta funci�n.
        Cabe destacar que esta funci�n no resetea el puntero file, por lo que s�lo debe llamarse una vez creado el objeto
        FILE con la respectiva referencia al archivo de entrada, y tambi�n despu�s de llamar a la funci�n fgetParameters de
        manera que el puntero est� posicionado al principio del tablero.

*/

char** fgetMatrix(FILE *file,int height,int width,person *peopleArray,zombie *zombieArray,int ammo,int zombieArrayLenght){
    int i,j;
    int indicePersonArray=0;
    int indiceZombieArray=0;
    int condition=0;
    int contador=0;
    char** matrix=(char**)malloc(sizeof(char*)*(height));
    for(i=0;i<height;i++){
        matrix[i]=(char*)malloc(sizeof(char)*(width+1)); // Se reserva un espacio m�s por cada fila para almacenar los saltos de l�nea
		    for(j=0;j<=width;j++){
            fscanf(file,"%c",&matrix[i][j]);
            if(matrix[i][j]=='P'){
                peopleArray[indicePersonArray].posX=j;
                peopleArray[indicePersonArray].posY=i;
                peopleArray[indicePersonArray].ammo=ammo;
                peopleArray[indicePersonArray].gun=0;
                indicePersonArray++;
            }
            if(matrix[i][j]=='E'&&condition==0){
                condition++;
                while(indiceZombieArray<zombieArrayLenght) {
                    zombieArray[indiceZombieArray].posX=j;
                    zombieArray[indiceZombieArray].posY=i+1;
                    zombieArray[indiceZombieArray].activated=0;
                    zombieArray[indiceZombieArray].numero=contador;
                    contador++;
                    indiceZombieArray++;
                }
            }
        }
	  }
	  return matrix;
}
