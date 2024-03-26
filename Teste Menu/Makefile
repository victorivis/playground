WFLAGS = -I ..\..\SDL2\x86_64-w64-mingw32\include\ -L ..\..\SDL2\x86_64-w64-mingw32\lib\ -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

main.o: main.cpp
	g++ .\main.cpp $(WFLAGS) -c -o main.o

menu.o: menu.cpp 
	g++ .\menu.cpp $(WFLAGS) -c -o menu.o

wincpp: menu.o main.o
	g++ .\menu.o .\main.o $(WFLAGS) -o main.exe

winrun: wincpp
	del .\*.o
	.\main.exe
	del .\*.exe