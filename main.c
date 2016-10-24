#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "readFile.h"
#include "functions.h"
#include "zombie.h"
#include "person.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrera; // Se declara un objeto barrier (barrera).
pthread_barrier_t barrera2;
char** matriz;
int ** infoMatrix;
int threads;
int turno;

void pS(int height,int width,int **matrix){
    int i,j;
    for(i=0;i<height;i++){
        for(j=0;j<=width;j++){
            printf("%d",matrix[i][j]);
        }
        printf("\n");
    }
	printf("\n");
}

void f(int height,int width){
    int i,j;
	printf("\n\n");
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            printf("[%d][%d]  ",i,j);
        }
		printf("\n\n");
    }
	printf("\n\n");
}

int main(int argc, char *argv[]){
    //Lectura e impresi�n de la matriz (tablero de la simulaci�n)
    turno=0;
    FILE* archivo=fopen(argv[1],"r");
    int* parametros=fgetParameters(archivo); //Se leen los par�metros desde el archivo de entrada.
    int ancho=parametros[0];
    int largo=parametros[1];
    int zombies=parametros[2];
    int people=parametros[3];
    int ammo = parametros[4];
    int zombieArrayLenght=zombies+people;
    threads = zombies + people + 1;
    person peopleArray[people]; // Se crean arreglos en donde se almacenan estructuras person y zombie.
    zombie zombieArray[zombieArrayLenght];
    matriz=fgetMatrix(archivo,largo,ancho,peopleArray,zombieArray,ammo,zombieArrayLenght); //Se crea la matriz con los datos del archivo de entrada.
	  printScreen(largo,ancho,matriz); //Se imprime la matriz.

	  int i,j; // Contadores para prop�sitos varios
		
		
	srand(time(NULL));
	  // Se crea una matriz de igual tama�o que matriz para realizar verificaciones entre turnos durante la partida.
	  infoMatrix = (int**)malloc(sizeof(int*)*largo);
    for(i=0;i<largo;i++){
        infoMatrix[i]=(int*)malloc(sizeof(int)*ancho);
		    for(j=0;j<ancho;j++) infoMatrix[i][j]=0;
	  }

    //Creaci�n de hebras
    //Creaci�n de la barrera para manejar hebras durante el turno.
    pthread_barrier_init (&barrera, NULL, threads); // El 3er argumento representa el n�mero de threads que deben realizar sus tareas.
	  pthread_barrier_init (&barrera2, NULL, threads);
    pthread_t zombieThreads[zombies];
    pthread_t personThreads[people];
    for(i=0;i<zombies;i++) pthread_create (&zombieThreads[i], NULL, zombieFunc, &zombieArray[i]);
    for(i=0;i<people;i++) pthread_create (&personThreads[i], NULL, personFunc, &peopleArray[i]);

    /*
    C�digo por escribir...
    - Creaci�n de los threads.
    - Posiblemente, la implementaci�n del sistema de turnos.
    Nota: Se debe llevar la cuenta de los threads creados para poder usar barrier correctamente.
    */
	f(largo,ancho);
	pthread_barrier_wait(&barrera);
    while(gameOver(largo,ancho,matriz)){
        printScreen(largo,ancho,matriz);
        pS(largo,ancho,infoMatrix);
		f(largo,ancho);
        sleep(1);
        turno++;
        corpses(largo,ancho,matriz,infoMatrix);
        pthread_barrier_wait(&barrera2);
        pthread_barrier_wait(&barrera);
    	// En este punto ya todas las hebras habr�n terminado de hacer lo que ten�an que hacer durante el turno.
    }
    return 0;
}
