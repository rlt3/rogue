CC=g++
CFLAGS=-c
#SOURCES=main.cpp Render.cpp Animation.cpp Player.cpp
SOURCES=Rogue.cpp Game.cpp Entity.cpp Item.cpp Location.cpp SDL_Main/SDLMain.m
SDLLIBS=-framework SDL -framework SDL_image
FRAMEWORKS=-framework Cocoa
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=rogue

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -Wall -o $@ $(OBJECTS) $(SDLLIBS) $(FRAMEWORKS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
		rm -rf */*.o && rm -rf *.o
