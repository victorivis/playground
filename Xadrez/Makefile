FLAGS = -std=c++20 -Wno-narrowing -D_REENTRANT -I/usr/include/SDL2 -lSDL2
WFLAGS = -std=c++20 -Wno-narrowing -I ..\..\SDL2\x86_64-w64-mingw32\include\ -L ..\..\SDL2\x86_64-w64-mingw32\lib\ -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

run: main
	./saida.out
	rm saida.out

main.o: src\main.cpp
	g++ src\main.cpp $(WFLAGS) -c -o main.o

pecas.o: src\pecas.cpp
	g++ src\pecas.cpp $(WFLAGS) -c -o pecas.o

menu.o: src\menu.cpp
	g++ src\menu.cpp $(WFLAGS) -c -o menu.o

wincpp: pecas.o menu.o main.o
	g++ .\main.o .\pecas.o .\menu.o $(WFLAGS) -o main.exe
	del *.o

winrun: wincpp
	.\main.exe
	del main.exe

