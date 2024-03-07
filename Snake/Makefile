WFLAGS = -I ..\..\SDL2\x86_64-w64-mingw32\include\ -L ..\..\SDL2\x86_64-w64-mingw32\lib\ -lmingw32 -lSDL2main -lSDL2

run: main
	@./a.out
	@rm a.out

main: main.c
	gcc main.c $(shell pkg-config --cflags --libs sdl2)

winc: main.c
	gcc .\main.c $(WFLAGS) -o main.exe

winrun: winc
	@ ./main.exe
	@ del main.exe