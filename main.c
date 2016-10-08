#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "readFile.h"
#include "funciones.h"
#include "zombie.h"
#include "person.h"

pthread_barrier_t barrera; // Se declara un objeto barrier (barrera).

int main(int argc, char *argv[]){

    //Lectura e impresi�n de la matriz (tablero de la simulaci�n)
    FILE* archivo=fopen(argv[1],"r");
    int* parametros=fgetParameters(archivo); //Se leen los par�metros desde el archivo de entrada.
    int ancho=parametros[0];
    int largo=parametros[1];
    char** matriz=fgetMatrix(archivo,largo,ancho); //Se crea la matriz con los datos del archivo de entrada.
	  printScreen(largo,ancho,matriz); //Se imprime la matriz.

	  int i,j; // Contadores para prop�sitos varios

	  // Se crea una matriz de igual tama�o que matriz para realizar verificaciones entre turnos durante la partida.
	  int ** infoMatrix = (int**)malloc(sizeof(int*)*largo);
	  for(i=0;i<ancho;i++) infoMatrix[i]=(int*)malloc(sizeof(int)*ancho);
    for(i=0;i<largo;i++){
		    for(j=0;j<ancho;j++) infoMatrix[i][j]=0;
	  }

    //Creaci�n de hebras
    int zombies=parametros[2];
    int people=parametros[3];
	  int threads = zombies + people + 1;

    //Creaci�n de la barrera para manejar hebras durante el turno.
    pthread_barrier_init (&barrera, NULL, threads); // El 3er argumento representa el n�mero de threads que deben realizar sus tareas.
    pthread_t zombieThreads[zombies];
    pthread_t personThreads[people];
    for(i=0;i<zombies;i++) pthread_create (&zombieThreads[i], NULL, zombie, NULL);
    for(i=0;i<people;i++) pthread_create (&personThreads[i], NULL, person, NULL);

    /*
    C�digo por escribir...
    - Creaci�n de los threads.
    - Posiblemente, la implementaci�n del sistema de turnos.
    Nota: Se debe llevar la cuenta de los threads creados para poder usar barrier correctamente.
    */

    pthread_barrier_wait(&barrera);
    // En este punto ya todas las hebras habr�n terminado de hacer lo que ten�an que hacer durante el turno.

    return 0;
}
