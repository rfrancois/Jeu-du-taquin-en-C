CC=gcc
CFLAGS=-Wall -ansi -lMLV
LDLIBS= `pkg-config --libs-only-l MLV` -I./headers


SRC= main.c interface.c algo.c
OBJ= $(SRC:%.c=bin/%.o)

taquin: $(OBJ)
	$(CC) -o taquin $(OBJ) $(CFLAGS)

bin/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDLIBS) -lm

clean: 
	rm -f $(OBJECTS)
	rm -f /src/*~
	rm -f taquin

