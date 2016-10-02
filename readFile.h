#ifndef READFILE_H_INCLUDED
#define READFILE_H_INCLUDED

// Primero se declaran las funciones
int * getParameters (FILE * filePointer);
char ** fgetMatrix(FILE * file, int height, int width);

// Ahora se implementan

/*
fgetParameters
    Argumentos
        Puntero a un objeto FILE (archivo)
    Devuelve
        Un arreglo con los parámetros de la partida
    Descripción
        Se leen los parámetros de la partida desde el objeto FILE que tiene los datos del archivo de entrada (se sabe que son 5),
        para que luego sean almacenados en un arreglo de enteros. Este arreglo es lo que devuelve la función.
*/

int * fgetParameters (FILE * file) {
    int * parameters = (int*)malloc(sizeof(int)*5);
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
    Descripción
        Se leen los caracteres que componen el tablero desde el objeto FILE, haciendo un recorrido de este con la funcion
        fscanf, y al mismo tiempo escribiendo los caracteres encontrados en una matriz de dimensiones height por width.
        La matriz con todo el tablero guardado es lo que devuelve esta función.
        Cabe destacar que esta función no resetea el puntero file, por lo que sólo debe llamarse una vez creado el objeto
        FILE con la respectiva referencia al archivo de entrada, y también después de llamar a la función fgetParameters de
        manera que el puntero esté posicionado al principio del tablero.

*/

char ** fgetMatrix(FILE * file, int height, int width){
	int i,j;
	char ** matrix = (char**)malloc(sizeof(char*)*(height));
	for(i=0;i<height;i++){
        matrix[i] = (char*)malloc(sizeof(char)*(width+1)); // Se reserva un espacio más por cada fila para almacenar los saltos de línea
		for(j=0;j<=width;j++){
			fscanf(file,"%c",&matrix[i][j]);
		}
	}
	return matrix;
}

#endif // READFILE_H_INCLUDED
