WFLAGS = -I ..\..\SDL2\x86_64-w64-mingw32\include\ -L ..\..\SDL2\x86_64-w64-mingw32\lib\ -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

run: main
	@./a.out
	@rm a.out

main: main.cpp
	g++ main.cpp $(shell pkg-config --cflags --libs sdl2) -lSDL2_ttf

wincpp:
	g++ -std=c++20 main.cpp $(WFLAGS) -o main.exe

winrun: wincpp
	.\main.exe
	del main.exe
