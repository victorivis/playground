FLAGS = -D_REENTRANT -I/usr/include/SDL2 -lSDL2 -lSDL2_mixer
FLAGS_outro = $(shell pkg-config --cflags --libs sdl2)

run: main
	./*.out
	rm -f *.out

main:
	g++ main.cpp $(FLAGS)