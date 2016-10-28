CC= gcc
CFLAGS= -lpthread -lncurses
DEPS = functions.h readFile.h person.h zombie.h
OBJ = main.o functions.o readFile.o person.o zombie.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
