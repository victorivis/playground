FLAGS = -lm -D_REENTRANT -I/usr/include/SDL2 -lSDL2

run: main som
	gcc main.o som.o $(FLAGS) -o saida.out
	rm -f *.o
	./saida.out
	rm saida.out

main: main.c
	gcc main.c $(FLAGS) -c -o main.o

som: som.c
	gcc som.c $(FLAGS) -c -o som.o	
