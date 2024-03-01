player: player.cpp
	g++ player.cpp $(shell pkg-config --cflags --libs sdl2) -c -o player.o

main: main.cpp
	g++ main.cpp $(shell pkg-config --cflags --libs sdl2) -c -o main.o

run: main player
	g++ main.o player.o $(shell pkg-config --cflags --libs sdl2) -o saida.out
	rm main.o
	rm player.o
	./saida.out

teste:
	g++ player.cpp $(shell pkg-config --cflags --libs sdl2)
	./a.out
