INC := `sdl2-config --cflags`
INC += -Iinclude

LIB := `sdl2-config --libs`
LIB += -lSDL2_image -lSDL2_mixer -lSDL2_gfx

CC := g++
CFLAGS := -std=c++11 -Wall -fpermissive

compile:
	$(CC) $(CFLAGS) include/*.h src/*.cpp $(INC) $(LIB) -o Main   

dep:
	sudo apt install g++ libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-gfx-dev libjsoncpp-dev indent

run:
	./Main

format:

	find src/ -name '*.cpp' -exec indent {} \;
	find include/ -name '*.h' -exec indent {} \;

clean:
	rm -f **/*.o **/*~ Main 