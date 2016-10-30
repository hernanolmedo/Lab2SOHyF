IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -lpthread -lncurses
ODIR=obj
LDIR=../lib
LIBS=-lm
_DEPS=functions.h readFile.h person.h zombie.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))
_OBJ=main.o functions.o readFile.o person.o zombie.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)
.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~