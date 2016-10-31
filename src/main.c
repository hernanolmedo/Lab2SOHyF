#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <ncurses.h>
#include "readFile.h"
#include "functions.h"
#include "zombie.h"
#include "person.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrera; // Esta primera barrera sirve para que las hebras se sincronicen por turnos .
pthread_barrier_t barrera2; // Esta otra barrera sirve para que la hebra principal realice las impresiones cada 1 seg, entre turnos.
char** matriz; // Matriz en donde se almacena el tablero. 
int ** infoMatrix; // Matríz para manejar las unidades que están vivas y muertas y por cuando tiempo lo han estado.
int threads; // Catidad de hebras.
int turno; // Se lleva la cuenta de los turnos.
int ammoPerGun; // Balas por pistola.
int zombies; // Cantidad de zombies.
int people; // Cantidad de personas.

int main(int argc, char *argv[]){
    //Lectura e impresi�n de la matriz (tablero de la simulaci�n)
    turno=0;
    FILE* archivo=fopen(argv[1],"r");
    int* parametros=fgetParameters(archivo); //Se leen los par�metros desde el archivo de entrada.
    int ancho=parametros[0];
    int largo=parametros[1];
	int win;
    zombies=parametros[2];
    people=parametros[3];
    ammoPerGun = parametros[4];
    // Verificaciones de la entrada
    if (((ancho<4)&&(largo<3))||((ancho<3)&&(largo<4))) {
        printf("Las dimensiones de la matriz no son adecuadas para la simulación. Edite el archivo de entrada.");
        return -1; // Se verifica que las dimensiones de la matriz sean los mínimos permitidos
    }
    if ((zombies<1)||(people<1)){
        printf("La cantidad de zombies o de personas debe ser superior a 0. Edite el archivo de entrada.");
        return -1; // para poder llevar a cabo la simulación.
    }

    threads = zombies + people + 1; // Numero de zombies + numero de personas + 1 hebra principal
    person peopleArray[people]; // Se crean arreglos en donde se almacenan estructuras person y zombie.
    zombie zombieArray[zombies];
    matriz=fgetMatrix(archivo,largo,ancho,peopleArray,zombieArray,ammoPerGun,zombies); //Se crea la matriz con los datos del archivo de entrada.
    initscr(); // Se inicia el modo ncurses
    if(has_colors() == FALSE){ // Se verifica si el terminal soporta colores
        endwin();
        printf("ERROR: Su terminal no soporta colores.\n");
        return -1;
    }
    start_color(); // Se activa el modo color del terminal.
    printScreen(largo,ancho,matriz); //Se imprime la matriz.

	  int i,j; // Contadores para prop�sitos varios

	  srand(time(NULL)); // Se crea un número al azar para su uso posterior en algoritmos de movimiento.

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

	  pthread_barrier_wait(&barrera); // Se termina el primer turno
    sleep(1); // Se hace una espera de 1 seg al iniciar la partida para apreciar el estado inicial de la pantalla
    while(!(win=gameOver(largo,ancho,matriz,zombies,zombieArray))){ // Ciclo principal de la simulacion
        printScreen(largo,ancho,matriz); // Se imprime la pantalla...
        sleep(1); // cada aprox. 1 seg
        turno++; // se aumenta el turno
        pthread_barrier_wait(&barrera2); // Aqui termina el entre turno.
        pthread_barrier_wait(&barrera); // Comienza un nuevo turno
        corpses(largo,ancho,matriz,infoMatrix); // Se verivida infoMatrix para ver si hay muertos y cuanto tiempo lo han estado
    	  // En este punto ya todas las hebras habr�n terminado de hacer lo que ten�an que hacer durante el turno.
    }
	  printScreen(largo,ancho,matriz); // Se imprime la pantalla por ultima vez.
	  printw("GAME OVER. Ganararon ");
	if(win==1) printw("las personas\n\n");
	else printw("los zombies\n\n");
    printw("Presione una tecla para salir..."); 
    refresh();
    getch();
    endwin(); // Se cierra el modo ncurses en repuesta a que el usuario presione una tecla.
    return 0; // Se termina el programa.
}
