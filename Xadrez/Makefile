FLAGS = -std=c++20 -Wno-narrowing -D_REENTRANT -I/usr/include/SDL2 -lSDL2
WFLAGS = -std=c++20 -Wno-narrowing -I ..\..\SDL2\x86_64-w64-mingw32\include\ -L ..\..\SDL2\x86_64-w64-mingw32\lib\ -lmingw32 -lSDL2main -lSDL2

run: main
	./saida.out
	rm saida.out

main: main.cpp
	g++ main.cpp $(FLAGS) -o saida.out

wincpp: main.cpp
	g++ .\main.cpp $(WFLAGS) -o main.exe

winrun: wincpp
	.\main.exe
	del main.exe

