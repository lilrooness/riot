CC=gcc
CFLAGS= -I /usr/include/lua5.2 -llua5.2 `allegro-config --libs`

all: riot

riot: main.c rioter.h
	$(CC) $(CFLAGS) main.c rioter.h -o riot

clean:
	rm -rf *.o *.gch riot
