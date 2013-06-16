CC=g++
CFLAGS=-c
CPATH=~/Source/Rogue/
LDFLAGS=-L ~/Source/Rogue/SDLlib
FRAMEWORKS=-framework SDL -framework SDL_image -framework Cocoa
SOURCES=main.cpp Game/Game.cpp Game/Collision.cpp Render/Render.cpp Dungeon/Dungeon.cpp Entity/Entity.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=rogue

game: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -Wall -o $@ $(OBJECTS) SDLlib/SDL_Main/SDLMain.m $(LDFLAGS) $(FRAMEWORKS) 

.cpp.o:
	$(CC) $(CFLAGS) -I ~/Source/Rogue $(CPATH)$< -o $@

clean:
	rm -rf */*.o && rm -rf *.o
