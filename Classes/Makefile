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

wincpp: main.cpp
	g++ .\main.cpp -I .\SDL2\x86_64-w64-mingw32\include\ -L .\SDL2\x86_64-w64-mingw32\lib\ -lmingw32 -lSDL2main -lSDL2 -c -o main.o

winplay: player.cpp 
	g++ .\player.cpp -I .\SDL2\x86_64-w64-mingw32\include\ -L .\SDL2\x86_64-w64-mingw32\lib\ -lmingw32 -lSDL2main -lSDL2 -c -o player.o

winrun: winplay wincpp
	g++ .\player.o .\main.o -I .\SDL2\x86_64-w64-mingw32\include\ -L .\SDL2\x86_64-w64-mingw32\lib\ -lmingw32 -lSDL2main -lSDL2 -o main.exe
	del .\main.o
	del .\player.o
	.\main.exe