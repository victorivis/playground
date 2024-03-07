FLAGS = -std=c++20 -Wno-narrowing -D_REENTRANT -I/usr/include/SDL2 -lSDL2

run: main
	./saida.out
	#rm saida.out

main: main.cpp
	g++ main.cpp $(FLAGS) -o saida.out

