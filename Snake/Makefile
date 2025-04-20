# Libs
WINLIBS = -std=c++20 -Wno-narrowing -I ..\..\SDL2\x86_64-w64-mingw32\include\ -L ..\..\SDL2\x86_64-w64-mingw32\lib\ -lmingw32 -lSDL2main -lSDL2
LINUXLIBS = $(shell pkg-config --cflags --libs sdl2)
WEBLIBS = -s WASM=1 -s USE_SDL=2

winc: $(FILES)
	gcc snake.c $(WINLIBS) -o saida.exe

linuxc: $(FILES)
	gcc snake.c $(LINUXLIBS) -o saida.out

webc: $(FILES)
	emcc snake.c $(WEBLIBS) -o index.js

winrun: winc
	./saida.exe

linuxrun: linuxc
	./saida.out

webrun: webc
	emrun index.html