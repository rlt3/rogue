CC=g++
CFLAGS=-c
LDFLAGS=-I/Library/Frameworks/SDL.framework/Headers
FRAMEWORKS=-framework SDL -framework SDL_image -framework Cocoa
#SOURCES=main.cpp Render.cpp Animation.cpp Player.cpp
SOURCES=main.cpp Render/Render.cpp Render/Animation.cpp Entity/Entity.cpp Entity/Player.cpp Game.cpp Dungeon/Dungeon.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=rogue

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -Wall -o $@ $(OBJECTS) SDLMain.m $(LDFLAGS) $(FRAMEWORKS) 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
		rm -rf */*.o
