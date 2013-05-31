CC=g++
CFLAGS=-c
LDFLAGS=-I/Library/Frameworks/SDL.framework/Headers
FRAMEWORKS=-framework SDL -framework SDL_image -framework Cocoa
SOURCES=main.cpp Game/Game.cpp Render/Render.cpp Dungeon/Dungeon.cpp Entity/Entity.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=rogue

game: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -Wall -o $@ $(OBJECTS) SDL_Main/SDLMain.m $(LDFLAGS) $(FRAMEWORKS) 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf */*.o && rm -rf *.o
