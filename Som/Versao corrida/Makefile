FLAGS = -lm

run: main
	@./a.out
	@rm a.out

main: main.c
	gcc main.c $(FLAGS) $(shell pkg-config --cflags --libs sdl2)

runcpp: cpp
	@./a.out
	@rm a.out

cpp: main.cpp
	g++ -std=c++20 $(FLAGS) main.cpp $(shell pkg-config --cflags --libs sdl2)

windows: main.c
	gcc -std=c17 main.c -ISDL2\include -LSDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o main.exe

cwin: main.c
	gcc .\main.c -I .\SDL2\x86_64-w64-mingw32\include\ -L .\SDL2\x86_64-w64-mingw32\lib\ -lmingw32 -lSDL2main -lSDL2 -o main.exe

cppwin: main.cpp
	g++ .\main.cpp -I .\SDL2\x86_64-w64-mingw32\include\ -L .\SDL2\x86_64-w64-mingw32\lib\ -lmingw32 -lSDL2main -lSDL2 -o main.exe
	
runwin: cwin
	@ ./main.exe
	@ rm main.exe

runwincpp: cppwin
	@ ./main.exe
	@ rm main.exe
