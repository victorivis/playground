FLAGS = -std=c++20 -D_REENTRANT -I/usr/include/SDL2 -lSDL2 -lSDL2_mixer -lSDL2_image

run: main som
	g++ main.o som.o $(FLAGS) -o saida.out
	rm -rf *.o
	./saida.out
	#rm saida.out

main: main.cpp
	g++ main.cpp $(FLAGS) -c -o main.o

som: som.cpp
	g++ som.cpp $(FLAGS) -c -o som.o	
