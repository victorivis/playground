run: main
	@./a.out
	@rm a.out

main: main.c
	gcc main.c $(shell pkg-config --cflags --libs sdl2)

runcpp: cpp
	@./a.out
	@rm a.out

cpp: main.cpp
	g++ main.cpp $(shell pkg-config --cflags --libs sdl2)

windows: main.c
	gcc -std=c17 main.c -ISDL2\include -LSDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o main.exe
