WFLAGS = -I ..\..\SDL2\x86_64-w64-mingw32\include\ -L ..\..\SDL2\x86_64-w64-mingw32\lib\ -lmingw32 -lSDL2main -lSDL2
DEBUG = -static-libgcc -static-libstdc++ -ggdb

run: main
	@./a.out
	@rm a.out

main: main.c
	gcc main.c $(shell pkg-config --cflags --libs sdl2)

windows: main.c
	gcc -std=c17 main.c $(WFLAGS) -o main.exe