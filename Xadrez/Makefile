FLAGS = -std=c++20 -Wno-narrowing $(shell pkg-config --cflags --libs sdl2 ) -lSDL2_ttf
WFLAGS = -std=c++20 -Wno-narrowing -I ..\..\SDL2\x86_64-w64-mingw32\include\ -L ..\..\SDL2\x86_64-w64-mingw32\lib\ -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

#compilacao para windows
main.o: src\main.cpp
	g++ src\main.cpp $(WFLAGS) -c -o main.o

pecas.o: src\pecas.cpp
	g++ src\pecas.cpp $(WFLAGS) -c -o pecas.o

menu.o: src\menu.cpp
	g++ src\menu.cpp $(WFLAGS) -c -o menu.o

visual.o: src\visual.cpp
	g++ src\visual.cpp $(WFLAGS) -c -o visual.o

ia.o: src\ia.cpp
	g++ src\ia.cpp $(WFLAGS) -c -o ia.o

wincpp: pecas.o menu.o visual.o ia.o main.o
	g++ .\main.o .\pecas.o .\menu.o .\visual.o .\ia.o $(WFLAGS) -o main.exe
	del *.o

winrun: wincpp
	.\main.exe
	del main.exe


#compilacao para linux
lmain.o: src/main.cpp
	g++ src/main.cpp $(FLAGS) -c -o main.o

lpecas.o: src/pecas.cpp
	g++ src/pecas.cpp $(FLAGS) -c -o pecas.o

lmenu.o: src/menu.cpp
	g++ src/menu.cpp $(FLAGS) -c -o menu.o

lvisual.o: src/visual.cpp
	g++ src/visual.cpp $(FLAGS) -c -o visual.o

lia.o: src/ia.cpp
	g++ src/ia.cpp $(FLAGS) -c -o ia.o

cpp: lpecas.o lmenu.o lvisual.o lia.o lmain.o
	g++ ./main.o ./pecas.o ./menu.o ./visual.o ./ia.o $(FLAGS) -o saida.out
	rm *.o

run: cpp
	./saida.out
	rm *.out