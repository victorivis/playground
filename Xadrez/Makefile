FLAGS = -std=c++20 -Wno-narrowing -D_REENTRANT -I/usr/include/SDL2 -lSDL2
WFLAGS = -std=c++20 -Wno-narrowing -I ..\..\SDL2\x86_64-w64-mingw32\include\ -L ..\..\SDL2\x86_64-w64-mingw32\lib\ -lmingw32 -lSDL2main -lSDL2

run: main
	./saida.out
	rm saida.out

main.o: main.cpp
	g++ main.cpp $(WFLAGS) -c -o main.o

pecas.o: pecas.cpp
	g++ pecas.cpp $(WFLAGS) -c -o pecas.o

wincpp: pecas.o main.o
	g++ .\main.o .\pecas.o $(WFLAGS) -o main.exe
	del *.o

winrun: wincpp
	.\main.exe
	del main.exe

