#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

int randomPosition(){
    srand(time(NULL));
    int r = rand()%8;
    return r;
}

int whoLives(){
    srand(time(NULL));
    int r = rand()%9;
    if(r<3) return 0;
    else return 1;
}

void printScreen(int height,int width,char **matrix){
    int i,j;
    for(i=0;i<height;i++){
        for(j=0;j<=width;j++){
            printf("%c",matrix[i][j]);
        }
    }
}

void move(int posX,int posY,char **matrix){
    int number=0,result=0,newX,newY;
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
}

int positionCheker(int posX,int posY,char **matrix){
    if(matrix[posY][posX]=='0') return 1;
    return 0;
}

int gameOver(int height,int width,char **matrix){
    int i,j,countP=0,countZ=0;
    for(i=0;i<height;i++){
        for(j=0;j<=width;j++){
            if(matrix[i][j]=='P') countP++;
            else if(matrix[i][j]=='Z'||matrix[i][j]=='d') countZ++;
        }
    }
    if(countP==0||countZ==0) return 1;
    return 0;
}

//Verificación en orden N S E W NE NW SE SW
void shoot(int posX,int posY,char **matrix){
	int targetX,targetY;
    if(matrix[targetY=posY-1][targetX=posX]=='Z')
    else if(matrix[targetY=posY+1][targetX=posX]=='Z')
    else if(matrix[targetY=posY][targetX=posX+1]=='Z')
    else if(matrix[targetY=posY][targetX=posX-1]=='Z')
    else if(matrix[targetY=posY-1][targetX=posX+1]=='Z')
    else if(matrix[targetY=posY-1][targetX=posX-1]=='Z')
    else if(matrix[targetY=posY+1][targetX=posX+1]=='Z')
    else if(matrix[targetY=posY+1][targetX=posX-1]=='Z')
    else return;
	if(whoLives()==0) matrix[targetY][targetX]='z';
	else matrix[posY][posX]='d';
}

//void killZombie(){


//}


#endif
