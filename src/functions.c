#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include "functions.h"

//Descripcion: Entrega una posición de las 8 casillas disponibles además de la casilla actual
//Argumentos: Sin
//Retorna: número del 0 al 8 (9 posibles casillas)
int randomPosition(){
    int r = rand()%9;
    return r;
}

//Descripcion: Dado que de a la persona 30% de probabilidad de sobrevivir y 70% al zombie
//Argumentos: Sin
//Retorna: 0 si vive la persona, 1 si vive el zombie
int whoLives(){
    int r = rand()%10;
    if(r<3) return 0;
    else return 1;
}

//Descripcion: Imprime la pantalla
//Argumentos: altura, ancho, matriz
//Retorna: Nada
void printScreen(int height,int width,char **matrix){
    clear(); // Se limpia la pantalla ncurses
    int i,j;
    char slot;
    char timeString[6];
    struct tm timeStruct; // Se crea una estructura tm para tener el formato MM:SS que será impreso después.
    int timeSeconds=turno; // Se termina de calcular el tiempo transcurrido en segundos.
    int timeMinutes=(int)turno/60;
    int remainingSeconds;
    if(timeMinutes!=0) remainingSeconds=(int)timeSeconds%(timeMinutes*60);
    else remainingSeconds=timeSeconds;
    timeStruct.tm_sec=remainingSeconds;
    timeStruct.tm_min=timeMinutes;
    strftime(timeString,6,"%M:%S",&timeStruct);
    for(i=0;i<height;i++){
        for(j=0;j<=width;j++){
            slot=matrix[i][j];
            switch(slot) {
                case 'P':
                    init_pair(8,COLOR_MAGENTA,COLOR_YELLOW);
                    attron(COLOR_PAIR(8));
                    printw("%c",slot); // Imprime en pantalla ncurses
                    attroff(COLOR_PAIR(8));
                    break;
                case 'Z':
                    init_pair(1,COLOR_GREEN,COLOR_RED);
                    attron(COLOR_PAIR(1));
                    printw("%c",slot); // Imprime en pantalla ncurses
                    attroff(COLOR_PAIR(1));
                    break;
                case 'G':
                    init_pair(2,COLOR_RED,COLOR_CYAN);
                    attron(COLOR_PAIR(2));
                    printw("%c",slot); // Imprime en pantalla ncurses
                    attroff(COLOR_PAIR(2));
                    break;
                case 'X':
                    init_pair(3,COLOR_BLACK,COLOR_WHITE);
                    attron(COLOR_PAIR(3));
                    printw("%c",slot); // Imprime en pantalla ncurses
                    attroff(COLOR_PAIR(3));
                    break;
                case 'd':
                    init_pair(4,COLOR_MAGENTA,COLOR_RED);
                    attron(COLOR_PAIR(4));
                    printw("%c",slot); // Imprime en pantalla ncurses
                    attroff(COLOR_PAIR(4));
                    break;
                case 'z':
                    init_pair(5,COLOR_GREEN,COLOR_BLUE);
                    attron(COLOR_PAIR(5));
                    printw("%c",slot); // Imprime en pantalla ncurses
                    attroff(COLOR_PAIR(5));
                    break;
                case 'E':
                    init_pair(6, COLOR_RED, COLOR_BLACK);
                    attron(COLOR_PAIR(6));
                    printw("%c",slot); // Imprime en pantalla ncurses
                    attroff(COLOR_PAIR(6));
                    break;
                case '0':
                    init_pair(7,COLOR_WHITE,COLOR_BLACK);
                    attron(COLOR_PAIR(7));
                    printw("%c",slot); // Imprime en pantalla ncurses
                    attroff(COLOR_PAIR(7));
                    break;
                case '\n':
                    printw("%c",slot); // Imprime en pantalla ncurses
                    break;/*
                default:
                    printf("Error al imprimir matriz. Caracter inválido.\n\n");
                    exit(-1);*/
            }
        }
    }
    printw("\n"); // Imprime en pantalla ncurses
    printw("Tiempo: %s\n",timeString);
    printw("Personas: %d\n",people);
    printw("Zombies: %d\n",zombies);
    refresh(); // Introduce las impresiones a la pantalla ncurses
}

//Descripcion: Verifica una posicion valida donde moverse y si hay un arma para la persona la toma
//Argumentos: posiciones actuales, matriz, si tiene arma y municiones
//Retorna: Nada
void changePosition(int *posrX,int *posrY,char **matrix,int *gun,int *ammo){
    int number=0,result=0,newX,newY,posX=*posrX,posY=*posrY,flagMove=0;
    while(result==0){
        number=randomPosition();
        if(number==0) result=positionCheker(newX=posX-1,newY=posY-1,matrix);
        else if(number==1) result=positionCheker(newX=posX,newY=posY-1,matrix);
        else if(number==2) result=positionCheker(newX=posX+1,newY=posY-1,matrix);
        else if(number==3) result=positionCheker(newX=posX-1,newY=posY,matrix);
        else if(number==4) {result=1; newX=posX; newY=posY; flagMove=1;}
        else if(number==5) result=positionCheker(newX=posX+1,newY=posY,matrix);
        else if(number==6) result=positionCheker(newX=posX-1,newY=posY+1,matrix);
        else if(number==7) result=positionCheker(newX=posX,newY=posY+1,matrix);
        else if(number==8) result=positionCheker(newX=posX+1,newY=posY+1,matrix);
    }
	if(flagMove==0){
		matrix[newY][newX]=matrix[posY][posX];
		matrix[posY][posX]='0';
	}
    int g=0;//flag arma alrededor
    if(matrix[newY][newX]=='P'){
        if(matrix[newY-1][newX-1]=='G') {g=1; posY=newY-1; posX=newX-1;}
        else if(matrix[newY-1][newX]=='G') {g=1; posY=newY-1; posX=newX;}
        else if(matrix[newY-1][newX+1]=='G') {g=1; posY=newY-1; posX=newX+1;}
        else if(matrix[newY][newX-1]=='G') {g=1; posY=newY; posX=newX-1;}
        else if(matrix[newY][newX+1]=='G') {g=1; posY=newY; posX=newX+1;}
        else if(matrix[newY+1][newX-1]=='G') {g=1; posY=newY+1; posX=newX-1;}
        else if(matrix[newY+1][newX]=='G') {g=1; posY=newY+1; posX=newX;}
        else if(matrix[newY+1][newX+1]=='G') {g=1; posY=newY+1; posX=newX+1;}
    }
    if((g==1)&&((*gun)==0)){
		matrix[posY][posX]='0';
        (*gun)=1;
        (*ammo)=(*ammo)+ammoPerGun;
    }
	  *posrX=newX;
	  *posrY=newY;
}

//Descripcion: Primer movimiento de los zombies desde la entrada
//Argumentos: Posición inicial zombies, matriz
//Retorna: 1 si logra moverse, 0 si no
int m(int *posrX,int *posrY,char **matrix){
    int number=0,result=0,newX,newY,posX=*posrX,posY=*posrY;
    while(result==0){
        number=rand()%4;
        if(number==0) {
		result=1;
		return 0;
	}
        else if(number==1) result=positionCheker(newX=posX-1,newY=posY+1,matrix);
        else if(number==2) result=positionCheker(newX=posX,newY=posY+1,matrix);
        else if(number==3) result=positionCheker(newX=posX+1,newY=posY+1,matrix);
    }
    matrix[newY][newX]='Z';
	*posrX=newX;
	*posrY=newY;
	return 1;
}

//Descripcion: Verifica que una posición este libre '0'
//Argumentos: Posición a verificar y matriz
//Retorna: 1 si es posible, 0 cc
int positionCheker(int posX,int posY,char **matrix){
    if(matrix[posY][posX]=='0') return 1;
    return 0;
}

//Descripcion: Analiza si no quedan personas (ganan zombies) o biceversa
//Argumentos: Altura, ancho, matriz, numero de zombies, array de estructura de zombies
//Retorna: 0 si aun no termina, 1 si ganan personas y 2 si lo hacen los zombies
int gameOver(int height,int width,char **matrix,int nzombies,zombie *zombieArray){
    int i,j,countP=0,countZ=0,act=0;
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            if(matrix[i][j]=='P') countP++;
            else if(matrix[i][j]=='Z'||matrix[i][j]=='d') countZ++;
        }
    }
    for(i=0;i<nzombies;i++){
    	if(zombieArray[i].activated==0){
    		act=1;
    	}
    }
    if(act==0){
		if(countZ==0) return 1;// ganan las personas
		else if(countP==0) return 2;// ganan los zombies
	}
    return 0;
}

//Descripcion: Verifica si a la posicion donde se mueve la persona hay un zombie y decide quien gana
//Argumentos: Posicion persona, matriz, infomatrix (estado cadaveres), municiones, arma
//Retorna: Nada
void shoot(int posX,int posY,char **matrix,int **infoMatrix,int *ammo,int *gun){
	int targetX,targetY;
    if(matrix[posY-1][posX]=='Z'){targetY=posY-1; targetX=posX;}
    else if(matrix[posY+1][posX]=='Z'){targetY=posY+1; targetX=posX;}
    else if(matrix[posY][posX+1]=='Z'){targetY=posY; targetX=posX+1;}
    else if(matrix[posY][posX-1]=='Z'){targetY=posY; targetX=posX-1;}
    else if(matrix[posY-1][posX+1]=='Z'){targetY=posY-1; targetX=posX+1;}
    else if(matrix[posY-1][posX-1]=='Z'){targetY=posY-1; targetX=posX-1;}
    else if(matrix[posY+1][posX+1]=='Z'){targetY=posY+1; targetX=posX+1;}
    else if(matrix[posY+1][posX-1]=='Z'){targetY=posY+1; targetX=posX-1;}
    else return;
	  if(whoLives()==0){
        if(((*gun)==1)&&((*ammo)>0)){
          infoMatrix[targetY][targetX]=1;
          matrix[targetY][targetX]='z';
          (*ammo)--;
          zombies--;
        }
    }
    else{
      infoMatrix[posY][posX]=1;
      matrix[posY][posX]='d';
      people--;
      zombies++;
    }
}

//Descripcion: Analiza si el ser esta muerto, si la posicion es 0 no lo esta
//Argumentos: Posicion actual del ser
//Retorna: 1 si esta vivo, 0 si no
int dead(int posX,int posY){
	if(infoMatrix[posY][posX]==0) return 1;
	return 0;
}

//Descripcion: Analiza el estado de los cadaveres, los deteriora hasta que desaparecen o se convierten
//Argumentos: Datos matriz e infoMatrix
//Retorna: Nada
void corpses(int height,int width,char **matrix,int **infoMatrix){
    int i,j;
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
          	if(infoMatrix[i][j]==1) infoMatrix[i][j]=2;
            else if(infoMatrix[i][j]==2) infoMatrix[i][j]=3;
            else if(infoMatrix[i][j]==3){
                if(matrix[i][j]=='z') matrix[i][j]='0';
                infoMatrix[i][j]=0;
            }
        }
    }
}
