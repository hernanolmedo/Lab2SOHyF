#ifndef READFILE_H_INCLUDED
#define READFILE_H_INCLUDED

int* fgetParameters (FILE* filePointer);
char** fgetMatrix(FILE* file,int height,int width,person *peopleArray,zombie *zombieArray,int ammo);

#endif // READFILE_H_INCLUDED
