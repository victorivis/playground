FLAGS = -D_REENTRANT -I/usr/include/SDL2 -lSDL2 -lSDL2_mixer
FLAGS_outro = $(shell pkg-config --cflags --libs sdl2)
WFLAGS = -I ..\..\..\SDL2\x86_64-w64-mingw32\include\ -L ..\..\..\SDL2\x86_64-w64-mingw32\lib\ -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer

run: main
	./*.out
	rm -f *.out

main:
	g++ main.cpp $(FLAGS)

wincpp: main.cpp
	g++ .\main.cpp $(WFLAGS) -o main.exe

winrun: wincpp
	.\main.exe
	del .\main.exe