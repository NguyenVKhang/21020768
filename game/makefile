LIBFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
LIB = -Isrc/include -Lsrc/lib
all:
	g++ $(LIB) -o main main.cpp player.cpp game.cpp gameMap.cpp baseObject.cpp menuGame.cpp mixer.cpp $(LIBFLAGS)

