#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

int randomPosition(){
    srand(time(NULL));
    int r = rand()%7;
    return r;
}

void printScreen(int height,int width,char **matrix){
    int i,j;
    for(i=0;i<height;i++){
        for(j=0;j<=width;j++) printf("%c",matrix[i][j]);
    }
}

#endif
