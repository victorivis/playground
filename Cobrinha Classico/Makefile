WFLAGS = -std=c++20 -Wno-narrowing -I ..\..\SDL2\x86_64-w64-mingw32\include\ -L ..\..\SDL2\x86_64-w64-mingw32\lib\ -lmingw32 -lSDL2main -lSDL2

run: cpp
	@./a.out
	@rm a.out

cpp: main.cpp
	g++ -std=c++20 main.cpp $(shell pkg-config --cflags --libs sdl2)

wincpp: main.cpp
	g++ .\main.cpp $(WFLAGS) -o main.exe
	
winrun: wincpp
	@ ./main.exe
	@ del main.exe
