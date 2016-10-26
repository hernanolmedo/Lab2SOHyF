#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "functions.h"

int randomPosition(){
    int r = rand()%9;
    return r;
}

int whoLives(){
    int r = rand()%10;
    if(r<3) return 0;
    else return 1;
}

void printScreen(int height,int width,char **matrix,clock_t startTime){
    clear(); // Se limpia la pantalla ncurses
    int i,j;
    char slot;
    char timeString[6];
    struct tm timeStruct;
    clock_t elapsedTime=clock()-startTime;
    int timeSeconds=(int)(elapsedTime*1000/CLOCKS_PER_SEC); // Se termina de calcular el tiempo transcurrido en segundos.
    int timeMinutes=(int)timeSeconds/60;
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
    refresh(); // Introduce las impresiones a la pantalla ncurses
}

void changePosition(int *posrX,int *posrY,char **matrix,int *gun,int *ammo){
    int number=0,result=0,newX,newY,posX=*posrX,posY=*posrY;
    while(result==0){
        number=randomPosition();
        if(number==0) result=positionCheker(newX=posX-1,newY=posY-1,matrix);
        else if(number==1) result=positionCheker(newX=posX,newY=posY-1,matrix);
        else if(number==2) result=positionCheker(newX=posX+1,newY=posY-1,matrix);
        else if(number==3) result=positionCheker(newX=posX-1,newY=posY,matrix);
        else if(number==4) {result=1; return;}
        else if(number==5) result=positionCheker(newX=posX+1,newY=posY,matrix);
        else if(number==6) result=positionCheker(newX=posX-1,newY=posY+1,matrix);
        else if(number==7) result=positionCheker(newX=posX,newY=posY+1,matrix);
        else if(number==8) result=positionCheker(newX=posX+1,newY=posY+1,matrix);
    }
    matrix[newY][newX]=matrix[posY][posX];
    matrix[posY][posX]='0';
    int g=0;//flag arma alrededor
    if(matrix[newY][newX]=='P'){
        if(matrix[newY-1][newX-1]=='G') {g=1; matrix[newY-1][newX-1]='0';}
        else if(matrix[newY-1][newX]=='G') {g=1; matrix[newY-1][newX]='0';}
        else if(matrix[newY-1][newX+1]=='G') {g=1; matrix[newY-1][newX+1]='0';}
        else if(matrix[newY][newX-1]=='G') {g=1; matrix[newY][newX-1]='0';}
        else if(matrix[newY][newX+1]=='G') {g=1; matrix[newY][newX+1]='0';}
        else if(matrix[newY+1][newX-1]=='G') {g=1; matrix[newY+1][newX-1]='0';}
        else if(matrix[newY+1][newX]=='G') {g=1; matrix[newY+1][newX]='0';}
        else if(matrix[newY+1][newX+1]=='G') {g=1; matrix[newY+1][newX+1]='0';}
    }
    if(g==1){
        (*gun)=1;
        (*ammo)=(*ammo)+ammoPerGun;
    }
	  *posrX=newX;
	  *posrY=newY;
}
//entrada zombie
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

int positionCheker(int posX,int posY,char **matrix){
    if(matrix[posY][posX]=='0') return 1;
    return 0;
}

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
    if((act==0&&countZ==0)||countP==0) return 0;
    return 1;
}

//Verificación en orden N S E W NE NW SE SW
void shoot(int posX,int posY,char **matrix,int **infoMatrix,int *ammo,int *gun){
	int targetX,targetY;
    if(matrix[posY-1][posX]=='Z'){targetY=posY-1; targetX=posX;}
    else if(matrix[posY+1][posX]=='Z'){targetY=posY-1; targetX=posX;}
    else if(matrix[posY][posX+1]=='Z'){targetY=posY-1; targetX=posX;}
    else if(matrix[posY][posX-1]=='Z'){targetY=posY-1; targetX=posX;}
    else if(matrix[posY-1][posX+1]=='Z'){targetY=posY-1; targetX=posX;}
    else if(matrix[posY-1][posX-1]=='Z'){targetY=posY-1; targetX=posX;}
    else if(matrix[posY+1][posX+1]=='Z'){targetY=posY-1; targetX=posX;}
    else if(matrix[posY+1][posX-1]=='Z'){targetY=posY-1; targetX=posX;}
    else return;
	  if(whoLives()==0){
        if(((*gun)==1)&&((*ammo)>0)){
          infoMatrix[targetY][targetX]=1;
          matrix[targetY][targetX]='z';
          (*ammo)--;
        }
    }
    else{
      infoMatrix[posY][posX]=1;
      matrix[posY][posX]='d';
    }
}

int dead(int posX,int posY){
	if(infoMatrix[posY][posX]==0) return 1;
	return 0;
}

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
