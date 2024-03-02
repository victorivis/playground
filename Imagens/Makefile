run: main
	@./a.out
	@rm a.out

main: main.cpp
	g++ main.cpp $(shell pkg-config --cflags --libs sdl2) -lSDL2_image