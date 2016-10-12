#ifndef READFILE_H_INCLUDED
#define READFILE_H_INCLUDED

int* fgetParameters (FILE* filePointer);
char** fgetMatrix(FILE* file,int height,int width);

#endif // READFILE_H_INCLUDED
